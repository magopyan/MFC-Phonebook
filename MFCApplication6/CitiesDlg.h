// CitiesDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

/// <summary> �������� ���� �� ������� CITIES, ���� ����� �� ������ ��� ��� ��� �� ��������� ����������� ����� </summary>
class CCitiesDlg : public CDialog
{

// Macros
// ----------------

	DECLARE_DYNAMIC(CCitiesDlg) 
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_DIALOG };  // �������� ����������� �� ��� �������� ���� ���� ���� ������
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� ����������� </summary>
	/// <param name="recCity"> ������� �� View ����, ����� ����� �� �� ������� � Edit Control-��� ��� ������������� �� ������� </param>
	/// <param name="pParent"> �������� ��� ����������� �������� </param>
	CCitiesDlg(CITIES& recCity, CWnd* pParent = nullptr);

	/// <summary> ����������� �� ���������� </summary>
	virtual ~CCitiesDlg();


// MFC Overrides
// ----------------

private:
	/// <summary> ������� ��������� �� ���������� �������� ��� ����������� �� ������� </summary>
	void DoDataExchange(CDataExchange* pDX) override;


// Overrides
// ----------------

	/// <summary> ������������ ������� � �������� ��������, ���������� �� �� ������ </summary>
	virtual BOOL OnInitDialog(); 


// Methods
// ----------------

private:
	/// <summary> ������� ���������� ����� � �������-���� </summary>
	virtual void OnOK();

	/// <summary> ����� �� �������� �� ���������� �� ����������� ���� </summary>
	/// <returns> ��������� TRUE ��� �������� �������� ����� � FALSE ��� ������� �� ������ �������� � �������� �� (��)�������� ���� </returns>
	const BOOL CheckInput() const;
	

// Members
// ----------------

private:
	/// <summary> ������, ������������ �� ������ EDB_CITY_NAME </summary>
	CEdit m_edbCityName;

	/// <summary> ������, ������������ �� ������ EDB_REGION_NAME </summary>
	CEdit m_edbRegionName;

	/// <summary> ���������� ��� ����, ����������� ���������� ��������� </summary>
	CITIES& m_recCity;
};

