// PhoneTypesDlg.cpp
//

#include "pch.h"
#include "Resource.h"
#include "MFCApplication6.h"
#include "PhoneBook_Header.h"
#include "PhoneTypesDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDlg

IMPLEMENT_DYNAMIC(CPhoneTypesDlg, CDialog)

BEGIN_MESSAGE_MAP(CPhoneTypesDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneTypesDlg::OnOK)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneTypesDlg::CPhoneTypesDlg(PHONE_TYPES& recPhoneType, CWnd* pParent /*=nullptr*/) 
	: CDialog(IDD_PHONE_TYPES_DIALOG, pParent), m_recPhoneType(recPhoneType)
{
	
}

CPhoneTypesDlg::~CPhoneTypesDlg()
{

}


// MFC Overrides
// ----------------

void CPhoneTypesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, EDB_PHONE_TYPE, m_edbPhoneType);
}


// Methods
// ----------------

BOOL CPhoneTypesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_edbPhoneType.SetLimitText(PHONETYPESIZE);
	

	m_edbPhoneType.SetWindowTextW(m_recPhoneType.szPhoneType);
	return TRUE;
}


void CPhoneTypesDlg::OnOK() 
{
	CString strPhoneType;
	m_edbPhoneType.GetWindowText(strPhoneType);
	
	_tcscpy_s(m_recPhoneType.szPhoneType, strPhoneType);

	if (!CheckInput())
	{
		return;
	}
	CDialog::OnOK();
}


BOOL CPhoneTypesDlg::CheckInput()
{
	CString strIncorrectInput = L" ";
	if (m_recPhoneType.szPhoneType[0] == strIncorrectInput || m_recPhoneType.szPhoneType[0] == '\0')
	{
		AfxMessageBox(_T("Полето е попълнено неправилно. В началото на думата не бива да има празни пространства."), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}
