// CitiesTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor

/// <summary>
/// ������� �� ������� ��������� CITIES; ���� �������� �� ������� �������� ����
/// </summary>
class CCitiesAccessor
{
protected:
	/// <summary> ����� �� ��������� ��������� CITIES, � ����� �� ������ ��������� </summary>
	CITIES m_recCity;

	// ����� ��������� 2 ������� �������� � �������� ������� �� ��������� ��������� 
	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // ������� � ���� 0 �� ���� lID (ID)
		COLUMN_ENTRY(1, m_recCity.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // ������� � ���� 1 �� ���������� ������
		COLUMN_ENTRY(2, m_recCity.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCity.szCityName)
		COLUMN_ENTRY(4, m_recCity.szRegionName)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>
/// �������� ���� �� ������� CITIES
/// ��������� CBaseTable, ���� �������� �������� �����, � ����� �������� �� ������� ���� �� �������
/// </summary>
class CCitiesTable : public CBaseTable<CCitiesAccessor, CITIES>
{

// Constructor / Destructor
// ----------------
public:
	/// <summary> ����������� �� �����������. ������ �� ������� �� ������� ���� �� ��� �� ������� �������� "CITIES" </summary>
	CCitiesTable();

	/// <summary> ����������� �� ���������� </summary>
	~CCitiesTable();


// Overrides
// ----------------

protected:
	/// <summary> ����� �� ���������� �� ������� �� ��������, � ����� �� ��������� ������ ������������ ��� �� RowSet-� </summary>
	/// <returns> ����� ���������� ��� ������� �� �������� </returns>
	CITIES& GetAccessorData();

	/// <summary> ����� �� ��������� �� ������� �� ��������� �����-����, ����� ����� ������ �� Update Counter </summary>
	/// <param name="recObject"> �����-����, ����� Update Counter �� ���� ������ </param>
	/// <returns> ����� ����� ����, � ����� ����������� ��� � ��� �������� </returns>
	const long* GetUpdateCounter(const CITIES& recObject);
};