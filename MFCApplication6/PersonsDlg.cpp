// PersonsDlg.cpp
//

#include "pch.h"
#include "Resource.h"
#include "MFCApplication6.h"
#include "PhoneBook_Header.h"
#include "PersonsDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDlg

enum eColumns { eColumnsNumber = 0, eColumnsType = 1 };

enum eColumnsWidth { eColumnsWidthNumber = 200, eColumnsWidthType = 200 };

#define NO_SUBITEM -1

IMPLEMENT_DYNAMIC(CPersonsDlg, CDialog)

BEGIN_MESSAGE_MAP(CPersonsDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPersonsDlg::OnOK)
	
	ON_NOTIFY(NM_RCLICK, LSC_PHONE_NUMBERS, &CPersonsDlg::MenuOnRightClick)
	ON_COMMAND(ID_ADD, &CPersonsDlg::OnAdd)
	ON_COMMAND(ID_EDIT, &CPersonsDlg::OnEdit)
	ON_COMMAND(ID_REMOVE, &CPersonsDlg::OnDelete)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPersonsDlg::CPersonsDlg(CPerson& oPersonAndPhones, CCitiesMap& oCitiesMap, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent) : CDialog(IDD_PERSONS_DIALOG, pParent),
m_oPersonAndPhones(oPersonAndPhones), m_oCitiesMap(oCitiesMap), m_oPhoneTypesMap(oPhoneTypesMap)
{

}

CPersonsDlg::~CPersonsDlg()
{

}


// MFC Overrides
// ----------------

void CPersonsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, EDB_FIRST_NAME, m_edbFirstName);
	DDX_Control(pDX, EDB_SECOND_NAME, m_edbSecondName);
	DDX_Control(pDX, EDB_THIRD_NAME, m_edbThirdName);
	DDX_Control(pDX, EDB_EGN, m_edbEGN);
	DDX_Control(pDX, EDB_ADRESS, m_edbAdress);
	DDX_Control(pDX, CMB_CITY, m_cmbCity);
	DDX_Control(pDX, LSC_PHONE_NUMBERS, m_lscPhoneNumbers);
}


// Methods
// ----------------

BOOL CPersonsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edbFirstName.SetLimitText(FIRSTNAMESIZE);
	m_edbSecondName.SetLimitText(SECONDNAMESIZE);
	m_edbThirdName.SetLimitText(THIRDNAMESIZE);
	m_edbEGN.SetLimitText(EGNSIZE);
	m_edbAdress.SetLimitText(ADRESSSIZE);

	m_edbFirstName.SetWindowTextW(m_oPersonAndPhones.m_recPerson.szFirstName);
	m_edbSecondName.SetWindowTextW(m_oPersonAndPhones.m_recPerson.szSecondName);
	m_edbThirdName.SetWindowTextW(m_oPersonAndPhones.m_recPerson.szThirdName);
	m_edbEGN.SetWindowTextW(m_oPersonAndPhones.m_recPerson.szEGN);
	m_edbAdress.SetWindowTextW(m_oPersonAndPhones.m_recPerson.szAdress);

	long lCityID;
	int iIndex;
	CITIES recCity;
	CCitiesMap::CPair *pPair;
	pPair = m_oCitiesMap.PGetFirstAssoc();
	while (pPair != NULL)
	{
		lCityID = pPair->key;
		recCity = pPair->value;
		iIndex = m_cmbCity.AddString(recCity.szCityName);
		m_cmbCity.SetItemData(iIndex, lCityID);
		pPair = m_oCitiesMap.PGetNextAssoc(pPair);

		// Селектиране на град, ако подаденият на конструктора абонат е вече инициализиран
		if (lCityID == m_oPersonAndPhones.m_recPerson.lCityID) 
		{
			m_cmbCity.SetCurSel(iIndex);
		}
	}

	m_lscPhoneNumbers.SetExtendedStyle(LVS_EX_FULLROWSELECT); // позволява при кликване да се избира цял ред от ListCtrl
	CString strColumnName1 = L"Телефонен номер:";
	CString strColumnName2 = L"Вид на номера:";
	if (m_lscPhoneNumbers.InsertColumn(eColumnsNumber, strColumnName1, LVCFMT_LEFT, eColumnsWidthNumber, NO_SUBITEM) == -1 ||
		(m_lscPhoneNumbers.InsertColumn(eColumnsType, strColumnName2, LVCFMT_LEFT, eColumnsWidthType, NO_SUBITEM) == -1))
	{
		return FALSE;
	}

	PHONE_NUMBERS recPhoneNumber;
	PHONE_TYPES recPhoneType;
	iIndex = 0;
	for (INT_PTR i = 0; i < m_oPersonAndPhones.m_oPhoneNumbers.GetCount(); i++)
	{
		recPhoneNumber = *m_oPersonAndPhones.m_oPhoneNumbers.GetAt(i);
		m_lscPhoneNumbers.InsertItem(iIndex, recPhoneNumber.szPhoneNumber);

		m_oPhoneTypesMap.Lookup(recPhoneNumber.lPhoneTypeID, recPhoneType);
		m_lscPhoneNumbers.SetItemText(iIndex, eColumnsType, recPhoneType.szPhoneType);
		iIndex++; // позволява индексите на номерата в масива да съответстват на тези от списъка
	}

	return TRUE;
}


