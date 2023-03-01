// PhoneNumbersTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor

/// <summary>
/// Аксесор за дискова структура PHONE_NUMBERS; Бива наследен от базовия табличен клас
/// </summary>
class CPhoneNumbersAccessor
{
protected:
	/// <summary> Обект от дисковата структура PHONE_NUMBERS, с който ще работи аксесорът </summary>
	PHONE_NUMBERS m_recPhoneNumber;

	// Карта свързваща 2 отделни аксесора с различни мембъри на дисковата структура 
	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // Аксесор с ключ 0 за поле lID (ID)
		COLUMN_ENTRY(1, m_recPhoneNumber.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // Аксесор с ключ 1 за останалите полета
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
/// Табличен клас на таблица PHONE_NUMBERS
/// Наследява CBaseTable, като дефинира типовете данни, с които методите на базовия клас ще работят
/// </summary>
class CPhoneNumbersTable : public CBaseTable<CPhoneNumbersAccessor, PHONE_NUMBERS>
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор, задаващ на мембъра на базовия клас за име на таблица стойност "PHONE_NUMBERS" </summary>
	CPhoneNumbersTable();

	/// <summary> Експлицитен конструктор, приемащ вече отворена сесия, задаващ на мембъра на базовия клас за име на таблица стойност "PHONE_NUMBERS" </summary>
	/// <param name="oSession"> Вече отворена сесия, която базовият клас ще присвои на своя мембър-указател към сесия </param>
	CPhoneNumbersTable(CSession& oSession);

	/// <summary> Подразбиращ се деструктор </summary>
	~CPhoneNumbersTable();


// Overrides
// ----------------
protected:
	/// <summary> Метод за получаване на мембъра на аксесора, в който се съхранява текущо разглеждания ред от RowSet-а </summary>
	/// <returns> Връща референция към мембъра на аксесора </returns>
	PHONE_NUMBERS& GetAccessorData();

	/// <summary> Метод за прочитане на мембъра от подадения обект-номер, който играе ролята на Update Counter </summary>
	/// <param name="recObject"> Референция към номер, чийто Update Counter да бъде върнат </param>
	/// <returns> Връща броя пъти, в които съответният ред е бил променян </returns>
	const long* GetUpdateCounter(const PHONE_NUMBERS& recObject);
};