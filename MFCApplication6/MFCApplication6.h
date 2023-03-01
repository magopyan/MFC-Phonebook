
// MFCApplication6.h : main header file for the MFCApplication6 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCApplication6App:
// See MFCApplication6.cpp for the implementation of this class
//

class CMFCApplication6App : public CWinAppEx
{
public:
	CMFCApplication6App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication6App theApp;
