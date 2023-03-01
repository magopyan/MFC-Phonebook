// PersonsView.h 
//

#pragma once
#include "pch.h"
#include "afxcview.h"  
#include "PersonsDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsView

/// <summary> Имплементация на CListView, с която се презентират редовете от таблица PERSONS </summary>
class CPersonsView : public CListView
{

// Constructor / Destructor
// ----------------
public:
	/// <summary> Подразбиращ се конструктор </summary>
	CPersonsView() noexcept;

	

public:
	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPersonsView() override;


// Methods
// ----------------

private:
	/// <summary> Метод за получаване на достъп до документа, обвързан с този клас </summary>
	/// <returns> Функцията връща указател към документа </returns>
	CPersonsDocument* GetDocument() const;

	/// <summary> Метод за създаване на колоните </summary>
	void InsertPersonsColumns();

	/// <summary> Метод за попълване на редовете с данните от документа (след като вече са създадени колоните) </summary>
	/// <returns> Функцията връща резултат TRUE при успех и FALSE при липса на данни в документа </returns>
	BOOL FillPersonsViewRows();

	/// <summary> Метод, който се вика при промяна на съдържанието на документа, за да се актуализира и списъчния View  </summary>
	/// <param name="pSender"> Указател към базовия CView, който трябва да се актуализира </param>
	/// <param name="lHint"> Дава информация за модификацията </param>
	/// <param name="pHint"> Сочи обект, носещ информация за модификацията </param>
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;

	/// <summary> Метод за добавяне на нов абонат с негови номера чрез въвеждане на данни в диалогов прозорец </summary>
	void OnAdd();

	/// <summary> Метод за добавяне на новия абонат към View при обновяване на View </summary>
	/// <param name="recPerson"> Съдържа данните, които ще се презентират на новодобавения ред </param>
	void AddPersonToView(const PERSONS& recPerson);

	/// <summary> Метод за промяна на ред от View, която се отразява на всички слоеве </summary>
	void OnEdit();

	/// <summary> Метод, отразяващ промяната в модифицирания абонат и номерата му във View </summary>
	/// <param name="recPerson"> Съдържа данните, с които да се обнови реда </param>
	void EditPersonInView(const PERSONS& recPerson);

	/// <summary> Метод за изтриване на ред от View и всички други слоеве </summary>
	void OnDelete();

	/// <summary> Метод за изтриване на реда от View при обновяване на View </summary>
	/// <param name="lID"> ID на абоната, който да бъде премахнат от View </param>
	void DeletePersonFromView(const long& lID);


// Overrides
// ----------------

public:
	/// <summary> Метод за първоначалното инициализиране на View. Определя стила, създава колоните и попълва редовете </summary>
	void OnInitialUpdate() override;

	/// <summary> Метод за създаване на меню при натискане на десен бутон в рамките на View </summary>
	/// <param name="pWnd"> Указател към прозореца </param>
	/// <param name="pos"> Съдържа двете координати, които определят къде в прозореца да се изчертае менюто </param>
	void OnContextMenu(CWnd* pWnd, CPoint pos);

	/// <summary> Метод, изпълняващ чертаенето в рамките на View </summary>
	/// <param name="pDC"> Клас, дефиниращ обекти според контекста на устройството </param>
	virtual void OnDraw(CDC* pDC) override;

	/// <summary> Метод, изпълняващ се преди създаването на прозореца на View </summary>
	/// <param name="pDC"> Структура, съдържаща ранотипни данни </param>
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

protected:
	/// <summary> Метод, изпълняващ се преди принтирането или преглеждането на документ </summary>
	/// <param name="pDC"> Обект, съхраняващ информация за операция принтиране или преглеждане на документ </param>
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo) override;

	/// <summary> Метод, изпълняващ се при начало на принтиране или преглеждане на документ; Разпределя ресурси, нужни за тези операции </summary>
	/// <param name="pDC"> Структура, съдържаща ранотипни данни </param>
	/// <param name="pInfo"> Обект, съхраняващ информация за операция принтиране или преглеждане на документ </param>
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) override;

	/// <summary> Метод, изпълняващ се след принтиране или преглеждане на документ; Освобождава заетите от OnBeginPrinting() ресурси </summary>
	/// <param name="pDC"> Структура, съдържаща ранотипни данни </param>
	/// <param name="pDC"> Обект, съхраняващ информация за операция принтиране или преглеждане на документ </param>
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) override;


// Implementation
// ----------------

	DECLARE_DYNCREATE(CPersonsView)

#ifdef _DEBUG
	/// <summary> Валидира вътрешното състояние на обектите от класа </summary>
	virtual void AssertValid() const override;

	/// <summary> Съхранява информация за обект от класа при възникване на проблем, прекъсващ изпълнението </summary>
	/// <param name="dc"> Обект, съхраняващ информация за обекта и представящ я по разбираем за програмиста начин </param>
	virtual void Dump(CDumpContext& dc) const override;
#endif


// Generated message map functions
// ----------------

protected:
	DECLARE_MESSAGE_MAP()
};