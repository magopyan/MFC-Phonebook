// PhoneNumbersDlg.cpp
//

#include "pch.h"
#include "Resource.h"
#include "MFCApplication6.h"
#include "PhoneBook_Header.h"
#include "PhoneNumbersDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDlg


IMPLEMENT_DYNAMIC(CPhoneNumbersDlg, CDialog)

BEGIN_MESSAGE_MAP(CPhoneNumbersDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneNumbersDlg::OnOK)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneNumbersDlg::CPhoneNumbersDlg(PHONE_NUMBERS& recPhoneNumber, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent /*=nullptr*/) 
	: CDialog(IDD_PHONE_NUMBERS_DIALOG, pParent), m_oPhoneTypesMap(oPhoneTypesMap), m_recPhoneNumber(recPhoneNumber)
{
	
}

CPhoneNumbersDlg::~CPhoneNumbersDlg()
{

}


// MFC Overrides
// ----------------

void CPhoneNumbersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, EDB_PHONE_NUMBER, m_edbPhoneNumber);
	DDX_Control(pDX, CMB_PHONE_TYPE, m_cmbPhoneType);
}


// Methods
// ----------------

BOOL CPhoneNumbersDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_edbPhoneNumber.SetLimitText(PHONENUMBERSIZE);
	m_edbPhoneNumber.SetWindowTextW(m_recPhoneNumber.szPhoneNumber);

	long lID;
	int iIndex;
	PHONE_TYPES recPhoneType;
	CPhoneTypesMap::CPair *pPair;
	pPair = m_oPhoneTypesMap.PGetFirstAssoc();
	while (pPair != NULL)
	{
		lID = pPair->key;
		recPhoneType = pPair->value;
		iIndex = m_cmbPhoneType.AddString(recPhoneType.szPhoneType);
		m_cmbPhoneType.SetItemData(iIndex, lID);
		pPair = m_oPhoneTypesMap.PGetNextAssoc(pPair);

		if (lID == m_recPhoneNumber.lPhoneTypeID)
		{
			m_cmbPhoneType.SetCurSel(iIndex);
		}
	}
	return TRUE;
}


void CPhoneNumbersDlg::OnOK()
{
	CString strPhoneNumber;
	m_edbPhoneNumber.GetWindowText(strPhoneNumber);
	_tcscpy_s(m_recPhoneNumber.szPhoneNumber, strPhoneNumber);

	int iSelectedPhoneType = m_cmbPhoneType.GetCurSel();
	long lPhoneTypeID = m_cmbPhoneType.GetItemData(iSelectedPhoneType);
	m_recPhoneNumber.lPhoneTypeID = lPhoneTypeID;

	if (!CheckInput())
	{
		return;
	}
	CDialog::OnOK();
}


BOOL CPhoneNumbersDlg::CheckInput()
{
	int iSelectedPhoneType = m_cmbPhoneType.GetCurSel();
	if (iSelectedPhoneType == CB_ERR)
	{
		AfxMessageBox(_T("Моля селектирайте вида на телефонния номер."), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	CString strIncorrectInput = L" ";
	if (m_recPhoneNumber.szPhoneNumber[0] == strIncorrectInput || m_recPhoneNumber.szPhoneNumber[0] == '\0' )
	{
		AfxMessageBox(_T("Полето е попълнено неправилно. В началото на думата не бива да има празни пространства."), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	CString strPlus = L"+";
	CString strMinus = L"-";
	for (int i = 0; i < _tcslen(m_recPhoneNumber.szPhoneNumber); i++)
	{
		if (!isdigit(m_recPhoneNumber.szPhoneNumber[i]) && m_recPhoneNumber.szPhoneNumber[i] != strPlus && m_recPhoneNumber.szPhoneNumber[i] != strMinus)
		{
			AfxMessageBox(_T("Телефонният номер може да съдържа само цифри и символите + и - ."), MB_OK | MB_ICONWARNING);
			return FALSE;
		}
			
	}

	return TRUE;
}
