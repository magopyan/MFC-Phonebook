// CitiesView.cpp 
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#endif
#include "CitiesDocument.h"
#include "CitiesView.h"
#include "CitiesDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Кодиране на колоните, които ще се изчертаят в списъчния View
enum eColumns { eColumnsCity = 0, eColumnsRegion = 1 };

// Кодиране на ширината (в брой пиксели) на двете колони
enum eColumnsWidth { eColumnsWidthCity = 175, eColumnsWidthRegion = 200 };

#define NO_SUBITEM -1 // при добавяне на колоните те няма да имат пояснителен текст

#define NEW_ROW_INDEX 0 // при добавяне на нов ред индексът му винаги е 0


/////////////////////////////////////////////////////////////////////////////
// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)

	// Обвързване на трите операции при десен бутон с обработващия им метод
	ON_COMMAND(eActionCitiesAdd, &CCitiesView::OnAdd)
	ON_COMMAND(eActionCitiesEdit, &CCitiesView::OnEdit)
	ON_COMMAND(eActionCitiesDelete, &CCitiesView::OnDelete)
	
	ON_WM_CONTEXTMENU()
	
END_MESSAGE_MAP()



// Constructor / Destructor
// ----------------

CCitiesView::CCitiesView() noexcept
{

}

CCitiesView::~CCitiesView()
{

}

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT; // задаване на стил на списъчния View
	return CListView::PreCreateWindow(cs);
}



// Methods
// ----------------

CCitiesDocument* CCitiesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDocument)));
	return (CCitiesDocument*)m_pDocument;
}

void CCitiesView::InsertCitiesColumns()
{
	CListCtrl& oListCtrl = GetListCtrl(); 
	const CString strColumnCity = L"Град";
	const CString strColumnRegion = L"Регион";

	if (oListCtrl.InsertColumn(eColumnsCity, strColumnCity, LVCFMT_LEFT, eColumnsWidthCity, NO_SUBITEM) == -1 ||
		oListCtrl.InsertColumn(eColumnsRegion, strColumnRegion, LVCFMT_LEFT, eColumnsWidthRegion, NO_SUBITEM) == -1)
	{
		AfxMessageBox(_T("Грешка при изчертаването на колоните на списъка."), MB_OK | MB_ICONERROR);
		return;
	}
}

BOOL CCitiesView::FillCitiesViewRows()
{
	const CCitiesArray& oCityArray = GetDocument()->GetDocumentCitiesData();
	if (!oCityArray.GetCount())
	{
		AfxMessageBox(_T("В документа липсват данни, които да бъдат презентирани."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	CListCtrl& oListCtrl = GetListCtrl();
	for (INT_PTR i = 0; i < oCityArray.GetCount(); i++)
	{
		const CITIES* pCity = oCityArray.GetAt(i);
		oListCtrl.InsertItem(eColumnsCity, pCity->szCityName);
		oListCtrl.SetItemData(NEW_ROW_INDEX, pCity->lID); 
		oListCtrl.SetItemText(NEW_ROW_INDEX, eColumnsRegion, pCity->szRegionName);
	}
	return TRUE;
}


void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CITIES *pCity = NULL;
	long lID = (long)pHint;

	switch (lHint)
	{
	case eActionCitiesAdd:
		pCity = (CITIES*)pHint;
		AddCityToView(*pCity);
		break;

	case eActionCitiesEdit:
		pCity = (CITIES*)pHint;
		EditCityInView(*pCity);
		break;

	case eActionCitiesDelete:
		DeleteCityFromView(lID);
		break;

	default:
		break;
	}
}


void CCitiesView::OnAdd() 
{
	CITIES recCity;
	CCitiesDlg oDlg(recCity);
	INT_PTR iDialogResult = oDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("Градът няма да бъде записан."), MB_OK | MB_ICONWARNING);
		return;
	}
	CCitiesDocument* pDocument = GetDocument();
	pDocument->AddCity(recCity);
}

