// PersonsData.cpp
//

#include "pch.h"  
#include "PersonsData.h" 
#include "ConnectToDB.h"  


/////////////////////////////////////////////////////////////////////////////
// CPersonsData


// Constructor / Destructor
// ----------------

CPersonsData::CPersonsData()
{

}

CPersonsData::~CPersonsData()
{

}


// Methods
// ----------------

BOOL CPersonsData::OpenSession(CSession& oSession)
{
	CDataSource& oDataSource = CConnectToDB::GetInstance()->GetDataSource();
	HRESULT lHResult = oSession.Open(oDataSource);
	if (FAILED(lHResult))
	{
		CString strMessage;
		strMessage.Format(_T("Неуспешно отваряне на сесия. Грешка: %d"), lHResult);
		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);

		return FALSE;
	}
	return TRUE;
}

BOOL CPersonsData::CheckQueryResult(const HRESULT& lHResult, CSession& oSession, const CString& strQuery)
{
	if (FAILED(lHResult))
	{
		CString strMessage;
		strMessage.Format(_T("Неуспешно изпълнение на заявката. Грешка: %d. Заявка: %s"), lHResult, strQuery);
		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonsData::SelectAllPersons(CPersonsArray& oPersonsArray)
{
	CPersonsTable oPersonsTable;
	if (!oPersonsTable.SelectAll(oPersonsArray))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CPersonsData::GetPersonsNumbers(const long& lID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	CPhoneNumbersArray oArray;
	CPhoneNumbersTable oPhoneNumbersTable;
	if (!oPhoneNumbersTable.SelectAll(oArray))
	{
		return FALSE;
	}

	for (INT_PTR i = 0; i < oArray.GetCount(); i++)
	{
		if (oArray.GetAt(i)->lPersonID == lID)
		{
			PHONE_NUMBERS* pNumber = new PHONE_NUMBERS(*oArray.GetAt(i));
			oPhoneNumbersArray.Add(pNumber);
		}
	}
	return TRUE;
}


BOOL CPersonsData::InsertPersonAndPhones(CPerson& oPersonAndPhones)
{
	CSession oSession;
	if (!OpenSession(oSession))
	{
		return FALSE;
	}

	HRESULT lHResult = oSession.StartTransaction();
	if (!CheckQueryResult(lHResult, oSession, L"BEGIN TRAN"))
	{
		return FALSE;
	}

	CPersonsTable oPersonsTable(oSession);
	if (!oPersonsTable.Insert(oPersonAndPhones.m_recPerson))
	{
		oSession.Abort();
		return FALSE;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	PHONE_NUMBERS* pPhoneNumber;
	for (INT_PTR i = 0; i < oPersonAndPhones.m_oPhoneNumbers.GetCount(); i++)
	{
		pPhoneNumber = oPersonAndPhones.m_oPhoneNumbers.GetAt(i);
		pPhoneNumber->lPersonID = oPersonAndPhones.m_recPerson.lID;

		if (!oPhoneNumbersTable.Insert(*pPhoneNumber))
		{
			oSession.Abort();
			return FALSE;
		}
	}

	lHResult = oSession.Commit(); 
	if (!CheckQueryResult(lHResult, oSession, L"COMMIT"))
	{
		oSession.Abort();
		return FALSE;
	}

	oSession.Close();
	oPersonsTable.Close();
	oPhoneNumbersTable.Close();
	return TRUE;
}


BOOL CPersonsData::UpdatePersonAndPhones(CPerson& oPersonAndPhones)
{
	CSession oSession;
	if (!OpenSession(oSession))
	{
		return FALSE;
	}

	HRESULT lHResult = oSession.StartTransaction(); 
	if (!CheckQueryResult(lHResult, oSession, L"BEGIN TRAN"))
	{
		return FALSE;
	}

	CPersonsTable oPersonsTable(oSession);
	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	const long lID = oPersonAndPhones.m_recPerson.lID;
	const PERSONS recPerson = oPersonAndPhones.m_recPerson;
	if (!oPersonsTable.UpdateWhereID(lID, recPerson))
	{
		oSession.Abort();
		return FALSE;
	}

	CPhoneNumbersArray oInsert, oUpdate;
	CPhoneNumbersArray oAllNumbersWherePersonID;
	if (!GetPersonsNumbers(lID, oAllNumbersWherePersonID))
	{
		oSession.Abort();
		return FALSE;
	}

	PHONE_NUMBERS* pCurrentPhoneNumber1;
	PHONE_NUMBERS* pCurrentPhoneNumber2;
	bool bNumberGotUpdated;
	long lNumberID;


	for (INT_PTR i = 0; i < oAllNumbersWherePersonID.GetCount(); i++)
	{
		pCurrentPhoneNumber1 = oAllNumbersWherePersonID.GetAt(i);
		lNumberID = pCurrentPhoneNumber1->lID;
		bNumberGotUpdated = false;
		
		for (INT_PTR j = 0; j < oPersonAndPhones.m_oPhoneNumbers.GetCount(); j++)
		{
			pCurrentPhoneNumber2 = oPersonAndPhones.m_oPhoneNumbers.GetAt(j);
			if (lNumberID == pCurrentPhoneNumber2->lID && lNumberID != 0)
			{
				bNumberGotUpdated = true;
				PHONE_NUMBERS* pNewPhoneNumber = new PHONE_NUMBERS(*pCurrentPhoneNumber2);
				oUpdate.Add(pNewPhoneNumber);
				break;
			}
		}
		if (!bNumberGotUpdated)
		{
			pCurrentPhoneNumber2 = pCurrentPhoneNumber1;
			if (!oPhoneNumbersTable.DeleteWhereID(pCurrentPhoneNumber2->lID))
			{
				oSession.Abort();
				return FALSE;
			}
		}
	}


	PHONE_NUMBERS* pCurrentPhoneNumber;
	for (INT_PTR i = 0; i < oUpdate.GetCount(); i++)
	{
		const PHONE_NUMBERS recPhoneNumber = *oUpdate.GetAt(i);
		if (!oPhoneNumbersTable.UpdateWhereID(recPhoneNumber.lID, recPhoneNumber))
		{
			oSession.Abort();
			return FALSE;
		}
	}

	for (INT_PTR i = 0; i < oPersonAndPhones.m_oPhoneNumbers.GetCount(); i++)
	{
		pCurrentPhoneNumber = oPersonAndPhones.m_oPhoneNumbers.GetAt(i);
		if (pCurrentPhoneNumber->lID == 0)
		{
			PHONE_NUMBERS* pNewPhoneNumber = new PHONE_NUMBERS(*pCurrentPhoneNumber); 
			pNewPhoneNumber->lPersonID = lID;
			oInsert.Add(pNewPhoneNumber);
		}
	}

	for (INT_PTR i = 0; i < oInsert.GetCount(); i++)
	{
		pCurrentPhoneNumber = oInsert.GetAt(i);
		pCurrentPhoneNumber->lPersonID = lID;

		if (!oPhoneNumbersTable.Insert(*pCurrentPhoneNumber))
		{
			oSession.Abort();
			return FALSE;
		}
	}

	lHResult = oSession.Commit(); 
	if (!CheckQueryResult(lHResult, oSession, L"COMMIT"))
	{
		oSession.Abort();
		return FALSE;
	}

	oSession.Close();
	oPersonsTable.Close();
	oPhoneNumbersTable.Close();
	return TRUE;
}


BOOL CPersonsData::DeletePersonWhereID(const long& lID)
{
	CSession oSession;
	if (!OpenSession(oSession))
	{
		return FALSE;
	}

	HRESULT lHResult = oSession.StartTransaction(); 
	if (!CheckQueryResult(lHResult, oSession, L"BEGIN TRAN"))
	{
		return FALSE;
	}

	CPersonsTable oPersonsTable(oSession);
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	CPhoneNumbersArray oPhoneNumbersArray;

	GetPersonsNumbers(lID, oPhoneNumbersArray);
	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pNumber = oPhoneNumbersArray.GetAt(i);
		if (!oPhoneNumbersTable.DeleteWhereID(pNumber->lID))
		{
			oSession.Abort();
			return FALSE;
		}
	}

	if (!oPersonsTable.DeleteWhereID(lID)) 
	{
		oSession.Abort();
		return FALSE;
	}

	lHResult = oSession.Commit(); 
	if (!CheckQueryResult(lHResult, oSession, L"COMMIT"))
	{
		oSession.Abort();
		return FALSE;
	}

	oSession.Close();
	oPersonsTable.Close();
	oPhoneNumbersTable.Close();
	return TRUE;
}


