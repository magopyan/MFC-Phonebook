// PhoneTypesData.cpp
//

#include "pch.h"  
#include "PhoneTypesData.h" 
#include "ConnectToDB.h"  


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData


// Constructor / Destructor
// ----------------

CPhoneTypesData::CPhoneTypesData()
{

}

CPhoneTypesData::~CPhoneTypesData()
{

}


// Methods
// ----------------

BOOL CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTypesArray)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (!oPhoneTypesTable.SelectWhereID(lID, recPhoneType))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CPhoneTypesData::UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (!oPhoneTypesTable.UpdateWhereID(lID, recPhoneType))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CPhoneTypesData::Insert(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (!oPhoneTypesTable.Insert(recPhoneType))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CPhoneTypesData::DeleteWhereID(const long lID)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (!oPhoneTypesTable.DeleteWhereID(lID))
	{
		return FALSE;
	}

	return TRUE;
}


