// PhoneTypesTable.cpp
//

#include "pch.h"
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable


// Constructor / Destructor
// ----------------

CPhoneTypesTable::CPhoneTypesTable()
{
	m_strTableName = L"PHONE_TYPES";
}

CPhoneTypesTable::~CPhoneTypesTable()
{

}


// Overrides
// ----------------

PHONE_TYPES& CPhoneTypesTable::GetAccessorData()
{
	return m_recPhoneType;
}

const long* CPhoneTypesTable::GetUpdateCounter(const PHONE_TYPES& recObject)
{
	const long* pUpdateCounter = &recObject.lUpdateCounter;
	return pUpdateCounter;
}
