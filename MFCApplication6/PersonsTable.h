// PersonsTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor

/// <summary>
/// Аксесор за дискова структура PERSONS. Бива наследен от базовия табличен клас
/// </summary>
class CPersonsAccessor
{
protected:
	/// <summary> Обект от дисковата структура PERSONS, с който ще работи аксесорът </summary>
	PERSONS m_recPerson;

	// Карта свързваща 2 отделни аксесора с различни мембъри на дисковата структура 
	BEGIN_ACCESSOR_MAP(CPersonsAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // Аксесор с ключ 0 за поле lID (ID)
		COLUMN_ENTRY(1, m_recPerson.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // Аксесор с ключ 1 за останалите полета
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
/// Табличен клас на таблица PERSONS
/// Наследява CBaseTable, като дефинира типовете данни, с които методите на базовия клас ще работят
/// </summary>
class CPersonsTable : public CBaseTable<CPersonsAccessor, PERSONS>
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор, задаващ на мембъра за име на таблицата на базовия клас стойност "PERSONS" </summary>
	CPersonsTable();

	/// <summary> Експлицитен конструктор, приемащ отворена сесия и задаващ на мембъра на базовия клас за име на таблица стойност "PERSONS" </summary>
	/// <param name="oSession"> Вече отворена сесия, която базовият клас ще присвои на своя мембър-указател към сесия </param>
	CPersonsTable(CSession& oSession);

	/// <summary> Подразбиращ се деструктор </summary>
	~CPersonsTable();


// Overrides
// ----------------

protected:
	/// <summary> Метод за получаване на мембъра на аксесора, в който се съхранява текущо разглеждания ред от RowSet-а </summary>
	/// <returns> Връща референция към мембъра на аксесора </returns>
	PERSONS& GetAccessorData();

	/// <summary> Метод за прочитане на мембъра от подадения обект-абонат, който играе ролята на Update Counter </summary>
	/// <param name="recObject"> Обект-абонат, чийто Update Counter да бъде върнат </param>
	/// <returns> Връща броя пъти, в които съответният ред е бил променян </returns>
	const long* GetUpdateCounter(const PERSONS& recObject);
};
