// PhoneNumbersTable.cpp
//

#include "pch.h"
#include "PhoneNumbersTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable


// Constructor / Destructor
// ----------------

CPhoneNumbersTable::CPhoneNumbersTable() : CBaseTable()
{
	m_strTableName = L"PHONE_NUMBERS";
}

CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSession) : CBaseTable(oSession)
{
	m_strTableName = L"PHONE_NUMBERS";
}

CPhoneNumbersTable::~CPhoneNumbersTable()
{

}


// Overrides
// ----------------

PHONE_NUMBERS& CPhoneNumbersTable::GetAccessorData()
{
	return m_recPhoneNumber;
}

const long* CPhoneNumbersTable::GetUpdateCounter(const PHONE_NUMBERS& recObject)
{
	const long* pUpdateCounter = &recObject.lUpdateCounter;
	return pUpdateCounter;
}
