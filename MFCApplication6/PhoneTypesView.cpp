// PhoneTypesView.cpp 
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#endif

#include "PhoneTypesDocument.h"
#include "PhoneTypesView.h"
#include "PhoneTypesDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �������� �� ��������, ����� �� �� ������ ��� ��������� View
#define PHONE_TYPE_COLUMN 0  

// �������� �� �������� (� ���� �������) �� ��������
#define COLUMN_WIDTH 225

#define NO_SUBITEM -1 // ��� �������� �� �������� �� ���� �� ��� ����������� �����

#define NEW_ROW_INDEX 0 // ��� �������� �� ��� ��� �������� �� ������ � 0


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)

	// ���������� �� ����� �������� ��� ����� ����� � ������������ �� �����
	ON_COMMAND(eActionPhoneTypesAdd, &CPhoneTypesView::OnAdd)
	ON_COMMAND(eActionPhoneTypesEdit, &CPhoneTypesView::OnEdit)
	ON_COMMAND(eActionPhoneTypesDelete, &CPhoneTypesView::OnDelete)

	ON_WM_CONTEXTMENU()

END_MESSAGE_MAP()



// Constructor / Destructor
// ----------------

CPhoneTypesView::CPhoneTypesView() noexcept
{

}

CPhoneTypesView::~CPhoneTypesView()
{

}

BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}


// Methods
// ----------------

CPhoneTypesDocument* CPhoneTypesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDocument)));
	return (CPhoneTypesDocument*)m_pDocument;
}

void CPhoneTypesView::InsertPhoneTypesColumns()
{
	CListCtrl& oListCtrl = GetListCtrl();
	const CString strColumnPhoneType = L"��� ��������� �����";

	if (oListCtrl.InsertColumn(PHONE_TYPE_COLUMN, strColumnPhoneType, LVCFMT_LEFT, COLUMN_WIDTH, NO_SUBITEM) == -1)
	{
		AfxMessageBox(_T("������ ��� ������������� �� �������� �� �������."), MB_OK | MB_ICONERROR);
		return;
	}
}

BOOL CPhoneTypesView::FillPhoneTypesViewRows()
{
	const CPhoneTypesArray& oPhoneTypesArray = GetDocument()->GetDocumentPhoneTypesData();
	if (!oPhoneTypesArray.GetCount())
	{
		AfxMessageBox(_T("� ��������� ������� �����, ����� �� ����� ������������."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	CListCtrl& oListCtrl = GetListCtrl();
	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); i++)
	{
		const PHONE_TYPES* pPhoneType = oPhoneTypesArray.GetAt(i);
		oListCtrl.InsertItem(PHONE_TYPE_COLUMN, pPhoneType->szPhoneType);
		oListCtrl.SetItemData(NEW_ROW_INDEX, pPhoneType->lID); 
	}
	return TRUE;
}


void CPhoneTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	PHONE_TYPES *pPhoneType = NULL;
	long lID = (long)pHint;

	switch (lHint)
	{
	case eActionPhoneTypesAdd:
		pPhoneType = (PHONE_TYPES*)pHint;
		AddPhoneTypeToView(*pPhoneType);
		break;

	case eActionPhoneTypesEdit:
		pPhoneType = (PHONE_TYPES*)pHint;
		EditPhoneTypeInView(*pPhoneType);
		break;

	case eActionPhoneTypesDelete:
		DeletePhoneTypeFromView(lID);
		break;

	default:
		break;
	}
}


void CPhoneTypesView::OnAdd() 
{
	PHONE_TYPES recPhoneType;
	CPhoneTypesDlg oDlg(recPhoneType);
	INT_PTR iDialogResult = oDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("����� ��������� ����� ���� �� ���� �������."), MB_OK | MB_ICONWARNING);
		return;
	}
	CPhoneTypesDocument* pDocument = GetDocument();
	pDocument->AddPhoneType(recPhoneType);
}

void CPhoneTypesView::AddPhoneTypeToView(const PHONE_TYPES& recPhoneType) 
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.InsertItem(PHONE_TYPE_COLUMN, recPhoneType.szPhoneType);
	oListCtrl.SetItemData(NEW_ROW_INDEX, recPhoneType.lID); 
}


