// CitiesTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor

/// <summary>
/// Аксесор за дискова структура CITIES; Бива наследен от базовия табличен клас
/// </summary>
class CCitiesAccessor
{
protected:
	/// <summary> Обект от дисковата структура CITIES, с който ще работи аксесорът </summary>
	CITIES m_recCity;

	// Карта свързваща 2 отделни аксесора с различни мембъри на дисковата структура 
	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // Аксесор с ключ 0 за поле lID (ID)
		COLUMN_ENTRY(1, m_recCity.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // Аксесор с ключ 1 за останалите полета
		COLUMN_ENTRY(2, m_recCity.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCity.szCityName)
		COLUMN_ENTRY(4, m_recCity.szRegionName)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>
/// Табличен клас на таблица CITIES
/// Наследява CBaseTable, като дефинира типовете данни, с които методите на базовия клас ще работят
/// </summary>
class CCitiesTable : public CBaseTable<CCitiesAccessor, CITIES>
{

// Constructor / Destructor
// ----------------
public:
	/// <summary> Подразбиращ се конструктор. Задава на мембъра на базовия клас за име на таблица стойност "CITIES" </summary>
	CCitiesTable();

	/// <summary> Подразбиращ се деструктор </summary>
	~CCitiesTable();


// Overrides
// ----------------

protected:
	/// <summary> Метод за получаване на мембъра на аксесора, в който се съхранява текущо разглеждания ред от RowSet-а </summary>
	/// <returns> Връща референция към мембъра на аксесора </returns>
	CITIES& GetAccessorData();

	/// <summary> Метод за прочитане на мембъра от подадения обект-град, който играе ролята на Update Counter </summary>
	/// <param name="recObject"> Обект-град, чийто Update Counter да бъде върнат </param>
	/// <returns> Връща броят пъти, в които съответният ред е бил променян </returns>
	const long* GetUpdateCounter(const CITIES& recObject);
};