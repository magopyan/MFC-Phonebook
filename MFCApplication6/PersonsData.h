// PersonsData.h
//

#pragma once
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsData


/// <summary>
/// Клас с обединената бизнес логика на таблици PERSONS и PHONE_NUMBERS
/// </summary>
class CPersonsData
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор </summary>
	CPersonsData();

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPersonsData();


// Methods
// ----------------

private:
	/// <summary> Метод за инициализиране на сесия </summary>
	/// <param name="oSession"> Обект-сесия, която да бъде инициализирана </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL OpenSession(CSession& oSession);

	/// <summary> Метод за проверка на изпълнението на дадена SQL заявка </summary>
	/// <param name="lHResult"> Съдържа резултата от изпълнената заявка </param>
	/// <param name="oSession"> Подадена вече отворена сесия </param>
	/// <param name="strQuery"> Заявката под форма на символен низ </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL CheckQueryResult(const HRESULT& lHResult, CSession& oSession, const CString& strQuery);


public:
	/// <summary> Метод за изчитане на всички редове от таблица PERSONS, като те се записват в масива-параметър </summary>
	/// <param name="oPersonsArray"> Масив от абонати, в който ще се съхранят прочетените от БД редове </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL SelectAllPersons(CPersonsArray& oPersonsArray);

	/// <summary> Метод за изчитане от БД на телефонните номера, принадлежящи на определен абонат </summary>
	/// <param name="lID"> ID на абоната, чиито номера да се изчетат </param>
	/// <param name="oPhoneNumbersArray"> Масив от номера, в който да се съхранят номерата на абоната </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL GetPersonsNumbers(const long& lID, CPhoneNumbersArray& oPhoneNumbersArray);


	/// <summary> Метод за добавяне на нов абонат и неговите телефонни номера </summary>
	/// <param name="oPersonAndPhones"> Структура, съдържаща абоната и телефонните му номера </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL InsertPersonAndPhones(CPerson& oPersonAndPhones);

	/// <summary> Метод за промяна на данните за даден абонат и телефонните му номера </summary>
	/// <param name="oPersonAndPhones"> Структура, съдържаща изменения абонат и номерата му </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL UpdatePersonAndPhones(CPerson& oPersonAndPhones);

	/// <summary> Метод за изтриване на абонат с определено ID и всичките му номера </summary>
	/// <param name="lID"> ID на абоната, който трябва да бъде изтрит </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL DeletePersonWhereID(const long& lID);
};

