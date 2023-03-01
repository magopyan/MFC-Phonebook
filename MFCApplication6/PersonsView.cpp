// PersonsView.cpp 
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#endif
#include "CitiesView.h"
#include "PersonsView.h"
#include "PersonsDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Кодиране на колоните, които ще се добавят към списъчния View
enum eColumns {eColumnsFirstName = 0, eColumnsThirdName = 1, eColumnsCity = 2};

// Кодиране на ширината (в брой пиксели) на трите колони
enum eColumnsWidth { eColumnsWidthFirstName = 150, eColumnsWidthThirdName = 150, eColumnsWidthCity = 150 };

#define NO_SUBITEM -1 // при добавяне на колоните те няма да имат пояснителен текст


/////////////////////////////////////////////////////////////////////////////
// CPersonsView

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)

	// Обвързване на трите операции при десен бутон с обработващия им метод
	ON_COMMAND(eActionCitiesAdd, &CPersonsView::OnAdd)
	ON_COMMAND(eActionEditPerson, &CPersonsView::OnEdit)
	ON_COMMAND(eActionCitiesDelete, &CPersonsView::OnDelete)

	ON_WM_CONTEXTMENU()

END_MESSAGE_MAP()



// Constructor / Destructor
// ----------------

CPersonsView::CPersonsView() noexcept
{

}

CPersonsView::~CPersonsView()
{

}

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}


// Methods
// ----------------

CPersonsDocument* CPersonsView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDocument)));
	return (CPersonsDocument*)m_pDocument;
}


void CPersonsView::InsertPersonsColumns()
{
	CListCtrl& oListCtrl = GetListCtrl();
	const CString strColumnFirstName = L"Име";
	const CString strColumnThirdName = L"Фамилия";
	const CString strColumnCity = L"Град";

	if (oListCtrl.InsertColumn(eColumnsFirstName, strColumnFirstName, LVCFMT_LEFT, eColumnsWidthFirstName, NO_SUBITEM) == -1 ||
		oListCtrl.InsertColumn(eColumnsThirdName, strColumnThirdName, LVCFMT_LEFT, eColumnsWidthThirdName, NO_SUBITEM) == -1 ||
		oListCtrl.InsertColumn(eColumnsCity, strColumnCity, LVCFMT_LEFT, eColumnsWidthCity, NO_SUBITEM) == -1 )
	{
		AfxMessageBox(_T("Грешка при изчертаването на колоните на списъка."), MB_OK | MB_ICONERROR);
		return;
	}
}


