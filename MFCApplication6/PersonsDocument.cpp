// PersonsDocument.cpp 
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "CitiesDocument.h"
#endif
#include "PersonsView.h"
#include "PersonsDocument.h"
#include "PersonsData.h"
#include "CitiesData.h"
#include "PhoneTypesData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPersonsDocument, CDocument)
BEGIN_MESSAGE_MAP(CPersonsDocument, CDocument)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument


// Constructor / Destructor
// ----------------

CPersonsDocument::CPersonsDocument() noexcept
{

}

CPersonsDocument::~CPersonsDocument()
{

}


// Methods
// ----------------

const CPersonsArray& CPersonsDocument::GetDocumentPersonsData() const
{
	return m_oPersonsArray;
}

BOOL CPersonsDocument::GetPhoneNumbersArray(const long& lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	CPersonsData oData;
	if (!oData.GetPersonsNumbers(lPersonID, oPhoneNumbersArray))
	{
		return FALSE;
	}
	return TRUE;
}

CCitiesMap& CPersonsDocument::GetDocumentCitiesData() 
{
	return m_oCitiesMap;
}

CPhoneTypesMap& CPersonsDocument::GetDocumentPhoneTypesData()
{
	return m_oPhoneTypesMap;
}

const PERSONS* CPersonsDocument::GetPersonWithID(const long& lID) const 
{
	for (INT_PTR i = 0; i < m_oPersonsArray.GetCount(); i++)
	{
		if (m_oPersonsArray.GetAt(i)->lID == lID)
		{
			return m_oPersonsArray.GetAt(i);
		}
	}
	return NULL;
}


BOOL CPersonsDocument::AddPerson(CPerson& oPersonAndPhones) 
{
	CPersonsData oData;
	if (!oData.InsertPersonAndPhones(oPersonAndPhones))
	{
		return FALSE;
	}
	PERSONS* pPerson = new PERSONS(oPersonAndPhones.m_recPerson);
	m_oPersonsArray.Add(pPerson);
	UpdateAllViews(NULL, eActionAddPerson, (CObject*)pPerson);
	return TRUE;
}

BOOL CPersonsDocument::EditPerson(CPerson& oPersonAndPhones)
{
	CPersonsData oData;
	if (!oData.UpdatePersonAndPhones(oPersonAndPhones))
	{
		return FALSE;
	}
	
	UpdateEditedPerson(oPersonAndPhones.m_recPerson);
	UpdateAllViews(NULL, eActionEditPerson, (CObject*)&oPersonAndPhones.m_recPerson);
	return TRUE;
}

void CPersonsDocument::UpdateEditedPerson(const PERSONS& recPerson)
{
	for (INT_PTR i = 0; i < m_oPersonsArray.GetCount(); i++)
	{
		PERSONS* pPerson = m_oPersonsArray.GetAt(i);
		if (pPerson->lID == recPerson.lID)
		{
			*pPerson = recPerson;
			break;
		}
	}
}

BOOL CPersonsDocument::DeletePerson(const long& lID) 
{
	CPersonsData oData;
	if (!oData.DeletePersonWhereID(lID))
	{
		return FALSE;
	}
	if (GetPersonWithID(lID) == NULL)
	{
		AfxMessageBox(_T("Абонатът, който трябва да бъде изтрит, липсва в документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	UpdateAllViews(NULL, eActionDeletePerson, (CObject*)lID);
	DeletePersonFromDocArray(lID);
	return TRUE;
}

void CPersonsDocument::DeletePersonFromDocArray(const long& lID)
{
	for (INT_PTR i = 0; i < m_oPersonsArray.GetCount(); i++)
	{
		PERSONS* pPerson = m_oPersonsArray.GetAt(i);
		if (pPerson->lID == lID)
		{
			delete pPerson;
			pPerson = NULL;
			m_oPersonsArray.RemoveAt(i);
			break;
		}
	}
}


// Overrrides
// ----------------

BOOL CPersonsDocument::OnNewDocument()
{
	CPersonsData oPersonsData;
	if (!oPersonsData.SelectAllPersons(m_oPersonsArray))
	{
		AfxMessageBox(_T("Грешка при извличване на данните за абонатите от базата данни."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	CCitiesArray oCitiesArray;
	CCitiesData oCitiesData;
	if (!oCitiesData.SelectAll(oCitiesArray))
	{
		AfxMessageBox(_T("Грешка при извличване на данните за градовете от базата данни."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	long lID = 0;
	CITIES recCity;
	m_oCitiesMap.InitHashTable(oCitiesArray.GetCount());

	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); i++)
	{
		lID = oCitiesArray.GetAt(i)->lID;
		recCity = *oCitiesArray.GetAt(i);
		m_oCitiesMap.SetAt(lID, recCity);
	}

	CPhoneTypesArray oPhoneTypesArray;
	CPhoneTypesData oPhoneTypesData;
	if (!oPhoneTypesData.SelectAll(oPhoneTypesArray))
	{
		AfxMessageBox(_T("Грешка при извличване на данните за видовете номера от базата данни."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	PHONE_TYPES recPhoneType;
	m_oPhoneTypesMap.InitHashTable(oPhoneTypesArray.GetCount());

	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); i++)
	{
		lID = oPhoneTypesArray.GetAt(i)->lID;
		recPhoneType = *oPhoneTypesArray.GetAt(i);
		m_oPhoneTypesMap.SetAt(lID, recPhoneType);
	}

	if (!CDocument::OnNewDocument())
	{
		AfxMessageBox(_T("Грешка при създаването на документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}


// CPersonsDocument serialization
// ----------------

void CPersonsDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPersonsDocument::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPersonsDocument::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPersonsDocument::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif 


// CPersonsDocument diagnostics
// ----------------

#ifdef _DEBUG
void CPersonsDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonsDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif 


