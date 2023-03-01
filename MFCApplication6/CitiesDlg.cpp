// CitiesDlg.cpp
//

#include "pch.h"
#include "Resource.h"
#include "MFCApplication6.h"
#include "PhoneBook_Header.h"
#include "CitiesDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialog)

BEGIN_MESSAGE_MAP(CCitiesDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCitiesDlg::OnOK)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesDlg::CCitiesDlg(CITIES& recCity, CWnd* pParent /*=nullptr*/) 
	: CDialog(IDD_CITIES_DIALOG, pParent), m_recCity(recCity)
{

}

CCitiesDlg::~CCitiesDlg()
{

}


// MFC Overrides
// ----------------

void CCitiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, EDB_CITY_NAME, m_edbCityName);  
	DDX_Control(pDX, EDB_REGION_NAME, m_edbRegionName); 
} 


// Methods
// ----------------

BOOL CCitiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_edbCityName.SetLimitText(CITYNAMESIZE);
	m_edbRegionName.SetLimitText(REGIONNAMESIZE);

	m_edbCityName.SetWindowTextW(m_recCity.szCityName);
	m_edbRegionName.SetWindowTextW(m_recCity.szRegionName);
	return TRUE;  
}


void CCitiesDlg::OnOK()
{
	CString strCityName, strRegionName;
	m_edbCityName.GetWindowText(strCityName);
	m_edbRegionName.GetWindowText(strRegionName);

	_tcscpy_s(m_recCity.szCityName, strCityName);
	_tcscpy_s(m_recCity.szRegionName, strRegionName);
	
	if (!CheckInput())
	{
		return;
	}
	CDialog::OnOK(); 
}


const BOOL CCitiesDlg::CheckInput() const
{
	CString strIncorrectInput = L" ";
	if (m_recCity.szCityName[0] == strIncorrectInput || m_recCity.szRegionName[0] == strIncorrectInput 
		|| m_recCity.szCityName[0] == '\0' || m_recCity.szRegionName[0] == '\0')
	{
		AfxMessageBox(_T("Някое от полетата е попълнено неправилно. В началото на думите не бива да има празни пространства."), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}
