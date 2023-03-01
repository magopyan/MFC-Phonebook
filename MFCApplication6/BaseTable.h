// BaseTable.h
//

#pragma once
#include "PhoneBook_Header.h" 
#include "ConnectToDB.h"  

// Кодиране на аксесора, който ще отговаря за ID и на този, който ще отговаря за всички останали колони
enum eAccessor { eAccessorID = 0, eAccessorAllOtherColumns = 1 };


/////////////////////////////////////////////////////////////////////////////
// CBaseTable

/// <summary>
/// Базов темплейтен табличен клас, който се наследява от табличните класове на всяка таблица 
/// </summary>
template <typename ACCESSOR, typename STRUCT> // Темплейтни типове, с които методите на класа ще работят
class CBaseTable : public CCommand<CAccessor<ACCESSOR>>
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор, създаващ и инициализиращ сесия </summary>
	CBaseTable()
	{
		m_bSessionIsPassedAsParameter = false;

		m_pSession = new CSession;
		if (!OpenSession(*m_pSession))
		{
			return;
		}
	}

	/// <summary> Експлицитен конструктор, приемащ като аргумент вече отворена сесия </summary>
	/// <param name="oSession"> Подадена вече инициализирана сесия </param>
	CBaseTable(CSession& oSession)
	{
		m_pSession = &oSession;
		m_bSessionIsPassedAsParameter = true;
	}

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CBaseTable()
	{

	}


// Methods
// ----------------

private:
	/// <summary> Напълно виртуален метод за получаване на мембъра на аксесорния клас, в който се записват прочетените от БД редове </summary>
	/// <returns> Връща референция към мембъра на аксесорния клас </returns>
	virtual STRUCT& GetAccessorData() = 0;

	/// <summary> Напълно виртуален метод за получаване на Update Counter на обект </summary>
	/// <param name="recObject"> Обекта, чийто Update Counter трябва да бъде получен </param>
	/// <returns> Връща указател към мембъра на обекта, който отговаря за Update Counter </returns>
	virtual const long* GetUpdateCounter(const STRUCT& recObject) = 0;


	/// <summary> Метод за инициализиране на сесия </summary>
	/// <param name="oSession"> Обект-сесия, която да бъде инициализирана </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL OpenSession(CSession& oSession)
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

	/// <summary> Метод за проверка на изпълнението на дадена SQL заявка </summary>
	/// <param name="lHResult"> Съдържа резултата от изпълнената заявка </param>
	/// <param name="oSession"> Подадена вече отворена сесия </param>
	/// <param name="strQuery"> Заявката под форма на символен низ </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL CheckQueryResult(const HRESULT& lHResult, CSession& oSession, const CString& strQuery)
	{
		if (FAILED(lHResult))
		{
			CString strMessage;
			strMessage.Format(_T("Неуспешно изпълнение на заявката. Грешка: %d. Заявка: %s"), lHResult, strQuery);
			AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
			if (!m_bSessionIsPassedAsParameter)
			{
				oSession.Close();
			}
			return FALSE;
		}
		return TRUE;
	}


