// CitiesView.h 
//

#pragma once
#include "pch.h"
#include "afxcview.h"  
#include "CitiesDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesView

/// <summary> ������������� �� CListView, � ����� �� ����������� �������� �� ������� CITIES </summary>
class CCitiesView : public CListView
{

// Constructor / Destructor
// ----------------

public:
	/// <summary> ����������� �� ����������� </summary>
	CCitiesView() noexcept;
	
public:
	/// <summary> ����������� �� ���������� </summary>
	virtual ~CCitiesView() override;


// Methods
// ----------------
private:
	/// <summary> ����� �� ���������� �� ������ �� ���������, �������� � ���� ���� </summary>
	/// <returns> ��������� ����� �������� ��� ��������� </returns>
	CCitiesDocument* GetDocument() const;

	/// <summary> ����� �� ��������� �� �������� </summary>
	void InsertCitiesColumns();

	/// <summary> ����� �� ��������� �� �������� � ������� �� ��������� (���� ���� ���� �� ��������� ��������) </summary>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ����� �� ����� � ��������� </returns>
	BOOL FillCitiesViewRows();

	/// <summary> �����, ����� �� ���� ��� ������� �� ������������ �� ���������, �� �� �� ����������� � ��������� View  </summary>
	/// <param name="pSender"> �������� ��� ������� CView, ����� ������ �� �� ����������� </param>
	/// <param name="lHint"> ���� ���������� �� ������������� </param>
	/// <param name="pHint"> ���� �����, ����� ���������� �� ������������� </param>
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;


	/// <summary> ����� �� �������� �� ��� ���� ���� ��������� �� ����� � �������� �������� </summary>
	void OnAdd();

	/// <summary> ����� �� �������� �� ����� ���� ��� View ��� ���������� �� View </summary>
	/// <param name="recCity"> ������� �������, ����� �� �� ����������� �� ������������� ��� </param>
	void AddCityToView(const CITIES& recCity);
	
	/// <summary> ����� �� ������� �� ��� �� View, ����� �� �������� �� ������ ������ </summary>
	void OnEdit();

	/// <summary> �����, ��������� ��������� � ������������� ���� ��� View </summary>
	/// <param name="recCity"> ������� �������, � ����� �� �� ������ ���� </param>
	void EditCityInView(const CITIES& recCity);

	/// <summary> ����� �� ��������� �� ��� �� View � ������ ����� ������ </summary>
	void OnDelete();

	/// <summary> ����� �� ��������� �� ���� �� View ��� ���������� �� View </summary>
	/// <param name="lID"> ID �� �����, ����� �� ���� ��������� �� View </param>
	void DeleteCityFromView(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> ����� �� �������������� �������������� �� View. �������� �����, ������� �������� � ������� �������� </summary>
	void OnInitialUpdate() override;

	/// <summary> ����� �� ��������� �� ���� ��� ��������� �� ����� ����� � ������� �� View </summary>
	/// <param name="pWnd"> �������� ��� ��������� </param>
	/// <param name="pos"> ������� ����� ����������, ����� ��������� ���� � ��������� �� �� �������� ������ </param>
	void OnContextMenu(CWnd* pWnd, CPoint pos); 

	/// <summary> �����, ���������� ���������� � ������� �� View </summary>
	/// <param name="pDC"> ����, ��������� ������ ������ ��������� �� ������������ </param>
	virtual void OnDraw(CDC* pDC) override;  

	/// <summary> �����, ���������� �� ����� ����������� �� ��������� �� View </summary>
	/// <param name="pDC"> ���������, ��������� ��������� ����� </param>
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

protected:
	/// <summary> �����, ���������� �� ����� ������������ ��� ������������� �� �������� </summary>
	/// <param name="pDC"> �����, ���������� ���������� �� �������� ���������� ��� ����������� �� �������� </param>
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo) override;

	/// <summary> �����, ���������� �� ��� ������ �� ���������� ��� ����������� �� ��������; ���������� �������, ����� �� ���� �������� </summary>
	/// <param name="pDC"> ���������, ��������� ��������� ����� </param>
	/// <param name="pInfo"> �����, ���������� ���������� �� �������� ���������� ��� ����������� �� �������� </param>
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) override;

	/// <summary> �����, ���������� �� ���� ���������� ��� ����������� �� ��������; ����������� ������� �� OnBeginPrinting() ������� </summary>
	/// <param name="pDC"> ���������, ��������� ��������� ����� </param>
	/// <param name="pDC"> �����, ���������� ���������� �� �������� ���������� ��� ����������� �� �������� </param>
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) override;


// Implementation
// ----------------

	/// <summary> ����������, �� ������ ���� �� �� ���������� ��������� </summary>
	DECLARE_DYNCREATE(CCitiesView)

#ifdef _DEBUG
	/// <summary> �������� ���������� ��������� �� �������� �� ����� </summary>
	virtual void AssertValid() const override;

	/// <summary> ��������� ���������� �� ����� �� ����� ��� ���������� �� �������, ��������� ������������ </summary>
	/// <param name="dc"> �����, ���������� ���������� �� ������ � ���������� � �� ��������� �� ����������� ����� </param>
	virtual void Dump(CDumpContext& dc) const override;
#endif


// Generated message map functions
// ----------------

protected:
	DECLARE_MESSAGE_MAP()
};