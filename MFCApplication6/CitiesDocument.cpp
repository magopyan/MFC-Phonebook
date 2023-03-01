// CitiesDocument.cpp 
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "CitiesDocument.h"
#endif
#include "CitiesView.h"
#include "CitiesDocument.h"
#include "CitiesData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCitiesDocument, CDocument)
BEGIN_MESSAGE_MAP(CCitiesDocument, CDocument)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument


// Constructor / Destructor
// ----------------

CCitiesDocument::CCitiesDocument() noexcept
{
	
}

CCitiesDocument::~CCitiesDocument()
{

}


// Methods
// ----------------

const CCitiesArray& CCitiesDocument::GetDocumentCitiesData() const
{
	return m_oCitiesArray;
}


CITIES* CCitiesDocument::GetCityWithID(const long& lID)  
{
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		if (m_oCitiesArray.GetAt(i)->lID == lID)
		{
			return m_oCitiesArray.GetAt(i);
		}
	}
	return NULL;
}


BOOL CCitiesDocument::AddCity(CITIES& recCity) 
{
	CITIES* pCity = new CITIES(recCity);
	CCitiesData oData;
	if (!oData.Insert(*pCity))
	{
		return FALSE;
	}
	m_oCitiesArray.Add(pCity);
	UpdateAllViews(NULL, eActionCitiesAdd, (CObject*)pCity);
	return TRUE;
}


BOOL CCitiesDocument::EditCity(CITIES recCity) 
{
	CCitiesData oData;
	if (!oData.UpdateWhereID(recCity.lID, recCity))
	{
		return FALSE;
	}
	if (GetCityWithID(recCity.lID) == NULL)
	{
		AfxMessageBox(_T("Градът, който трябва да се редактира, липсва в документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	oData.SelectWhereID(recCity.lID, recCity); // recCity получава инкрементирания Update Counter от БД преди да се презапише в масива от градове
	UpdateEditedCity(recCity);
	UpdateAllViews(NULL, eActionCitiesEdit, (CObject*)&recCity);
	return TRUE;
}

const void CCitiesDocument::UpdateEditedCity(const CITIES& recCity) 
{
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(i);
		if (pCity->lID == recCity.lID)
		{
			*pCity = recCity;
			break;
		}
	}
}


BOOL CCitiesDocument::DeleteCity(const long& lID) 
{
	CCitiesData oData;
	if (!oData.DeleteWhereID(lID))
	{
		return FALSE;
	}
	if (GetCityWithID(lID) == NULL)
	{
		AfxMessageBox(_T("Градът, който трябва да бъде изтрит, липсва в документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	UpdateAllViews(NULL, eActionCitiesDelete, (CObject*)lID);
	DeleteCityFromDocArray(lID);
	return TRUE;
}

const void CCitiesDocument::DeleteCityFromDocArray(const long& lID) 
{
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(i);
		if (pCity->lID == lID)
		{
			delete pCity;
			pCity = NULL;
			m_oCitiesArray.RemoveAt(i);
			break;
		}
	}
}


// Overrrides
// ----------------

BOOL CCitiesDocument::OnNewDocument()
{
	CCitiesData oCityData;
	if (!oCityData.SelectAll(m_oCitiesArray))
	{
		AfxMessageBox(_T("Грешка при извличване на данните за градовете от базата данни."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (!CDocument::OnNewDocument())  
	{
		AfxMessageBox(_T("Грешка при създаването на документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	
	return TRUE;
}


// CCitiesDocument serialization
// ----------------

void CCitiesDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCitiesDocument::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCitiesDocument::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCitiesDocument::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif


// CCitiesDocument diagnostics
// ----------------

#ifdef _DEBUG
void CCitiesDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif 


