// PhoneNumbersDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDlg

/// <summary> �������� ���� �� ������� PHONE_NUMBERS, ���� ����� �� ������ ��� ��� ��� �� ��������� ����������� ����� </summary>
class CPhoneNumbersDlg : public CDialog
{

// Macros
// ----------------

DECLARE_DYNAMIC(CPhoneNumbersDlg)
DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_DIALOG };  // �������� ����������� �� ��� �������� ���� ���� ���� ������; 
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� ����������� </summary>
	/// <param name="recPhoneNumber"> ���������� ��� �����, ����� �� �� ������ � ������ �� ��������� ��� �������� ������� �� ����� </param>
	/// <param name="oPhoneTypesMap"> ���������� ��� �����, ��������� �������� ��������� ������, ����� �� �� ������� � ComboBox-� </param>
	/// <param name="pParent"> �������� ��� ����������� �������� </param>
	CPhoneNumbersDlg(PHONE_NUMBERS& recPhoneNumber, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent = nullptr);

	/// <summary> ����������� �� ���������� </summary>
	virtual ~CPhoneNumbersDlg();


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
	/// <summary> ������� ���������� ����� � �������-����� </summary>
	virtual void OnOK();

	/// <summary> ����� �� �������� �� ��������� �� ����������� ����� </summary>
	/// <returns> ��������� TRUE ��� �������� ������� ����� � FALSE ��� ������� �� ������ �������� � �������� �� ������ ��� �������� ��� </returns>
	BOOL CheckInput();


// Members
// ----------------

private:
	/// <summary> ������, ������������ �� ������ EDB_PHONE_NUMBER </summary>
	CEdit m_edbPhoneNumber;

	/// <summary> ������, ������������ �� ������ CMB_PHONE_TYPE </summary>
	CComboBox m_cmbPhoneType;

	/// <summary> ����� � ���� - ID-���� �� �������� ������ � �������� - ����� �� ��������� ��������� �� ��� ����� </summary>
	CPhoneTypesMap& m_oPhoneTypesMap;

	/// <summary> ������-��������� �����, � ����� �� ��������� ��������� � ������� ����� ��� ��������� �� ����� "�����" </summary>
	PHONE_NUMBERS& m_recPhoneNumber;
};