afx_msg void CPersonsDlg::MenuOnRightClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	CPoint oPoint;
	GetCursorPos(&oPoint);

	CMenu oMenu;
	oMenu.LoadMenu(IDM_PHONE_NUMBERS_MENU);
	CMenu* pMenu = oMenu.GetSubMenu(0);
	if (pMenu == NULL)
		return;
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, oPoint.x, oPoint.y, this, NULL);
}


void CPersonsDlg::OnAdd()
{
	PHONE_NUMBERS recPhoneNumber; // празен
	CPhoneNumbersDlg oPhoneNumbersDlg(recPhoneNumber, m_oPhoneTypesMap);
	INT_PTR iDialogResult = oPhoneNumbersDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("Номерът няма да бъде записан."), MB_OK | MB_ICONWARNING);
		return;
	}

	PHONE_NUMBERS* pPhoneNumber = new PHONE_NUMBERS(recPhoneNumber);
	INT_PTR iIndexOfNewPhoneNumber = m_oPersonAndPhones.m_oPhoneNumbers.Add(pPhoneNumber);
	m_lscPhoneNumbers.InsertItem(iIndexOfNewPhoneNumber, pPhoneNumber->szPhoneNumber); 

	PHONE_TYPES recPhoneType;
	m_oPhoneTypesMap.Lookup(pPhoneNumber->lPhoneTypeID, recPhoneType);
	m_lscPhoneNumbers.SetItemText(iIndexOfNewPhoneNumber, eColumnsType, recPhoneType.szPhoneType);

}


void CPersonsDlg::OnEdit()
{
	int iIndexOfSelectedPhoneNumber = m_lscPhoneNumbers.GetSelectionMark();
	if (iIndexOfSelectedPhoneNumber == -1)
	{
		AfxMessageBox(_T("Моля първо селектирайте номер от списъка."), MB_OK | MB_ICONWARNING);
		return;
	}

	PHONE_NUMBERS* pPhoneNumber = m_oPersonAndPhones.m_oPhoneNumbers.GetAt(iIndexOfSelectedPhoneNumber);
	CPhoneNumbersDlg oPhoneNumbersDlg(*pPhoneNumber, m_oPhoneTypesMap);
	INT_PTR iDialogResult = oPhoneNumbersDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("Номерът няма да бъде редактиран."), MB_OK | MB_ICONWARNING);
		return;
	}

	m_lscPhoneNumbers.SetItemText(iIndexOfSelectedPhoneNumber, eColumnsNumber, pPhoneNumber->szPhoneNumber);
	PHONE_TYPES recPhoneType;
	m_oPhoneTypesMap.Lookup(pPhoneNumber->lPhoneTypeID, recPhoneType);
	m_lscPhoneNumbers.SetItemText(iIndexOfSelectedPhoneNumber, eColumnsType, recPhoneType.szPhoneType);
}


