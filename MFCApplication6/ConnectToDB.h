// ConnectToDB.h
//

#pragma once
#include "atldbcli.h" // �� CDBPropSet � CDataSource


/////////////////////////////////////////////////////////////////////////////
// CConnectToDB

/// <summary> ����-Singleton �� ������������ �� ������ � ������ ����� PhoneBook </summary>
class CConnectToDB
{

// Constructor / Destructor
// ----------------

private:
	/// <summary> ����������� �� �����������  </summary>
	CConnectToDB();

	/// <summary> ����������� �� ����������  </summary>
	~CConnectToDB();
	

// Methods
// ----------------

public:
	/// <summary> �������� ����� �� ���������� �������������� �� ��������� ������-�������� ��� ����� </summary>
	/// <returns> ����� ������, ����� ���������� ������-�������� ���� </returns>
	static CConnectToDB* GetInstance();

	/// <summary> ����� �� ������ �� �������-����� �� ������ � �� </summary>
	/// <returns> ����� ���������� ��� �������-������ � ��  </returns>
	CDataSource& GetDataSource();

	/// <summary> ����� �� ������������ �� ������ � �� </summary>
	/// <returns> ����� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL OpenConnection();

	/// <summary> ����� �� ������� �� �������� � ��, ���� �� ���� ��� �� � �������� ���������� �� ������ UPDATE, INSERT � DELETE </summary>
	/// <param name="oUpdateDBPropSet"> ������ ������������� ����� �� CDBPropSet, ����� ������ �� ���� ����������� </param>
	void UpdateDBPropSet(CDBPropSet& oUpdateDBPropSet);


// Members
// ----------------

private:
	/// <summary> �����-������ � �� </summary>
	CDataSource m_oConnection;

	/// <summary> �������� �������� ��� ����������� ����� �� ������ � �� </summary>
	static CConnectToDB* _pInstance;
};

