// PhoneTypesDocument.h 
//

#pragma once
#include "pch.h"
#include "PhoneBook_Header.h"

// Кодиране на подсказки, които ще бъдат изпращани на CPhoneTypesView чрез UpdateAllViews()
enum eActionPhoneTypes { eActionPhoneTypesAdd = 1, eActionPhoneTypesEdit = 2, eActionPhoneTypesDelete = 3 };


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument

/// <summary>
/// Клас наследник на CDocument, който съхранява данните от таблица PHONE_TYPES
/// </summary>
class CPhoneTypesDocument : public CDocument
{

// Constructor / Destructor
// ----------------

protected:
	/// <summary> Подразбиращ се конструктор </summary>
	CPhoneTypesDocument() noexcept;

public:
	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPhoneTypesDocument();


// Methods 
// ----------------

public:
	/// <summary> Метод, даващ достъп за четене до масива-мембър с видове номера </summary>
	/// <returns> Функцията връща референция към масива-мембър с указатели към PHONE_NUMBERS </returns>
	const CPhoneTypesArray& GetDocumentPhoneTypesData() const;

	/// <summary> Метод за достъп до вид номер с определено ID в масива-мембър </summary>
	/// <param name="lID"> ID на вида номер, чийто адрес трябва да бъде върнат </param>
	/// <returns> Функцията връща указател към вида номер с подаденото ID или NULL, ако няма такъв вид в масива-мембър </returns>
	PHONE_TYPES* GetPhoneTypeWithID(const long& lID);

	/// <summary> Метод за добавяне на въведен чрез диалогов прозорец вид телефонен номер към всички слоеве </summary>
	/// <param name="recPhoneType"> Съдържа името на вида, а след добавянето му към БД и ID, генерирано от SQL </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL AddPhoneType(PHONE_TYPES& recPhoneType);

	/// <summary> Метод за промяна на съществуващ вид номер във всички слоеве </summary>
	/// <param name="recPhoneType"> Съдържа новите данни за вида телефонен номер </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL EditPhoneType(PHONE_TYPES recPhoneType);

	/// <summary> Метод за изтриване на вид номер с определено ID от всички нива </summary>
	/// <param name="lID"> ID на вида номер, който да бъде изтрит </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL DeletePhoneType(const long& lID);

private:
	/// <summary> Метод за обновяване на променен вид номер в масива-мембър на документа </summary>
	/// <param name="recPhoneType"> Съдържа данните за вида номер, който трябва да бъде обновен в масива-мембър </param>
	void UpdateEditedPhoneType(const PHONE_TYPES& recPhoneType);

	/// <summary> Метод за премахване на вид номер от масива-мембър на документа </summary>
	/// <param name="lID"> ID на вида номер, който трябва да бъде изтрит </param>
	void DeletePhoneTypeFromDocArray(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> Метод, който се вика при създаване на документ и запълва масива-мембър с всички редове от таблица PHONE_TYPES </summary>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	virtual BOOL OnNewDocument();

	/// <summary> Метод, осигуряващ сериализацията на обектите от класа </summary>
/// <param name="ar"> Обект, осигуряващ универсален механизъм за запис и четене на всякакви данни в/от паметта </param>
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS


// Implementation
// ----------------

	DECLARE_DYNCREATE(CPhoneTypesDocument)

#ifdef _DEBUG
	/// <summary> Валидира вътрешното състояние на обектите от класа </summary>
	virtual void AssertValid() const;

	/// <summary> Съхранява информация за обект от класа при възникване на проблем, прекъсващ изпълнението </summary>
	/// <param name="dc"> Обект, съхраняващ информация за обекта и представящ я по разбираем за програмиста начин </param>
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
	/// <summary> Масив от указатели към видове телефонни номера, в който се съхраняват всички редове от таблица PHONE_TYPES </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};

