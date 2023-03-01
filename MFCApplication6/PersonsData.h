// PersonsData.h
//

#pragma once
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsData


/// <summary>
/// ���� � ����������� ������ ������ �� ������� PERSONS � PHONE_NUMBERS
/// </summary>
class CPersonsData
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� ����������� </summary>
	CPersonsData();

	/// <summary> ����������� �� ���������� </summary>
	virtual ~CPersonsData();


// Methods
// ----------------

private:
	/// <summary> ����� �� �������������� �� ����� </summary>
	/// <param name="oSession"> �����-�����, ����� �� ���� �������������� </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL OpenSession(CSession& oSession);

	/// <summary> ����� �� �������� �� ������������ �� ������ SQL ������ </summary>
	/// <param name="lHResult"> ������� ��������� �� ����������� ������ </param>
	/// <param name="oSession"> �������� ���� �������� ����� </param>
	/// <param name="strQuery"> �������� ��� ����� �� �������� ��� </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������  </returns>
	BOOL CheckQueryResult(const HRESULT& lHResult, CSession& oSession, const CString& strQuery);


public:
	/// <summary> ����� �� �������� �� ������ ������ �� ������� PERSONS, ���� �� �� �������� � ������-��������� </summary>
	/// <param name="oPersonsArray"> ����� �� �������, � ����� �� �� �������� ����������� �� �� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL SelectAllPersons(CPersonsArray& oPersonsArray);

	/// <summary> ����� �� �������� �� �� �� ����������� ������, ������������ �� ��������� ������ </summary>
	/// <param name="lID"> ID �� �������, ����� ������ �� �� ������� </param>
	/// <param name="oPhoneNumbersArray"> ����� �� ������, � ����� �� �� �������� �������� �� ������� </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL GetPersonsNumbers(const long& lID, CPhoneNumbersArray& oPhoneNumbersArray);


	/// <summary> ����� �� �������� �� ��� ������ � �������� ��������� ������ </summary>
	/// <param name="oPersonAndPhones"> ���������, ��������� ������� � ����������� �� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL InsertPersonAndPhones(CPerson& oPersonAndPhones);

	/// <summary> ����� �� ������� �� ������� �� ����� ������ � ����������� �� ������ </summary>
	/// <param name="oPersonAndPhones"> ���������, ��������� ��������� ������ � �������� �� </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL UpdatePersonAndPhones(CPerson& oPersonAndPhones);

	/// <summary> ����� �� ��������� �� ������ � ���������� ID � �������� �� ������ </summary>
	/// <param name="lID"> ID �� �������, ����� ������ �� ���� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL DeletePersonWhereID(const long& lID);
};

