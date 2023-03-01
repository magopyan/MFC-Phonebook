// PhoneTypesData.h
//

#pragma once
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData


/// <summary>
/// Клас с бизнес логиката на таблица PHONE_TYPES
/// </summary>
class CPhoneTypesData
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор </summary>
	CPhoneTypesData();

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPhoneTypesData();


// Methods
// ----------------

public:
	/// <summary> Метод за четене на всички редове от таблица PHONE_TYPES от БД, като те се запазват в масива-параметър </summary>
	/// <param name="oPhoneTypesArray"> Масив от указатели, в който ще се съхранят прочетените от БД редове </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL SelectAll(CPhoneTypesArray& oPhoneTypesArray);

	/// <summary> Метод за четене от БД само на реда с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде прочетен </param>
	/// <param name="recPhoneType"> Референция към обект-вид номер, в чийто мембъри ще се запазят данните от прочетения ред </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL SelectWhereID(const long lID, PHONE_TYPES& recPhoneType);

	/// <summary> Метод за промяна на данните в редa от БД с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде променен </param>
	/// <param name="recPhoneType"> Референция към обект-вид номер, с чийто мембъри ще се заменят данните за реда с подаденото ID </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType);

	/// <summary> Метод за добавяне на нов ред към таблицата и извличане на генерираното за него от SQL ID </summary>
	/// <param name="recPhoneType"> Референция към обект-вид номер, който ще бъде добавен като нов ред и ще приеме генерираното му от SQL ID </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL Insert(PHONE_TYPES& recPhoneType);

	/// <summary> Метод за изтриване на ред с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде изтрит </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL DeleteWhereID(const long lID);
};