void CPersonsDlg::OnDelete()
{
	int iIndexOfSelectedPhoneNumber = m_lscPhoneNumbers.GetSelectionMark();
	if (iIndexOfSelectedPhoneNumber == -1)
	{
		AfxMessageBox(_T("Моля първо селектирайте номер от списъка."), MB_OK | MB_ICONWARNING);
		return;
	}
	if (!m_lscPhoneNumbers.DeleteItem(iIndexOfSelectedPhoneNumber))
	{
		AfxMessageBox(_T("Изтриването на номера бе неуспешно."), MB_OK | MB_ICONERROR);
		return;
	}
	delete m_oPersonAndPhones.m_oPhoneNumbers.GetAt(iIndexOfSelectedPhoneNumber);
	m_oPersonAndPhones.m_oPhoneNumbers.RemoveAt(iIndexOfSelectedPhoneNumber);
}


void CPersonsDlg::OnOK()
{
	CString strFirstName, strSecondName, strThirdName, strEGN, strAdress;
	m_edbFirstName.GetWindowText(strFirstName);
	m_edbSecondName.GetWindowText(strSecondName);
	m_edbThirdName.GetWindowText(strThirdName);
	m_edbEGN.GetWindowText(strEGN);
	m_edbAdress.GetWindowText(strAdress);

	_tcscpy_s(m_oPersonAndPhones.m_recPerson.szFirstName, strFirstName);
	_tcscpy_s(m_oPersonAndPhones.m_recPerson.szSecondName, strSecondName);
	_tcscpy_s(m_oPersonAndPhones.m_recPerson.szThirdName, strThirdName);
	_tcscpy_s(m_oPersonAndPhones.m_recPerson.szEGN, strEGN);
	_tcscpy_s(m_oPersonAndPhones.m_recPerson.szAdress, strAdress);

	if (!CheckInput())
	{
		return;
	}
	
	int iIndexOfSelectedCity = m_cmbCity.GetCurSel();
	long lCityID = m_cmbCity.GetItemData(iIndexOfSelectedCity);
	m_oPersonAndPhones.m_recPerson.lCityID = lCityID;

	CDialog::OnOK();
}


BOOL CPersonsDlg::CheckInput()
{
	int iIndexOfSelectedCity = m_cmbCity.GetCurSel();
	if (iIndexOfSelectedCity == CB_ERR)
	{
		AfxMessageBox(_T("Моля първо селектирайте град от списъка."), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	if (m_lscPhoneNumbers.GetItemCount() == 0)
	{
		AfxMessageBox(_T("Моля добавете поне 1 телефонен номер."), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	PERSONS recPerson = m_oPersonAndPhones.m_recPerson; // за да се съкрати if-a
	CString strIncorrectInput = L" ";
	if (recPerson.szFirstName[0] == strIncorrectInput || recPerson.szSecondName[0] == strIncorrectInput 
		|| recPerson.szThirdName[0] == strIncorrectInput || recPerson.szEGN[0] == strIncorrectInput 
		|| recPerson.szAdress[0] == strIncorrectInput || recPerson.szFirstName[0] == '\0' || recPerson.szSecondName[0] == '\0' 
		|| recPerson.szThirdName[0] == '\0' || recPerson.szEGN[0] == '\0' || recPerson.szAdress[0] == '\0')
	{
		AfxMessageBox(_T("Някое от полетата е попълнено неправилно. В началото на думите не бива да има празни пространства."), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}


