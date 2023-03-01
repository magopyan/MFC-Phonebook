// PersonsTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor

/// <summary>
/// ������� �� ������� ��������� PERSONS. ���� �������� �� ������� �������� ����
/// </summary>
class CPersonsAccessor
{
protected:
	/// <summary> ����� �� ��������� ��������� PERSONS, � ����� �� ������ ��������� </summary>
	PERSONS m_recPerson;

	// ����� ��������� 2 ������� �������� � �������� ������� �� ��������� ��������� 
	BEGIN_ACCESSOR_MAP(CPersonsAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // ������� � ���� 0 �� ���� lID (ID)
		COLUMN_ENTRY(1, m_recPerson.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // ������� � ���� 1 �� ���������� ������
		COLUMN_ENTRY(2, m_recPerson.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPerson.szFirstName)
		COLUMN_ENTRY(4, m_recPerson.szSecondName)
		COLUMN_ENTRY(5, m_recPerson.szThirdName)
		COLUMN_ENTRY(6, m_recPerson.szEGN)
		COLUMN_ENTRY(7, m_recPerson.szAdress)
		COLUMN_ENTRY(8, m_recPerson.lCityID)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

/// <summary>
/// �������� ���� �� ������� PERSONS
/// ��������� CBaseTable, ���� �������� �������� �����, � ����� �������� �� ������� ���� �� �������
/// </summary>
class CPersonsTable : public CBaseTable<CPersonsAccessor, PERSONS>
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� �����������, ������� �� ������� �� ��� �� ��������� �� ������� ���� �������� "PERSONS" </summary>
	CPersonsTable();

	/// <summary> ����������� �����������, ������� �������� ����� � ������� �� ������� �� ������� ���� �� ��� �� ������� �������� "PERSONS" </summary>
	/// <param name="oSession"> ���� �������� �����, ����� �������� ���� �� ������� �� ���� ������-�������� ��� ����� </param>
	CPersonsTable(CSession& oSession);

	/// <summary> ����������� �� ���������� </summary>
	~CPersonsTable();


// Overrides
// ----------------

protected:
	/// <summary> ����� �� ���������� �� ������� �� ��������, � ����� �� ��������� ������ ������������ ��� �� RowSet-� </summary>
	/// <returns> ����� ���������� ��� ������� �� �������� </returns>
	PERSONS& GetAccessorData();

	/// <summary> ����� �� ��������� �� ������� �� ��������� �����-������, ����� ����� ������ �� Update Counter </summary>
	/// <param name="recObject"> �����-������, ����� Update Counter �� ���� ������ </param>
	/// <returns> ����� ���� ����, � ����� ����������� ��� � ��� �������� </returns>
	const long* GetUpdateCounter(const PERSONS& recObject);
};
