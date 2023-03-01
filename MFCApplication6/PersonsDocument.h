// PersonsDocument.h 
//

#pragma once
#include "pch.h"
#include "PhoneBook_Header.h"

// Кодиране на подсказки, които ще бъдат изпращани на CPersonsView чрез UpdateAllViews()
enum eActionPersons { eActionAddPerson = 1, eActionEditPerson = 2, eActionDeletePerson = 3 };


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

/// <summary>
/// Клас наследник на CDocument, който съхранява данните от таблица PERSONS
/// </summary>
class CPersonsDocument : public CDocument
{

// Constructor / Destructor
// ----------------

protected:
	/// <summary> Подразбиращ се конструктор </summary>
	CPersonsDocument() noexcept;


public:
	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPersonsDocument();


// Methods 
// ----------------

public:
	/// <summary> Метод, даващ достъп за четене до масива-мембър с абонати </summary>
	/// <returns> Функцията връща референция към масива-мембър с указатели към PERSONS </returns>
	const CPersonsArray& GetDocumentPersonsData() const;

	/// <summary> Метод за прочитане от БД на телефонните номера на даден абонат  </summary>
	/// <param name="lPersonID"> ID на абоната, чийто номера да се изчетат </param>
	/// <param name="oPhoneNumbersArray"> Масив, който да съхрани номерата </param>
	/// <returns> Функцията връща TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL GetPhoneNumbersArray(const long& lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);

	/// <summary> Метод, даващ достъп за четене до градовете от БД, за да могат да се заредят във View за съответните им абонати </summary>
	/// <returns> Функцията връща референция към CMap с градовете </returns>
	CCitiesMap& GetDocumentCitiesData();

	/// <summary> Метод, даващ достъп за четене до видовете номера от БД </summary>
	/// <returns> Функцията връща референция към CMap с видовете номера </returns>
	CPhoneTypesMap& GetDocumentPhoneTypesData();

	/// <summary> Метод за достъп до абонат с определено ID в масива-мембър </summary>
	/// <param name="lID"> ID на абоната, който да се достъпи чрез масива-мембър </param>
	/// <returns> Функцията връща указател към абоната с подаденото ID или NULL, ако няма такъв абонат в масива-мембър </returns>
	const PERSONS* GetPersonWithID(const long& lID) const;


	/// <summary> Метод за добавяне на въведен чрез диалогов прозорец абонат и номерата му към всички слоеве </summary>
	/// <param name="oPersonAndPhones"> Клас, окомплектоващ новия абонат с новите телефонни номера </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL AddPerson(CPerson& oPersonAndPhones);

	/// <summary> Метод за промяна на съществуващ абонат и номерата му във всички слоеве </summary>
	/// <param name="oPersonAndPhones"> Клас, окомплектоващ променения абонат с неговите телефонни номера </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка  </returns>
	BOOL EditPerson(CPerson& oPersonAndPhones);

	/// <summary> Метод за изтриване на абонат с определено ID и всичките му номера от всички нива </summary>
	/// <param name="lID"> ID на абоната, който ще бъде изтрит </param>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL DeletePerson(const long& lID);

private:
	/// <summary> Метод за обновяване на променен абонат в масива-мембър на документа </summary>
	/// <param name="recPerson"> Съдържа данните за абоната, който трябва да бъде обновен в масива-мембър </param>
	void UpdateEditedPerson(const PERSONS& recPerson);

	/// <summary> Метод за премахване на абонат от масива-мембър на документа </summary>
	/// <param name="lID"> ID на абоната, който трябва да бъде изтрит </param>
	void DeletePersonFromDocArray(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> Метод, който се вика при създаване на документ и запълва масива-мембър с всички редове от таблица PERSONS </summary>
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

	DECLARE_DYNCREATE(CPersonsDocument)

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
	/// <summary> Масив от абонати, в който се съхраняват всички редове от таблица PERSONS </summary>
	CPersonsArray m_oPersonsArray;

	/// <summary> Карта с всички градове от БД, свързваща ID на всеки град с обект от дисковата структура за град </summary>
	CCitiesMap m_oCitiesMap;

	/// <summary> Карта с всички видове номера от БД, свързваща ID на всеки вид с обект от дисковата структура за вид номер </summary>
	CPhoneTypesMap m_oPhoneTypesMap;
};