BOOL CPersonsView::FillPersonsViewRows()
{
	const CPersonsArray& oPersonsArray = GetDocument()->GetDocumentPersonsData();
	const CCitiesMap& oCitiesMap = GetDocument()->GetDocumentCitiesData();
	if (!oPersonsArray.GetCount())
	{
		AfxMessageBox(_T("В документа липсват данни за абонати, които да бъдат презентирани."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (!oCitiesMap.GetCount())
	{
		AfxMessageBox(_T("В документа липсват данни за градове, които да бъдат презентирани."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	CListCtrl& oListCtrl = GetListCtrl();
	int iNewItemIndex = 0;
	for (INT_PTR i = 0; i < oPersonsArray.GetCount(); i++)
	{
		const PERSONS* pPerson = oPersonsArray.GetAt(i);
		iNewItemIndex = oListCtrl.InsertItem(eColumnsFirstName, pPerson->szFirstName);
		oListCtrl.SetItemData(iNewItemIndex, pPerson->lID);
		oListCtrl.SetItemText(iNewItemIndex, eColumnsThirdName, pPerson->szThirdName);

		CITIES recCity;
		oCitiesMap.Lookup(pPerson->lCityID, recCity);
		oListCtrl.SetItemText(iNewItemIndex, eColumnsCity, recCity.szCityName);
	}
	return TRUE;
}


void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	PERSONS *pPerson = NULL;
	long lID = (long)pHint;

	switch (lHint)
	{

	case eActionAddPerson:
		pPerson = (PERSONS*)pHint;
		AddPersonToView(*pPerson);
		break;

	case eActionEditPerson:
		pPerson = (PERSONS*)pHint;
		EditPersonInView(*pPerson);
		break;

	case eActionDeletePerson:
		lID = (long)pHint;
		DeletePersonFromView(lID);
		break;

	default:
		break;
	}
}

void CPersonsView::OnAdd() 
{
	PHONE_NUMBERS recPhoneNumber;
	CCitiesMap& oCitiesMap = GetDocument()->GetDocumentCitiesData();
	CPhoneTypesMap& oPhoneTypesMap = GetDocument()->GetDocumentPhoneTypesData();
	CPerson oPersonAndPhones;
	CPersonsDlg oDlg(oPersonAndPhones, oCitiesMap, oPhoneTypesMap);

	INT_PTR iDialogResult = oDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("Абонатът и номерата му няма да бъдат записани."), MB_OK | MB_ICONWARNING);
		return;
	}
	GetDocument()->AddPerson(oPersonAndPhones);
}

void CPersonsView::AddPersonToView(const PERSONS& recPerson) 
{
	CListCtrl& oListCtrl = GetListCtrl();
	int iNewItemIndex = oListCtrl.InsertItem(eColumnsFirstName, recPerson.szFirstName);
	oListCtrl.SetItemData(iNewItemIndex, recPerson.lID); 
	oListCtrl.SetItemText(iNewItemIndex, eColumnsThirdName, recPerson.szThirdName);

	CITIES recCity;
	const CCitiesMap& oCitiesMap = GetDocument()->GetDocumentCitiesData();
	oCitiesMap.Lookup(recPerson.lCityID, recCity);
	oListCtrl.SetItemText(iNewItemIndex, eColumnsCity, recCity.szCityName);
}


void CPersonsView::OnEdit() 
{
	CListCtrl& oListCtrl = GetListCtrl();
	int iSelectedItem = oListCtrl.GetSelectionMark();
	if (iSelectedItem == -1)
	{
		AfxMessageBox(_T("Моля първо селектирайте абонат от списъка."), MB_OK | MB_ICONWARNING);
		return;
	}
	const long lID = oListCtrl.GetItemData(iSelectedItem);

	const PERSONS* pPerson = GetDocument()->GetPersonWithID(lID); 
	CCitiesMap& oCitiesMap = GetDocument()->GetDocumentCitiesData();
	CPhoneTypesMap& oPhoneTypesMap = GetDocument()->GetDocumentPhoneTypesData();

	CPerson oPersonAndPhones;
	oPersonAndPhones.m_recPerson = *pPerson;
	GetDocument()->GetPhoneNumbersArray(lID, oPersonAndPhones.m_oPhoneNumbers);

	PHONE_NUMBERS recPhoneNumber;
	CPersonsDlg oDlg(oPersonAndPhones, oCitiesMap, oPhoneTypesMap);
	INT_PTR iDialogResult = oDlg.DoModal();
	if (iDialogResult != IDOK)
	{
		AfxMessageBox(_T("Абонатът и номерата му няма да бъдат редактирани."), MB_OK | MB_ICONWARNING);
		return;
	}

	if (!GetDocument()->EditPerson(oPersonAndPhones))
	{
		return;
	}
}


void CPersonsView::EditPersonInView(const PERSONS& recPerson)
{
	CListCtrl& oListCtrl = GetListCtrl();
	for (INT_PTR i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (recPerson.lID == oListCtrl.GetItemData(i))
		{
			oListCtrl.SetItemText(i, eColumnsFirstName, recPerson.szFirstName);
			oListCtrl.SetItemText(i, eColumnsThirdName, recPerson.szThirdName);

			CITIES recCity;
			const CCitiesMap& oCitiesMap = GetDocument()->GetDocumentCitiesData();
			oCitiesMap.Lookup(recPerson.lCityID, recCity);
			oListCtrl.SetItemText(i, eColumnsCity, recCity.szCityName);
		}
	}
}


void CPersonsView::OnDelete() 
{
	CListCtrl& oListCtrl = GetListCtrl();
	int iSelectedItem = oListCtrl.GetSelectionMark();
	if (iSelectedItem == -1)
	{
		AfxMessageBox(_T("Моля първо селектирайте град от списъка."), MB_OK | MB_ICONWARNING);
		return;
	}
	const long lID = oListCtrl.GetItemData(iSelectedItem);

	if (!GetDocument()->DeletePerson(lID))
	{
		AfxMessageBox(_T("Изтриването на абоната и номерата му бе неуспешно."), MB_OK | MB_ICONERROR);
		return;
	}
}


void CPersonsView::DeletePersonFromView(const long& lID)  
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

void CPersonsView::OnInitialUpdate()
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT); 
	CListView::OnInitialUpdate();
	InsertPersonsColumns();
	FillPersonsViewRows();
}


void CPersonsView::OnContextMenu(CWnd* pWnd, CPoint pos)
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


// CPersonsView drawing
// ----------------

void CPersonsView::OnDraw(CDC* /*pDC*/)
{
	const CPersonsDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!&pDoc)
		return;
}


// CPersonsView printing
// ----------------

BOOL CPersonsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CPersonsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void CPersonsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}


// CPersonsView diagnostics
// ----------------

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CView::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif 

