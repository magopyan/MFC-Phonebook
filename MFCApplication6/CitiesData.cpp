// CitiesData.cpp
//

#include "pch.h"  
#include "CitiesData.h" 
#include "ConnectToDB.h"  


/////////////////////////////////////////////////////////////////////////////
// CCitiesData


// Constructor / Destructor
// ----------------

CCitiesData::CCitiesData()
{

}

CCitiesData::~CCitiesData()
{

}


// Methods
// ----------------

BOOL CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
{
	CCitiesTable oCitiesTable;
	if (!oCitiesTable.SelectAll(oCitiesArray))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	CCitiesTable oCitiesTable;
	if (!oCitiesTable.SelectWhereID(lID, recCities))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CCitiesData::UpdateWhereID(const long lID, const CITIES& recCities)
{
	CCitiesTable oCitiesTable;
	if (!oCitiesTable.UpdateWhereID(lID, recCities))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CCitiesData::Insert(CITIES& recCities)
{
	CCitiesTable oCitiesTable;
	if (!oCitiesTable.Insert(recCities))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CCitiesData::DeleteWhereID(const long lID)
{
	CCitiesTable oCitiesTable;
	if (!oCitiesTable.DeleteWhereID(lID))
	{
		return FALSE;
	}

	return TRUE;
}