void CPhoneTypesView::OnEdit() 
{
	CListCtrl& oListCtrl = GetListCtrl();
	int iSelectedItem;
	if ((iSelectedItem = oListCtrl.GetSelectionMark()) == -1)
	{
		AfxMessageBox(_T("���� ����� ������������ ��� ����� �� �������."), MB_OK | MB_ICONWARNING);
		return;
	}
	const long lID = oListCtrl.GetItemData(iSelectedItem);

	CPhoneTypesDocument* pDocument = GetDocument();
	PHONE_TYPES* pPhoneType = pDocument->GetPhoneTypeWithID(lID); 

	CPhoneTypesDlg oDlg(*pPhoneType); 
	INT_PTR iDialogResult = oDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("����� ��������� ����� ���� �� ���� ����������."), MB_OK | MB_ICONWARNING);
		return;
	}

	PHONE_TYPES recPhoneType = *pPhoneType; 

	if (!pDocument->EditPhoneType(recPhoneType))
	{
		return;
	}
}

void CPhoneTypesView::EditPhoneTypeInView(const PHONE_TYPES& recPhoneType) 
{
	CListCtrl& oListCtrl = GetListCtrl();
	for (INT_PTR i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (recPhoneType.lID == oListCtrl.GetItemData(i))
		{
			oListCtrl.SetItemText(i, PHONE_TYPE_COLUMN, recPhoneType.szPhoneType);
			break;
		}
	}
}


void CPhoneTypesView::OnDelete()  
{
	CListCtrl& oListCtrl = GetListCtrl();
	int iSelectedItem = oListCtrl.GetSelectionMark();
	if (iSelectedItem == -1)
	{
		AfxMessageBox(_T("���� ����� ������������ ��� ����� �� �������."), MB_OK | MB_ICONWARNING);
		return;
	}
	const long lID = oListCtrl.GetItemData(iSelectedItem);

	if (!GetDocument()->DeletePhoneType(lID))
	{
		AfxMessageBox(_T("����������� �� ���� ����� �� ���������."), MB_OK | MB_ICONERROR);
		return;
	}
}

void CPhoneTypesView::DeletePhoneTypeFromView(const long& lID) 
{
	CListCtrl& oListCtrl = GetListCtrl();
	for (INT_PTR i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (lID == oListCtrl.GetItemData(i))
		{
			oListCtrl.DeleteItem(i);
		}
	}
}



// Overrides
// ----------------

void CPhoneTypesView::OnInitialUpdate()
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT); 
	CListView::OnInitialUpdate();
	InsertPhoneTypesColumns();
	FillPhoneTypesViewRows();
}


void CPhoneTypesView::OnContextMenu(CWnd* pWnd, CPoint pos)
{
	CRect client_rect;
	CMenu SubMenu, MainMenu;

	GetClientRect(&client_rect);
	ClientToScreen(&client_rect);

	if (client_rect.PtInRect(pos))
	{
		if (!MainMenu.CreatePopupMenu())
		{
			AfxMessageBox(_T("������ ��� ����������� �� ������ ��� ��������� �� ����� �����."), MB_OK | MB_ICONERROR);
		}
		if (!MainMenu.AppendMenu(MF_STRING, eActionPhoneTypesAdd, _T("��������")) ||
			!MainMenu.AppendMenu(MF_STRING, eActionPhoneTypesEdit, _T("�����������")) ||
			!MainMenu.AppendMenu(MF_STRING, eActionPhoneTypesDelete, _T("���������")))
		{
			AfxMessageBox(_T("������ ��� ��������������� �� ������� �� ������."), MB_OK | MB_ICONERROR);
		}
		MainMenu.TrackPopupMenu(TPM_RIGHTALIGN, pos.x, pos.y, this);
	}
	else
	{
		CWnd::OnContextMenu(pWnd, pos);
	}
}


// CPhoneTypesView drawing
// ----------------

void CPhoneTypesView::OnDraw(CDC* /*pDC*/)
{
	const CPhoneTypesDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!&pDoc)
		return;
}


// CPhoneTypesView printing
// ----------------

BOOL CPhoneTypesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CPhoneTypesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void CPhoneTypesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}


// CPhoneTypesView diagnostics
// ----------------
#ifdef _DEBUG
void CPhoneTypesView::AssertValid() const
{
	CView::AssertValid();
}

void CPhoneTypesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif 

