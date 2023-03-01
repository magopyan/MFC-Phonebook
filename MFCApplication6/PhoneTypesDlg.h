// PhoneTypesDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDlg

/// <summary> �������� ���� �� ������� PHONE_TYPES, ���� ����� �� ������ ��� ��� ��� �� ��������� ����������� ����� </summary>
class CPhoneTypesDlg : public CDialog
{

// Macros
// ----------------

DECLARE_DYNAMIC(CPhoneTypesDlg)
DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_TYPES_DIALOG };  // �������� ����������� �� ��� �������� ���� ���� ���� ������
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� ����������� </summary>
	/// <param name="recPhoneType"> ������� �� View ��� �����, ����� �� �� ������ � Edit Control-� ��� ��������������� �� ������� </param>
	/// <param name="pParent"> �������� ��� ����������� �������� </param>
	CPhoneTypesDlg(PHONE_TYPES& recPhoneType, CWnd* pParent = nullptr);

	/// <summary> ����������� �� ���������� </summary>
	virtual ~CPhoneTypesDlg();


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
	/// <summary> ������� ���������� ����� � �������-���������� ��� ��� ��������� ����� </summary>
	virtual void OnOK();

	/// <summary> ����� �� �������� �� ���������� �� ����������� ���� </summary>
	/// <returns> ��������� TRUE ��� �������� �������� ���� � FALSE ��� ������� �� ������ �������� � �������� �� (��)���������� ���� </returns>
	BOOL CheckInput();


// Members
// ----------------

private:
	/// <summary> ������, ������������ �� ������ EDB_PHONE_TYPE </summary>
	CEdit m_edbPhoneType;

	/// <summary> ���������� ��� ��� �����, � ����� �� ��������� ���������� � ������� ��� ��������� �� ����� "�����" </summary>
	PHONE_TYPES& m_recPhoneType;
};


