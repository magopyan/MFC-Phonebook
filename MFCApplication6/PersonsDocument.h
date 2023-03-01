// PersonsDocument.h 
//

#pragma once
#include "pch.h"
#include "PhoneBook_Header.h"

// �������� �� ���������, ����� �� ����� ��������� �� CPersonsView ���� UpdateAllViews()
enum eActionPersons { eActionAddPerson = 1, eActionEditPerson = 2, eActionDeletePerson = 3 };


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

/// <summary>
/// ���� ��������� �� CDocument, ����� ��������� ������� �� ������� PERSONS
/// </summary>
class CPersonsDocument : public CDocument
{

// Constructor / Destructor
// ----------------

protected:
	/// <summary> ����������� �� ����������� </summary>
	CPersonsDocument() noexcept;


public:
	/// <summary> ����������� �� ���������� </summary>
	virtual ~CPersonsDocument();


// Methods 
// ----------------

public:
	/// <summary> �����, ����� ������ �� ������ �� ������-������ � ������� </summary>
	/// <returns> ��������� ����� ���������� ��� ������-������ � ��������� ��� PERSONS </returns>
	const CPersonsArray& GetDocumentPersonsData() const;

	/// <summary> ����� �� ��������� �� �� �� ����������� ������ �� ����� ������  </summary>
	/// <param name="lPersonID"> ID �� �������, ����� ������ �� �� ������� </param>
	/// <param name="oPhoneNumbersArray"> �����, ����� �� ������� �������� </param>
	/// <returns> ��������� ����� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL GetPhoneNumbersArray(const long& lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);

	/// <summary> �����, ����� ������ �� ������ �� ��������� �� ��, �� �� ����� �� �� ������� ��� View �� ����������� �� ������� </summary>
	/// <returns> ��������� ����� ���������� ��� CMap � ��������� </returns>
	CCitiesMap& GetDocumentCitiesData();

	/// <summary> �����, ����� ������ �� ������ �� �������� ������ �� �� </summary>
	/// <returns> ��������� ����� ���������� ��� CMap � �������� ������ </returns>
	CPhoneTypesMap& GetDocumentPhoneTypesData();

	/// <summary> ����� �� ������ �� ������ � ���������� ID � ������-������ </summary>
	/// <param name="lID"> ID �� �������, ����� �� �� ������� ���� ������-������ </param>
	/// <returns> ��������� ����� �������� ��� ������� � ���������� ID ��� NULL, ��� ���� ����� ������ � ������-������ </returns>
	const PERSONS* GetPersonWithID(const long& lID) const;


	/// <summary> ����� �� �������� �� ������� ���� �������� �������� ������ � �������� �� ��� ������ ������ </summary>
	/// <param name="oPersonAndPhones"> ����, ������������� ����� ������ � ������ ��������� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������  </returns>
	BOOL AddPerson(CPerson& oPersonAndPhones);

	/// <summary> ����� �� ������� �� ����������� ������ � �������� �� ��� ������ ������ </summary>
	/// <param name="oPersonAndPhones"> ����, ������������� ���������� ������ � �������� ��������� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������  </returns>
	BOOL EditPerson(CPerson& oPersonAndPhones);

	/// <summary> ����� �� ��������� �� ������ � ���������� ID � �������� �� ������ �� ������ ���� </summary>
	/// <param name="lID"> ID �� �������, ����� �� ���� ������ </param>
	/// <returns> ��������� ����� �������� TRUE ��� ����� � FALSE ��� ���������� ������ </returns>
	BOOL DeletePerson(const long& lID);

private:
	/// <summary> ����� �� ���������� �� �������� ������ � ������-������ �� ��������� </summary>
	/// <param name="recPerson"> ������� ������� �� �������, ����� ������ �� ���� ������� � ������-������ </param>
	void UpdateEditedPerson(const PERSONS& recPerson);

	/// <summary> ����� �� ���������� �� ������ �� ������-������ �� ��������� </summary>
	/// <param name="lID"> ID �� �������, ����� ������ �� ���� ������ </param>
	void DeletePersonFromDocArray(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> �����, ����� �� ���� ��� ��������� �� �������� � ������� ������-������ � ������ ������ �� ������� PERSONS </summary>
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

	DECLARE_DYNCREATE(CPersonsDocument)

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
	/// <summary> ����� �� �������, � ����� �� ���������� ������ ������ �� ������� PERSONS </summary>
	CPersonsArray m_oPersonsArray;

	/// <summary> ����� � ������ ������� �� ��, ��������� ID �� ����� ���� � ����� �� ��������� ��������� �� ���� </summary>
	CCitiesMap m_oCitiesMap;

	/// <summary> ����� � ������ ������ ������ �� ��, ��������� ID �� ����� ��� � ����� �� ��������� ��������� �� ��� ����� </summary>
	CPhoneTypesMap m_oPhoneTypesMap;
};