void CCitiesView::AddCityToView(const CITIES& recCity) 
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.InsertItem(eColumnsCity, recCity.szCityName);
	oListCtrl.SetItemData(NEW_ROW_INDEX, recCity.lID); 
	oListCtrl.SetItemText(NEW_ROW_INDEX, eColumnsRegion, recCity.szRegionName);
}


void CCitiesView::OnEdit() 
{
	CListCtrl& oListCtrl = GetListCtrl();
	int iSelectedItem = oListCtrl.GetSelectionMark();
	if (iSelectedItem == -1)
	{
		AfxMessageBox(_T("Моля първо селектирайте град от списъка."), MB_OK | MB_ICONWARNING);
		return;
	}
	const long lID = oListCtrl.GetItemData(iSelectedItem);

	CCitiesDocument* pDocument = GetDocument();
	CITIES* pCity = pDocument->GetCityWithID(lID); 

	CCitiesDlg oDlg(*pCity); 
	INT_PTR iDialogResult = oDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("Градът няма да бъде редактиран."), MB_OK | MB_ICONWARNING);
		return;
	}
	
	CITIES recCity = *pCity; 
	if (!pDocument->EditCity(recCity))
	{
		return;
	}
}

void CCitiesView::EditCityInView(const CITIES& recCity) 
{
	CListCtrl& oListCtrl = GetListCtrl();
	for (INT_PTR i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (recCity.lID == oListCtrl.GetItemData(i))
		{
			oListCtrl.SetItemText(i, eColumnsCity, recCity.szCityName);
			oListCtrl.SetItemText(i, eColumnsRegion, recCity.szRegionName);
		}
	}
}


void CCitiesView::OnDelete() 
{
	CListCtrl& oListCtrl = GetListCtrl();
	int iSelectedItem = oListCtrl.GetSelectionMark();
	if (iSelectedItem == -1)
	{
		AfxMessageBox(_T("Моля първо селектирайте град от списъка."), MB_OK | MB_ICONWARNING);
		return;
	}
	const long lID = oListCtrl.GetItemData(iSelectedItem);

	if (!GetDocument()->DeleteCity(lID))
	{
		AfxMessageBox(_T("Изтриването на града бе неуспешно."), MB_OK | MB_ICONERROR);
		return;
	}
}

void CCitiesView::DeleteCityFromView(const long& lID) 
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
void CCitiesView::OnInitialUpdate()
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT); // за да може при кликване да се избира целия ред
	CListView::OnInitialUpdate(); 
	InsertCitiesColumns();
	FillCitiesViewRows();
}

void CCitiesView::OnContextMenu(CWnd* pWnd, CPoint pos) 
{
	CRect client_rect;
	CMenu SubMenu, MainMenu;

	GetClientRect(&client_rect);
	ClientToScreen(&client_rect);

	if (client_rect.PtInRect(pos))
	{
		if (!MainMenu.CreatePopupMenu())
		{
			AfxMessageBox(_T("Грешка при създаването на менюто при натискане на десен бутон."), MB_OK | MB_ICONERROR);
		}
		if (!MainMenu.AppendMenu(MF_STRING, eActionCitiesAdd, _T("Добавяне")) ||
			!MainMenu.AppendMenu(MF_STRING, eActionCitiesEdit, _T("Редактиране")) ||
			!MainMenu.AppendMenu(MF_STRING, eActionCitiesDelete, _T("Изтриване")))
		{
			AfxMessageBox(_T("Грешка при визуализирането на опциите на менюто."), MB_OK | MB_ICONERROR);
		}
		MainMenu.TrackPopupMenu(TPM_RIGHTALIGN, pos.x, pos.y, this);
	}
	else
	{
		CWnd::OnContextMenu(pWnd, pos);
	}
}


// CCitiesView drawing
// ----------------
void CCitiesView::OnDraw(CDC* /*pDC*/)
{
	const CCitiesDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!&pDoc)
		return;
}


// CCitiesView printing
// ----------------
BOOL CCitiesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCitiesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void CCitiesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}


// CCitiesView diagnostics
// ----------------
#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif 

