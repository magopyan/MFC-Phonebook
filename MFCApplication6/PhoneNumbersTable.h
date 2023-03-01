// PhoneNumbersTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor

/// <summary>
/// ������� �� ������� ��������� PHONE_NUMBERS; ���� �������� �� ������� �������� ����
/// </summary>
class CPhoneNumbersAccessor
{
protected:
	/// <summary> ����� �� ��������� ��������� PHONE_NUMBERS, � ����� �� ������ ��������� </summary>
	PHONE_NUMBERS m_recPhoneNumber;

	// ����� ��������� 2 ������� �������� � �������� ������� �� ��������� ��������� 
	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // ������� � ���� 0 �� ���� lID (ID)
		COLUMN_ENTRY(1, m_recPhoneNumber.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // ������� � ���� 1 �� ���������� ������
		COLUMN_ENTRY(2, m_recPhoneNumber.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneNumber.szPhoneNumber)
		COLUMN_ENTRY(4, m_recPhoneNumber.lPhoneTypeID)
		COLUMN_ENTRY(5, m_recPhoneNumber.lPersonID)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

/// <summary>
/// �������� ���� �� ������� PHONE_NUMBERS
/// ��������� CBaseTable, ���� �������� �������� �����, � ����� �������� �� ������� ���� �� �������
/// </summary>
class CPhoneNumbersTable : public CBaseTable<CPhoneNumbersAccessor, PHONE_NUMBERS>
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� �����������, ������� �� ������� �� ������� ���� �� ��� �� ������� �������� "PHONE_NUMBERS" </summary>
	CPhoneNumbersTable();

	/// <summary> ����������� �����������, ������� ���� �������� �����, ������� �� ������� �� ������� ���� �� ��� �� ������� �������� "PHONE_NUMBERS" </summary>
	/// <param name="oSession"> ���� �������� �����, ����� �������� ���� �� ������� �� ���� ������-�������� ��� ����� </param>
	CPhoneNumbersTable(CSession& oSession);

	/// <summary> ����������� �� ���������� </summary>
	~CPhoneNumbersTable();


// Overrides
// ----------------
protected:
	/// <summary> ����� �� ���������� �� ������� �� ��������, � ����� �� ��������� ������ ������������ ��� �� RowSet-� </summary>
	/// <returns> ����� ���������� ��� ������� �� �������� </returns>
	PHONE_NUMBERS& GetAccessorData();

	/// <summary> ����� �� ��������� �� ������� �� ��������� �����-�����, ����� ����� ������ �� Update Counter </summary>
	/// <param name="recObject"> ���������� ��� �����, ����� Update Counter �� ���� ������ </param>
	/// <returns> ����� ���� ����, � ����� ����������� ��� � ��� �������� </returns>
	const long* GetUpdateCounter(const PHONE_NUMBERS& recObject);
};