// CitiesData.h
//

#pragma once
#include "CitiesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData


/// <summary>
/// Клас с бизнес логиката за таблица CITIES
/// </summary>
class CCitiesData 
{

// Constructor / Destructor
// ----------------
public:
	/// <summary> Подразбиращ се конструктор </summary>
	CCitiesData();

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CCitiesData();


// Methods
// ----------------
public:
	/// <summary> Метод за четене на всички редове от таблица CITIES от БД, като те се запазват в масива-параметър </summary>
	/// <param name="oCitiesArray"> Масив от указатели, в който ще се съхранят прочетените от БД редове </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL SelectAll(CCitiesArray& oCitiesArray);

	/// <summary> Метод за четене от БД само на реда с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде прочетен </param>
	/// <param name="recCities"> Референция към обект-град, в чийто мембъри ще се запазят данните от прочетения ред </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL SelectWhereID(const long lID, CITIES& recCities);

	/// <summary> Метод за промяна на данните в редa от БД с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде променен </param>
	/// <param name="recCities"> Референция към обект-град, с чийто мембъри ще се заменят данните за реда с подаденото ID </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);

	/// <summary> Метод за добавяне на нов ред към таблицата и извличане на генерираното за него от SQL ID </summary>
	/// <param name="recCities"> Референция към обект-град, който ще бъде добавен като нов ред и ще приеме генерираното му от SQL ID </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL Insert(CITIES& recCities);

	/// <summary> Метод за изтриване на ред с определено ID </summary>
	/// <param name="lID"> ID на реда, който трябва да бъде изтрит </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL DeleteWhereID(const long lID);
};
