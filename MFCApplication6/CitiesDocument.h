// CitiesDocument.h 
//

#pragma once
#include "pch.h"
#include "PhoneBook_Header.h"

// Кодиране на подсказки, които ще бъдат изпращани на CCitiesView чрез UpdateAllViews()
enum eActionCities { eActionCitiesAdd = 1, eActionCitiesEdit = 2, eActionCitiesDelete = 3 };


/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument

/// <summary>
/// Клас наследник на CDocument, който съхранява данните от таблица CITIES
/// </summary>
class CCitiesDocument : public CDocument
{
	

// Constructor / Destructor
// ----------------

private: 
	/// <summary> Подразбиращ се конструктор </summary>
	CCitiesDocument() noexcept;

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CCitiesDocument();


// Methods 
// ----------------

public:
	/// <summary> Метод, даващ достъп за четене до масива-мембър с градове </summary>
	/// <returns> Функцията връща референция към масива-мембър с указатели към CITIES </returns>
	const CCitiesArray& GetDocumentCitiesData() const;

	/// <summary> Метод за достъп до град с определено ID в масива-мембър </summary>
	/// <param name="lID"> ID на града, чийто адрес трябва да бъде върнат </param>
	/// <returns> Функцията връща указател към града с подаденото ID или NULL, ако няма такъв град в масива-мембър </returns>
	CITIES* GetCityWithID(const long& lID);

	/// <summary> Метод за добавяне на въведен чрез диалогов прозорец град към всички слоеве </summary>
	/// <param name="recCity"> Съдържа името на града и региона му, а след добавянето му към БД и ID, генерирано му от SQL </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL AddCity(CITIES& recCity);

	/// <summary> Метод за промяна на съществуващ град във всички слоеве </summary>
	/// <param name="recCity"> Съдържа новите данни за града </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL EditCity(CITIES recCity);

	/// <summary> Метод за изтриване на град с определено ID от всички нива </summary>
	/// <param name="lID"> ID на града, който ще бъде изтрит </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL DeleteCity(const long& lID);

private:	
	/// <summary> Метод за обновяване на променен град в масива-мембър на документа </summary>
	/// <param name="recCity"> Съдържа данните за града, който трябва да бъде обновен в масива-мембър </param>
	const void UpdateEditedCity(const CITIES& recCity);

	/// <summary> Метод за премахване на град от масива-мембър на документа </summary>
	/// <param name="lID"> ID на града, който трябва да бъде изтрит </param>
	const void DeleteCityFromDocArray(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> Метод, който се вика при създаване на документ и запълва масива-мембър с всички редове от таблица CITIES </summary>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	virtual BOOL OnNewDocument();

	/// <summary> Метод, осигуряващ сериализацията на обектите от класа </summary>
	/// <param name="ar"> Обект, осигуряващ универсален механизъм за запис и четене на всякакви данни в/от паметта </param>
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif 


// Implementation
// ----------------

	DECLARE_DYNCREATE(CCitiesDocument) 

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
	/// <summary> Масив от градове, в който се съхраняват всички редове от таблица CITIES </summary>
	CCitiesArray m_oCitiesArray;
};
