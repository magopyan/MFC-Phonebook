// PhoneTypesTable.h
//

#pragma once
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesAccessor

/// <summary>
/// Аксесор за дискова структура PHONE_TYPES; Бива наследен от базовия табличен клас
/// </summary>
class CPhoneTypesAccessor
{
protected:
	/// <summary> Обект от дисковата структура PHONE_TYPES, с който ще работи аксесорът </summary>
	PHONE_TYPES m_recPhoneType;

	// Карта свързваща 2 отделни аксесора с различни мембъри на дисковата структура 
	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)

		BEGIN_ACCESSOR(eAccessorID, true)  // Аксесор с ключ 0 за поле lID (ID)
		COLUMN_ENTRY(1, m_recPhoneType.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(eAccessorAllOtherColumns, true)  // Аксесор с ключ 1 за останалите полета
		COLUMN_ENTRY(2, m_recPhoneType.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneType.szPhoneType)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

/// <summary>
/// Табличен клас на таблица PHONE_TYPES
/// Наследява CBaseTable, като дефинира типовете данни, с които методите на базовия клас ще работят
/// </summary>
class CPhoneTypesTable : public CBaseTable<CPhoneTypesAccessor, PHONE_TYPES>
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор. Задава на мембъра на базовия клас за име на таблицата стойност "PHONE_TYPES" </summary>
	CPhoneTypesTable();

	/// <summary> Подразбиращ се деструктор </summary>
	~CPhoneTypesTable();


// Overrides
// ----------------

protected:
	/// <summary> Метод за получаване на мембъра на аксесора, в който се съхранява текущо разглеждания ред от RowSet-а </summary>
	/// <returns> Връща референция към мембъра на аксесора </returns>
	PHONE_TYPES& GetAccessorData();

	/// <summary> Метод за прочитане на мембъра от подадения обект-вид номер, който играе ролята на Update Counter </summary>
	/// <param name="recObject"> Обект-вид номер, чийто Update Counter да бъде върнат </param>
	/// <returns> Връща броят пъти, в които съответният ред е бил променян </returns>
	const long* GetUpdateCounter(const PHONE_TYPES& recObject);
}; 
