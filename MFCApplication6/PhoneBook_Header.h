#pragma once
#include "TypedPtrArrayAutoDelete.h" 


/* ���������� �� ������� �� ���������� ������ �� ��� TCHAR, ����� �� ������� � ��������� ��������� 
� ������������ �� ���������� � �� ������� �� ����������� ������ */

#define CITYNAMESIZE 64 // �� szCityName(� ��: CITY_NAME) �� ������� / ������� ��������� CITIES
#define REGIONNAMESIZE 128 // �� szRegionName (� ��: REGION_NAME) �� ������� / ������� ��������� CITIES
#define FIRSTNAMESIZE 64 // �� szFirstName (� ��: FIRST_NAME) �� ������� / ������� ��������� PERSONS
#define SECONDNAMESIZE 64 // �� szSecondName (� ��: SECOND_NAME) �� ������� / ������� ��������� PERSONS
#define THIRDNAMESIZE 64  // �� szThirdName (� ��: THIRD_NAME) �� ������� / ������� ��������� PERSONS
#define EGNSIZE 32 // �� szEGN (� ��: EGN) �� ������� / ������� ��������� PERSONS
#define ADRESSSIZE 128 // �� szAdress (� ��: ADRESS) �� ������� / ������� ��������� PERSONS
#define PHONETYPESIZE 64 // �� szPhoneType (� ��: PHONE_TYPE) �� ������� / ������� ��������� PHONE_TYPES
#define PHONENUMBERSIZE 32 // �� szPhoneNumber (� ��: PHONE_NUMBER) �� ������� / ������� ��������� PHONE_NUMBERS


/// <summary>
/// ���������, �������� ��� �� ������� CITIES
/// </summary>
struct CITIES 
{
	/// <summary> ������������� �� ����  </summary>
	long lID;

	/// <summary> ����� �� ��������� � ���� </summary>
	long lUpdateCounter;

	/// <summary> ��� �� ���� </summary>
	TCHAR szCityName[CITYNAMESIZE];

	/// <summary> ��� �� ������, � ����� �� ������ ������ </summary>
	TCHAR szRegionName[REGIONNAMESIZE];

	/// <summary> ����������� �� �����������, ����� ������ ��������� ��� ����������� �� ����� ����� </summary>
	CITIES() 
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
/// ���������, �������� ��� �� ������� PERSONS
/// </summary>
struct PERSONS 
{
	/// <summary> ������������� �� ������ </summary>
	long lID;

	/// <summary> ����� �� ��������� � ���� </summary>
	long lUpdateCounter;

	/// <summary> ��� </summary>
	TCHAR szFirstName[FIRSTNAMESIZE];

	/// <summary> ������� </summary>
	TCHAR szSecondName[SECONDNAMESIZE];

	/// <summary> ������� </summary>
	TCHAR szThirdName[THIRDNAMESIZE];

	/// <summary> ��� </summary>
	TCHAR szEGN[EGNSIZE];

	/// <summary> ����� </summary>
	TCHAR szAdress[ADRESSSIZE];

	/// <summary> ������������� �� ���� </summary>
	long lCityID;

	/// <summary> ����������� �� �����������, ����� ������ ��������� ��� ����������� �� ����� ����� </summary>
	PERSONS() 
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
/// ���������, �������� ��� �� ������� PHONE_TYPES
/// </summary>
struct PHONE_TYPES 
{
	/// <summary> ������������� �� ��� ��������� ����� </summary>
	long lID;

	/// <summary> ����� �� ��������� � ���� </summary>
	long lUpdateCounter;

	/// <summary> ��� �� ���������� ����� </summary>
	TCHAR szPhoneType[PHONETYPESIZE];

	/// <summary> ����������� �� �����������, ����� ������ ��������� ��� ����������� �� ����� ����� </summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};



/// <summary>
/// ���������, �������� ��� �� ������� PHONE_NUMBERS
/// </summary>
struct PHONE_NUMBERS 
{
	/// <summary> ������������� �� ��������� ����� </summary>
	long lID;

	/// <summary> ����� �� ��������� � ���� </summary>
	long lUpdateCounter;

	/// <summary> ��������� ����� </summary>
	TCHAR szPhoneNumber[PHONENUMBERSIZE];

	/// <summary> ������������� �� ��� ��������� ����� </summary>
	long lPhoneTypeID;

	/// <summary> ������������� �� ������ </summary>
	long lPersonID;

	/// <summary> ����������� �� �����������, ����� ������ ��������� ��� ����������� �� ����� ����� </summary>
	PHONE_NUMBERS() 
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/* �������� �� ����� �� �������� ������: CCities-, CPersons-, CPhoneTypes- � CPhoneNumbersArray,
   �� ����� �� �� ����������, �� �� ������ �� ���� CTypedPtrArrayAutoDelete �� ���������, 
   ������ ������ ��������� �� ��� CITIES, PERSONS, PHONE_TYPES ��� PHONE_NUMBERS */
typedef CTypedPtrArrayAutoDelete<CITIES> CCitiesArray;
typedef CTypedPtrArrayAutoDelete<PERSONS> CPersonsArray;
typedef CTypedPtrArrayAutoDelete<PHONE_TYPES> CPhoneTypesArray;
typedef CTypedPtrArrayAutoDelete<PHONE_NUMBERS> CPhoneNumbersArray;

/* �������� CMap, � ����-���� ����� (������ �� �� ��������� �������������� �� ����� ���) 
   � ��������-����� �� ��������� ���������, ������������� �� ��� �� ����������� ������� */
typedef CMap<long, long, CITIES, CITIES&> CCitiesMap;
typedef CMap<long, long, PHONE_TYPES, PHONE_TYPES&> CPhoneTypesMap;


/// <summary>
/// ����, ������������� ������ � �������� ��������� ������
/// </summary>
class CPerson
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� ����������� </summary>
	CPerson()
	{
		m_recPerson = PERSONS();
	}

	/// <summary> ����������� �� ���������� </summary>
	~CPerson()
	{

	}


// Members
// ----------------

	/// <summary> ����� �� ��������� ��������� PERSONS (������) </summary>
	PERSONS m_recPerson;

	/// <summary> �����, �������� ��������� ��� PHONE_NUMBERS (����������� ������ �� �������) </summary>
	CPhoneNumbersArray m_oPhoneNumbers;
};


