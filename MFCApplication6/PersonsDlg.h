// PersonsDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"
#include "PhoneNumbersDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDlg

/// <summary> �������� ���� �� ������� PERSONS, ���� ����� �� ������ ��� ������ ��� �� ��������� ����������� ����� </summary>
class CPersonsDlg : public CDialog
{

// Macros
// ----------------

	DECLARE_DYNAMIC(CPersonsDlg)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };  // �������� ����������� �� ��� �������� ���� ���� ���� ������; 
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� ����������� </summary>
	/// <param name="oPersonAndPhones"> ���������, ��������� ������ � �������� ������ </param>
	/// <param name="oCitiesMap"> ����� � ���������, ����� �� �� ������� � ComboBox </param>
	/// <param name="oPhoneTypesMap"> ����� � �������� ������, ����� �� �� ������� � ListCtrl � ComboBox �� CPhoneNumebersDlg  </param>
		/// <param name="pParent"> �������� ��� ����������� �������� </param>
	CPersonsDlg(CPerson& oPersonAndPhones, CCitiesMap& oCitiesMap, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent = nullptr);

	/// <summary> ����������� �� ���������� </summary>
	virtual ~CPersonsDlg();


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
	/// <summary> ������� ��������� ����� �������, ��������� � ������� �� ���������� �������� </summary>
	virtual void OnOK();

	/// <summary> �����, ���������� �� ��� ����� �����->Add. ��������� �������� �� ��� ��������� ����� ��� ������� </summary>
	virtual void OnAdd();

	/// <summary> �����, ���������� �� ��� ����� �����->Edit. ��������� ������������ �� ������ �� ������� ����� </summary>
	virtual void OnEdit();

	/// <summary> �����, ���������� �� ��� ����� �����->Delete. ����������� ��������� �� ������ �� ������� ����� </summary>
	virtual void OnDelete();

	/// <summary> �����, ��������� ���������� ���� ��� �������� ����� ����� � ������� �� ������� �� ��� ListCtrl </summary>
	/// <param name="pNMHDR"> �������� ��� ���������, ������ ���������� �� ����������� ��������� </param>
	/// <param name="pResult"> �������� ��� ���� �����, ��������� ��������� �������� </param>
	afx_msg void MenuOnRightClick(NMHDR* pNMHDR, LRESULT* pResult);

	/// <summary> ����� �� �������� �� ���������� �� ����������� ����� </summary>
	/// <returns> ��������� TRUE ��� �������� �������� ����� � FALSE ��� ���������� �������� </returns>
	BOOL CheckInput();


// Members
// ----------------

private:
	/// <summary> ������, ������������ �� ������ EDB_FIRST_NAME </summary>
	CEdit m_edbFirstName;
	
	/// <summary> ������, ������������ �� ������ EDB_SECOND_NAME </summary>
	CEdit m_edbSecondName;
	
	/// <summary> ������, ������������ �� ������ EDB_THIRD_NAME </summary>
	CEdit m_edbThirdName;
	
	/// <summary> ������, ������������ �� ������ EDB_EGN </summary>
	CEdit m_edbEGN;
	
	/// <summary> ������, ������������ �� ������ EDB_ADRESS </summary>
	CEdit m_edbAdress;
	
	/// <summary> ������, ������������ �� ������ CMB_CITY </summary>
	CComboBox m_cmbCity;

	/// <summary> ������, ������������ �� ������ LSC_PHONE_NUMBERS </summary>
	CListCtrl m_lscPhoneNumbers;

	/// <summary> ����� � ���������, ����� �� �������� � ComboBox </summary>
	CCitiesMap& m_oCitiesMap;

	/// <summary> ����� � �������� ������, ����� �� �������� � ListCtrl � ComboBox � ������� CPhoneNumbersDlg </summary>
	CPhoneTypesMap& m_oPhoneTypesMap;

	/// <summary> ���������, ����������� ������ � ����������� �� ������ </summary>
	CPerson& m_oPersonAndPhones;
};


