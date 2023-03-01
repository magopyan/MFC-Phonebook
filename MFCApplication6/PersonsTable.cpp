// PersonsTable.cpp
//

#include "pch.h"
#include "PersonsTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable


// Constructor / Destructor
// ----------------

CPersonsTable::CPersonsTable() : CBaseTable()
{
	m_strTableName = L"PERSONS";
}

CPersonsTable::CPersonsTable(CSession& oSession) : CBaseTable(oSession)
{
	m_strTableName = L"PERSONS";
}

CPersonsTable::~CPersonsTable()
{

}


// Overrides
// ----------------

PERSONS& CPersonsTable::GetAccessorData()
{
	return m_recPerson;
}

const long* CPersonsTable::GetUpdateCounter(const PERSONS& recObject)
{
	const long* pUpdateCounter = &recObject.lUpdateCounter;
	return pUpdateCounter;
}
