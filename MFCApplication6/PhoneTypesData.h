// PhoneTypesData.h
//

#pragma once
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData


/// <summary>
/// ���� � ������ �������� �� ������� PHONE_TYPES
/// </summary>
class CPhoneTypesData
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� ����������� </summary>
	CPhoneTypesData();

	/// <summary> ����������� �� ���������� </summary>
	virtual ~CPhoneTypesData();


// Methods
// ----------------

public:
	/// <summary> ����� �� ������ �� ������ ������ �� ������� PHONE_TYPES �� ��, ���� �� �� �������� � ������-��������� </summary>
	/// <param name="oPhoneTypesArray"> ����� �� ���������, � ����� �� �� �������� ����������� �� �� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL SelectAll(CPhoneTypesArray& oPhoneTypesArray);

	/// <summary> ����� �� ������ �� �� ���� �� ���� � ���������� ID </summary>
	/// <param name="lID"> ID �� ����, ����� ������ �� ���� �������� </param>
	/// <param name="recPhoneType"> ���������� ��� �����-��� �����, � ����� ������� �� �� ������� ������� �� ���������� ��� </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL SelectWhereID(const long lID, PHONE_TYPES& recPhoneType);

	/// <summary> ����� �� ������� �� ������� � ���a �� �� � ���������� ID </summary>
	/// <param name="lID"> ID �� ����, ����� ������ �� ���� �������� </param>
	/// <param name="recPhoneType"> ���������� ��� �����-��� �����, � ����� ������� �� �� ������� ������� �� ���� � ���������� ID </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType);

	/// <summary> ����� �� �������� �� ��� ��� ��� ��������� � ��������� �� ������������ �� ���� �� SQL ID </summary>
	/// <param name="recPhoneType"> ���������� ��� �����-��� �����, ����� �� ���� ������� ���� ��� ��� � �� ������ ������������ �� �� SQL ID </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL Insert(PHONE_TYPES& recPhoneType);

	/// <summary> ����� �� ��������� �� ��� � ���������� ID </summary>
	/// <param name="lID"> ID �� ����, ����� ������ �� ���� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL DeleteWhereID(const long lID);
};
