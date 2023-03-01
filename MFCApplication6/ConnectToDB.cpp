// ConnectToDB.cpp
//

#include "pch.h"
#include "ConnectToDB.h" 


/////////////////////////////////////////////////////////////////////////////
// CConnectToDB


// Constructor / Destructor
// ----------------

CConnectToDB::CConnectToDB()
{

}

CConnectToDB::~CConnectToDB()
{

}


// Initialize Static Members
// ----------------

CConnectToDB* CConnectToDB::_pInstance = NULL;


// Methods
// ----------------

CConnectToDB* CConnectToDB::GetInstance()
{
	if (!_pInstance)
	{
		_pInstance = new CConnectToDB;
	}
	return _pInstance;
}

CDataSource& CConnectToDB::GetDataSource()
{
	return m_oConnection;
}


BOOL CConnectToDB::OpenConnection()
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-OM63SED"));	
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));			
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));	
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Установяване на връзка с БД
	HRESULT hResult = m_oConnection.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		CString strMessage;
		strMessage.Format(_T("Неуспешно установяване на връзка с базата данни. Грешка: %d"), hResult);
		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}


void CConnectToDB::UpdateDBPropSet(CDBPropSet& oUpdateDBPropSet)
{
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
}


