#pragma once
#include "TypedPtrArrayAutoDelete.h" 


/* Дефиниране на размери на символните масиви от тип TCHAR, които са мембъри в дисковите структури 
и съответстват на зададените в БД размери за съответната колона */

#define CITYNAMESIZE 64 // за szCityName(в БД: CITY_NAME) от таблица / дискова структура CITIES
#define REGIONNAMESIZE 128 // за szRegionName (в БД: REGION_NAME) от таблица / дискова структура CITIES
#define FIRSTNAMESIZE 64 // за szFirstName (в БД: FIRST_NAME) от таблица / дискова структура PERSONS
#define SECONDNAMESIZE 64 // за szSecondName (в БД: SECOND_NAME) от таблица / дискова структура PERSONS
#define THIRDNAMESIZE 64  // за szThirdName (в БД: THIRD_NAME) от таблица / дискова структура PERSONS
#define EGNSIZE 32 // за szEGN (в БД: EGN) от таблица / дискова структура PERSONS
#define ADRESSSIZE 128 // за szAdress (в БД: ADRESS) от таблица / дискова структура PERSONS
#define PHONETYPESIZE 64 // за szPhoneType (в БД: PHONE_TYPE) от таблица / дискова структура PHONE_TYPES
#define PHONENUMBERSIZE 32 // за szPhoneNumber (в БД: PHONE_NUMBER) от таблица / дискова структура PHONE_NUMBERS


/// <summary>
/// Структура, описваща ред от таблица CITIES
/// </summary>
struct CITIES 
{
	/// <summary> Идентификатор на град  </summary>
	long lID;

	/// <summary> Брояч на промените в реда </summary>
	long lUpdateCounter;

	/// <summary> Име на град </summary>
	TCHAR szCityName[CITYNAMESIZE];

	/// <summary> Име на област, в която се намира градът </summary>
	TCHAR szRegionName[REGIONNAMESIZE];

	/// <summary> Подразбиращ се конструктор, който нулира мембърите при създаването на всеки обект </summary>
	CITIES() 
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
/// Структура, описваща ред от таблица PERSONS
/// </summary>
struct PERSONS 
{
	/// <summary> Идентификатор на абонат </summary>
	long lID;

	/// <summary> Брояч на промените в реда </summary>
	long lUpdateCounter;

	/// <summary> Име </summary>
	TCHAR szFirstName[FIRSTNAMESIZE];

	/// <summary> Презиме </summary>
	TCHAR szSecondName[SECONDNAMESIZE];

	/// <summary> Фамилия </summary>
	TCHAR szThirdName[THIRDNAMESIZE];

	/// <summary> ЕГН </summary>
	TCHAR szEGN[EGNSIZE];

	/// <summary> Адрес </summary>
	TCHAR szAdress[ADRESSSIZE];

	/// <summary> Идентификатор на град </summary>
	long lCityID;

	/// <summary> Подразбиращ се конструктор, който нулира мембърите при създаването на всеки обект </summary>
	PERSONS() 
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
/// Структура, описваща ред от таблица PHONE_TYPES
/// </summary>
struct PHONE_TYPES 
{
	/// <summary> Идентификатор на тип телефонен номер </summary>
	long lID;

	/// <summary> Брояч на промените в реда </summary>
	long lUpdateCounter;

	/// <summary> Вид на телефонния номер </summary>
	TCHAR szPhoneType[PHONETYPESIZE];

	/// <summary> Подразбиращ се конструктор, който нулира мембърите при създаването на всеки обект </summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};



/// <summary>
/// Структура, описваща ред от таблица PHONE_NUMBERS
/// </summary>
struct PHONE_NUMBERS 
{
	/// <summary> Идентификатор на телефонен номер </summary>
	long lID;

	/// <summary> Брояч на промените в реда </summary>
	long lUpdateCounter;

	/// <summary> Телефонен номер </summary>
	TCHAR szPhoneNumber[PHONENUMBERSIZE];

	/// <summary> Идентификатор на тип телефонен номер </summary>
	long lPhoneTypeID;

	/// <summary> Идентификатор на абонат </summary>
	long lPersonID;

	/// <summary> Подразбиращ се конструктор, който нулира мембърите при създаването на всеки обект </summary>
	PHONE_NUMBERS() 
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/* Задаване на имена на шаблонни типове: CCities-, CPersons-, CPhoneTypes- и CPhoneNumbersArray,
   за които ще се подразбира, че са масиви от клас CTypedPtrArrayAutoDelete от указатели, 
   сочещи обекти съответно от тип CITIES, PERSONS, PHONE_TYPES или PHONE_NUMBERS */
typedef CTypedPtrArrayAutoDelete<CITIES> CCitiesArray;
typedef CTypedPtrArrayAutoDelete<PERSONS> CPersonsArray;
typedef CTypedPtrArrayAutoDelete<PHONE_TYPES> CPhoneTypesArray;
typedef CTypedPtrArrayAutoDelete<PHONE_NUMBERS> CPhoneNumbersArray;

/* Шаблонни CMap, с ключ-цяло число (където ще се съхранява идентификатора на даден ред) 
   и стойност-обект от дисковата структура, съответстваща на ред от съответната таблица */
typedef CMap<long, long, CITIES, CITIES&> CCitiesMap;
typedef CMap<long, long, PHONE_TYPES, PHONE_TYPES&> CPhoneTypesMap;


/// <summary>
/// Клас, окомплектоващ абонат с неговите телефонни номера
/// </summary>
class CPerson
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор </summary>
	CPerson()
	{
		m_recPerson = PERSONS();
	}

	/// <summary> Подразбиращ се деструктор </summary>
	~CPerson()
	{

	}


// Members
// ----------------

	/// <summary> Обект от дисковата структура PERSONS (абонат) </summary>
	PERSONS m_recPerson;

	/// <summary> Масив, съдържащ указатели към PHONE_NUMBERS (телефонните номера на абоната) </summary>
	CPhoneNumbersArray m_oPhoneNumbers;
};


