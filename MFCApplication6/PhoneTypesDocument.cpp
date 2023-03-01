// PhoneTypesDocument.cpp 
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "PhoneTypesDocument.h"
#endif

#include "PhoneTypesView.h"
#include "PhoneTypesDocument.h"
#include "PhoneTypesData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPhoneTypesDocument, CDocument)
BEGIN_MESSAGE_MAP(CPhoneTypesDocument, CDocument)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument


// Constructor / Destructor
// ----------------

CPhoneTypesDocument::CPhoneTypesDocument() noexcept
{

}

CPhoneTypesDocument::~CPhoneTypesDocument()
{

}


// Methods
// ----------------

const CPhoneTypesArray& CPhoneTypesDocument::GetDocumentPhoneTypesData() const
{
	return m_oPhoneTypesArray;
}

PHONE_TYPES* CPhoneTypesDocument::GetPhoneTypeWithID(const long& lID)
{
	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); i++)
	{
		if (m_oPhoneTypesArray.GetAt(i)->lID == lID)
		{
			return m_oPhoneTypesArray.GetAt(i);
		}
	}
	return NULL;
}


BOOL CPhoneTypesDocument::AddPhoneType(PHONE_TYPES& recPhoneType)
{
	PHONE_TYPES* pPhoneType = new PHONE_TYPES(recPhoneType);
	CPhoneTypesData oData;
	if (!oData.Insert(*pPhoneType))
	{
		return FALSE;
	}
	m_oPhoneTypesArray.Add(pPhoneType);
	UpdateAllViews(NULL, eActionPhoneTypesAdd, (CObject*)pPhoneType);
	return TRUE;
}


BOOL CPhoneTypesDocument::EditPhoneType(PHONE_TYPES recPhoneType) 
{
	CPhoneTypesData oData;
	if (!oData.UpdateWhereID(recPhoneType.lID, recPhoneType))
	{
		return FALSE;
	}
	if (GetPhoneTypeWithID(recPhoneType.lID) == NULL)
	{
		AfxMessageBox(_T("Видът номер, който се опитвате да редактирате, липсва в документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	oData.SelectWhereID(recPhoneType.lID, recPhoneType); 
	UpdateEditedPhoneType(recPhoneType);
	UpdateAllViews(NULL, eActionPhoneTypesEdit, (CObject*)&recPhoneType);
	return TRUE;
}

void CPhoneTypesDocument::UpdateEditedPhoneType(const PHONE_TYPES& recPhoneType) 
{
	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(i);
		if (pPhoneType->lID == recPhoneType.lID)
		{
			*pPhoneType = recPhoneType;
			break;
		}
	}
}


BOOL CPhoneTypesDocument::DeletePhoneType(const long& lID) 
{
	CPhoneTypesData oData;
	if (!oData.DeleteWhereID(lID))
	{
		return FALSE;
	}
	if (GetPhoneTypeWithID(lID) == NULL)
	{
		AfxMessageBox(_T("Видът номер, който се опитвате да изтриете, липсва в документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	UpdateAllViews(NULL, eActionPhoneTypesDelete, (CObject*)lID);
	DeletePhoneTypeFromDocArray(lID);
	return TRUE;
}


void CPhoneTypesDocument::DeletePhoneTypeFromDocArray(const long& lID) 
{
	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(i);
		if (pPhoneType->lID == lID)
		{
			delete pPhoneType;
			pPhoneType = NULL;
			m_oPhoneTypesArray.RemoveAt(i);
			break;
		}
	}
}


// Overrrides
// ----------------

BOOL CPhoneTypesDocument::OnNewDocument()
{
	CPhoneTypesData oData;
	if (!oData.SelectAll(m_oPhoneTypesArray))
	{
		AfxMessageBox(_T("Грешка при извличането на данните от базата данни."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (!CDocument::OnNewDocument())
	{
		AfxMessageBox(_T("Грешка при създаването на документа."), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}


// CPhoneTypesDocument serialization
// ----------------

void CPhoneTypesDocument::Serialize(CArchive& ar)
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
void CPhoneTypesDocument::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPhoneTypesDocument::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPhoneTypesDocument::SetSearchContent(const CString& value)
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


// CPhoneTypesDocument diagnostics
// ----------------

#ifdef _DEBUG
void CPhoneTypesDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhoneTypesDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif 


