// CitiesTable.cpp
//

#include "pch.h"
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable


// Constructor / Destructor
// ----------------

CCitiesTable::CCitiesTable()
{
	m_strTableName = L"CITIES";
}

CCitiesTable::~CCitiesTable()
{

}


// Overrides
// ----------------

CITIES& CCitiesTable::GetAccessorData()
{
	return m_recCity;
}

const long* CCitiesTable::GetUpdateCounter(const CITIES& recObject)
{
	const long* pUpdateCounter = &recObject.lUpdateCounter;
	return pUpdateCounter;
}
