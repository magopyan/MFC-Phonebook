// CitiesDocument.h 
//

#pragma once
#include "pch.h"
#include "PhoneBook_Header.h"

// �������� �� ���������, ����� �� ����� ��������� �� CCitiesView ���� UpdateAllViews()
enum eActionCities { eActionCitiesAdd = 1, eActionCitiesEdit = 2, eActionCitiesDelete = 3 };


/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument

/// <summary>
/// ���� ��������� �� CDocument, ����� ��������� ������� �� ������� CITIES
/// </summary>
class CCitiesDocument : public CDocument
{
	

// Constructor / Destructor
// ----------------

private: 
	/// <summary> ����������� �� ����������� </summary>
	CCitiesDocument() noexcept;

	/// <summary> ����������� �� ���������� </summary>
	virtual ~CCitiesDocument();


// Methods 
// ----------------

public:
	/// <summary> �����, ����� ������ �� ������ �� ������-������ � ������� </summary>
	/// <returns> ��������� ����� ���������� ��� ������-������ � ��������� ��� CITIES </returns>
	const CCitiesArray& GetDocumentCitiesData() const;

	/// <summary> ����� �� ������ �� ���� � ���������� ID � ������-������ </summary>
	/// <param name="lID"> ID �� �����, ����� ����� ������ �� ���� ������ </param>
	/// <returns> ��������� ����� �������� ��� ����� � ���������� ID ��� NULL, ��� ���� ����� ���� � ������-������ </returns>
	CITIES* GetCityWithID(const long& lID);

	/// <summary> ����� �� �������� �� ������� ���� �������� �������� ���� ��� ������ ������ </summary>
	/// <param name="recCity"> ������� ����� �� ����� � ������� ��, � ���� ���������� �� ��� �� � ID, ���������� �� �� SQL </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������  </returns>
	BOOL AddCity(CITIES& recCity);

	/// <summary> ����� �� ������� �� ����������� ���� ��� ������ ������ </summary>
	/// <param name="recCity"> ������� ������ ����� �� ����� </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������  </returns>
	BOOL EditCity(CITIES recCity);

	/// <summary> ����� �� ��������� �� ���� � ���������� ID �� ������ ���� </summary>
	/// <param name="lID"> ID �� �����, ����� �� ���� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL DeleteCity(const long& lID);

private:	
	/// <summary> ����� �� ���������� �� �������� ���� � ������-������ �� ��������� </summary>
	/// <param name="recCity"> ������� ������� �� �����, ����� ������ �� ���� ������� � ������-������ </param>
	const void UpdateEditedCity(const CITIES& recCity);

	/// <summary> ����� �� ���������� �� ���� �� ������-������ �� ��������� </summary>
	/// <param name="lID"> ID �� �����, ����� ������ �� ���� ������ </param>
	const void DeleteCityFromDocArray(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> �����, ����� �� ���� ��� ��������� �� �������� � ������� ������-������ � ������ ������ �� ������� CITIES </summary>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	virtual BOOL OnNewDocument();

	/// <summary> �����, ���������� �������������� �� �������� �� ����� </summary>
	/// <param name="ar"> �����, ���������� ����������� ��������� �� ����� � ������ �� �������� ����� �/�� ������� </param>
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif 


// Implementation
// ----------------

	DECLARE_DYNCREATE(CCitiesDocument) 

#ifdef _DEBUG
	/// <summary> �������� ���������� ��������� �� �������� �� ����� </summary>
	virtual void AssertValid() const;

	/// <summary> ��������� ���������� �� ����� �� ����� ��� ���������� �� �������, ��������� ������������ </summary>
	/// <param name="dc"> �����, ���������� ���������� �� ������ � ���������� � �� ��������� �� ����������� ����� </param>
	virtual void Dump(CDumpContext& dc) const;
#endif

#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif 


// Generated message map functions
// ----------------

protected:
	DECLARE_MESSAGE_MAP()


// Members
// ----------------
private:
	/// <summary> ����� �� �������, � ����� �� ���������� ������ ������ �� ������� CITIES </summary>
	CCitiesArray m_oCitiesArray;
};