public:
	/// <summary> Метод за четене на всички редове от съответната таблица в БД, като те се запазват в масива-параметър </summary>
	/// <param name="oArray"> Масив, в който трябва да се съхранят прочетените от БД редове </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL SelectAll(CTypedPtrArrayAutoDelete<STRUCT>& oArray)
	{
		CString strQuery = _T("SELECT * FROM ");
		strQuery += m_strTableName;

		HRESULT lHResult = Open(*m_pSession, strQuery);
		if (!CheckQueryResult(lHResult, *m_pSession, strQuery))
		{
			return FALSE;
		}

		while ((lHResult = MoveNext()) == S_OK)
		{
			
			STRUCT* pObject = new STRUCT;
			*pObject = GetAccessorData(); 
			oArray.Add(pObject); 
		}
		if (lHResult != DB_S_ENDOFROWSET)
		{
			if (!CheckQueryResult(lHResult, *m_pSession, strQuery))
			{
				return FALSE;
			}
		}

		Close();
		if (!m_bSessionIsPassedAsParameter)
		{
			m_pSession->Close();
			delete m_pSession;
			m_pSession = NULL;
		}
		return TRUE;
	}


	/// <summary> Метод за четене на един ред от съответната таблица с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде прочетен </param>
	/// <param name="recObject"> Референция към обект от дискова структура, в чийто мембъри ще се запазят данните от прочетения ред </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL SelectWhereID(const long& lID, STRUCT& recObject)
	{
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName, lID);

		HRESULT lHResult = Open(*m_pSession, strQuery);
		if (!CheckQueryResult(lHResult, *m_pSession, strQuery))
		{
			return FALSE;
		}

		if (MoveNext() != S_OK)
		{
			return FALSE;
		}

		recObject = GetAccessorData();

		Close();
		if (!m_bSessionIsPassedAsParameter)
		{
			m_pSession->Close();
			delete m_pSession;
			m_pSession = NULL;
		}
		return TRUE;
	}

	
	/// <summary> Метод за промяна на данните на ред от БД с определено ID </summary>
	/// <param name="lID"> ID на реда, който да бъде променен </param>
	/// <param name="recObject"> Референция към обект от дискова структура, с чийто мембъри ще се заменят съответните данни на реда в БД </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL UpdateWhereID(const long& lID, const STRUCT& recObject)
	{
		HRESULT lHResult;
		if (!m_bSessionIsPassedAsParameter)
		{
			lHResult = m_pSession->StartTransaction(); 
			if (!CheckQueryResult(lHResult, *m_pSession, L"BEGIN TRAN"))
			{
				return FALSE;
			}
		}
		
		// Конструираме заявката за прочитане на реда с подаденото ID, като същевременно го заключваме за UPDATE
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WITH (UPDLOCK) WHERE ID = %d"), m_strTableName, lID);

		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		CConnectToDB::GetInstance()->UpdateDBPropSet(oUpdateDBPropSet);

		lHResult = Open(*m_pSession, strQuery, &oUpdateDBPropSet);
		if (!CheckQueryResult(lHResult, *m_pSession, strQuery))
		{
			return FALSE;
		}

		if (MoveNext() != S_OK)
		{
			return FALSE;
		}

		STRUCT* pAccessorObject = &GetAccessorData();
		long lAccessorObjectUpdateCounter = *GetUpdateCounter(*pAccessorObject);
		long lArgumentObjectUpdateCounter = *GetUpdateCounter(recObject);
		if (lAccessorObjectUpdateCounter != lArgumentObjectUpdateCounter) 
		{
			CString strMessage;
			strMessage.Format(_T("Грешка при обновяване на ред с ID = %d: Редът е бил обновен междувременно и трябва да бъде извлечен отново.", lID));
			AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);

			lHResult = m_pSession->Abort(); 
			if (!CheckQueryResult(lHResult, *m_pSession, L"ROLLBACK"))
			{
				return FALSE;
			}
			return FALSE;
		}

		*pAccessorObject = recObject;
		const long* pUpdateCounter = GetUpdateCounter(*pAccessorObject);
		pUpdateCounter++;

		lHResult = SetData(eAccessorAllOtherColumns); 
		if (!CheckQueryResult(lHResult, *m_pSession, L"UPDATE"))
		{
			m_pSession->Abort();
			return FALSE;
		}

		Close();
		if (!m_bSessionIsPassedAsParameter)
		{
			lHResult = m_pSession->Commit(); 
			if (!CheckQueryResult(lHResult, *m_pSession, L"COMMIT"))
			{
				m_pSession->Abort();
				return FALSE;
			}

			
			m_pSession->Close();
			delete m_pSession;
			m_pSession = NULL;
		}

		return TRUE;
	}


	/// <summary> Метод за добавяне на нов ред към таблицата и извличане на генерираното за него от SQL ID </summary>
	/// <param name="recObject"> Референция към обект от дискова структура, който ще бъде добавен като нов ред и ще приеме генерираното му от SQL ID </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL Insert(STRUCT& recObject)
	{
		CString strQuery;
		strQuery.Format(_T("SELECT TOP 0 * FROM %s"), m_strTableName); // отваряне на RowSet без да се извличат редове
		
		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		CConnectToDB::GetInstance()->UpdateDBPropSet(oUpdateDBPropSet);

		HRESULT lHResult = Open(*m_pSession, strQuery, &oUpdateDBPropSet);
		if (!CheckQueryResult(lHResult, *m_pSession, strQuery))
		{
			return FALSE;
		}
		

		STRUCT* pAccessorObject = &GetAccessorData();
		*pAccessorObject = recObject;

		lHResult = __super::Insert(eAccessorAllOtherColumns); // използване на втория аксесор с ключ=1, който за ID не си присвоява стойността от m_recCity
		if (!CheckQueryResult(lHResult, *m_pSession, L"INSERT"))
		{
			return FALSE;
		}

		if (MoveNext() != S_OK)
		{
			return FALSE;
		}

		recObject = GetAccessorData();

		Close();
		if (!m_bSessionIsPassedAsParameter)
		{
			m_pSession->Close();
			delete m_pSession;
			m_pSession = NULL;
		}
		return TRUE;
	}

	
	/// <summary> Метод за изтриване на ред с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде изтрит </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL DeleteWhereID(const long& lID)
	{
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d;"), m_strTableName, lID);

		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		CConnectToDB::GetInstance()->UpdateDBPropSet(oUpdateDBPropSet);

		HRESULT lHResult = Open(*m_pSession, strQuery, &oUpdateDBPropSet);
		if (!CheckQueryResult(lHResult, *m_pSession, strQuery))
		{
			return FALSE;
		}

		if (MoveNext() != S_OK)
		{
			return FALSE;
		}

		lHResult = Delete();
		if (!CheckQueryResult(lHResult, *m_pSession, L"DELETE"))
		{
			return FALSE;
		}

		Close();
		if (!m_bSessionIsPassedAsParameter)
		{
		
			m_pSession->Close();
			delete m_pSession;
			m_pSession = NULL;
		}
		return TRUE;
	}


// Members
// ----------------

public:
	/// <summary> Булев мембър, показващ дали сесията е подадена (true) или трябва да се създаде в този клас (false) </summary>
	bool m_bSessionIsPassedAsParameter;

	/// <summary> Указател към сесията, чрез която методите подават заявки към БД </summary>
	CSession* m_pSession;

	/// <summary> Символен низ, съдържащ името на таблицата от БД, с която наследникът на този клас ще работи </summary>
	CString m_strTableName;
};
