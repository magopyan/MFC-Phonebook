// PhoneTypesDocument.h 
//

#pragma once
#include "pch.h"
#include "PhoneBook_Header.h"

// �������� �� ���������, ����� �� ����� ��������� �� CPhoneTypesView ���� UpdateAllViews()
enum eActionPhoneTypes { eActionPhoneTypesAdd = 1, eActionPhoneTypesEdit = 2, eActionPhoneTypesDelete = 3 };


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument

/// <summary>
/// ���� ��������� �� CDocument, ����� ��������� ������� �� ������� PHONE_TYPES
/// </summary>
class CPhoneTypesDocument : public CDocument
{

// Constructor / Destructor
// ----------------

protected:
	/// <summary> ����������� �� ����������� </summary>
	CPhoneTypesDocument() noexcept;

public:
	/// <summary> ����������� �� ���������� </summary>
	virtual ~CPhoneTypesDocument();


// Methods 
// ----------------

public:
	/// <summary> �����, ����� ������ �� ������ �� ������-������ � ������ ������ </summary>
	/// <returns> ��������� ����� ���������� ��� ������-������ � ��������� ��� PHONE_NUMBERS </returns>
	const CPhoneTypesArray& GetDocumentPhoneTypesData() const;

	/// <summary> ����� �� ������ �� ��� ����� � ���������� ID � ������-������ </summary>
	/// <param name="lID"> ID �� ���� �����, ����� ����� ������ �� ���� ������ </param>
	/// <returns> ��������� ����� �������� ��� ���� ����� � ���������� ID ��� NULL, ��� ���� ����� ��� � ������-������ </returns>
	PHONE_TYPES* GetPhoneTypeWithID(const long& lID);

	/// <summary> ����� �� �������� �� ������� ���� �������� �������� ��� ��������� ����� ��� ������ ������ </summary>
	/// <param name="recPhoneType"> ������� ����� �� ����, � ���� ���������� �� ��� �� � ID, ���������� �� SQL </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������  </returns>
	BOOL AddPhoneType(PHONE_TYPES& recPhoneType);

	/// <summary> ����� �� ������� �� ����������� ��� ����� ��� ������ ������ </summary>
	/// <param name="recPhoneType"> ������� ������ ����� �� ���� ��������� ����� </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������  </returns>
	BOOL EditPhoneType(PHONE_TYPES recPhoneType);

	/// <summary> ����� �� ��������� �� ��� ����� � ���������� ID �� ������ ���� </summary>
	/// <param name="lID"> ID �� ���� �����, ����� �� ���� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL DeletePhoneType(const long& lID);

private:
	/// <summary> ����� �� ���������� �� �������� ��� ����� � ������-������ �� ��������� </summary>
	/// <param name="recPhoneType"> ������� ������� �� ���� �����, ����� ������ �� ���� ������� � ������-������ </param>
	void UpdateEditedPhoneType(const PHONE_TYPES& recPhoneType);

	/// <summary> ����� �� ���������� �� ��� ����� �� ������-������ �� ��������� </summary>
	/// <param name="lID"> ID �� ���� �����, ����� ������ �� ���� ������ </param>
	void DeletePhoneTypeFromDocArray(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> �����, ����� �� ���� ��� ��������� �� �������� � ������� ������-������ � ������ ������ �� ������� PHONE_TYPES </summary>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	virtual BOOL OnNewDocument();

	/// <summary> �����, ���������� �������������� �� �������� �� ����� </summary>
/// <param name="ar"> �����, ���������� ����������� ��������� �� ����� � ������ �� �������� ����� �/�� ������� </param>
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS


// Implementation
// ----------------

	DECLARE_DYNCREATE(CPhoneTypesDocument)

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
	/// <summary> ����� �� ��������� ��� ������ ��������� ������, � ����� �� ���������� ������ ������ �� ������� PHONE_TYPES </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};

