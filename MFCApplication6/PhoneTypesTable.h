// PhoneTypesTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesAccessor

/// <summary>
/// ������� �� ������� ��������� PHONE_TYPES; ���� �������� �� ������� �������� ����
/// </summary>
class CPhoneTypesAccessor
{
protected:
	/// <summary> ����� �� ��������� ��������� PHONE_TYPES, � ����� �� ������ ��������� </summary>
	PHONE_TYPES m_recPhoneType;

	// ����� ��������� 2 ������� �������� � �������� ������� �� ��������� ��������� 
	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // ������� � ���� 0 �� ���� lID (ID)
		COLUMN_ENTRY(1, m_recPhoneType.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // ������� � ���� 1 �� ���������� ������
		COLUMN_ENTRY(2, m_recPhoneType.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneType.szPhoneType)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

/// <summary>
/// �������� ���� �� ������� PHONE_TYPES
/// ��������� CBaseTable, ���� �������� �������� �����, � ����� �������� �� ������� ���� �� �������
/// </summary>
class CPhoneTypesTable : public CBaseTable<CPhoneTypesAccessor, PHONE_TYPES>
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� �����������. ������ �� ������� �� ������� ���� �� ��� �� ��������� �������� "PHONE_TYPES" </summary>
	CPhoneTypesTable();

	/// <summary> ����������� �� ���������� </summary>
	~CPhoneTypesTable();


// Overrides
// ----------------

protected:
	/// <summary> ����� �� ���������� �� ������� �� ��������, � ����� �� ��������� ������ ������������ ��� �� RowSet-� </summary>
	/// <returns> ����� ���������� ��� ������� �� �������� </returns>
	PHONE_TYPES& GetAccessorData();

	/// <summary> ����� �� ��������� �� ������� �� ��������� �����-��� �����, ����� ����� ������ �� Update Counter </summary>
	/// <param name="recObject"> �����-��� �����, ����� Update Counter �� ���� ������ </param>
	/// <returns> ����� ����� ����, � ����� ����������� ��� � ��� �������� </returns>
	const long* GetUpdateCounter(const PHONE_TYPES& recObject);
}; 
