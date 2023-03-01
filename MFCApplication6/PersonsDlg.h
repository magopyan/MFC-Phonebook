// PersonsDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"
#include "PhoneNumbersDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDlg

/// <summary> Диалогов клас за таблица PERSONS, чрез който се добавя нов абонат или се редактира съществуващ такъв </summary>
class CPersonsDlg : public CDialog
{

// Macros
// ----------------

	DECLARE_DYNAMIC(CPersonsDlg)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };  // Определя поведението на кой ресурсен файл този клас описва; 
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> Експлицитен конструктор </summary>
	/// <param name="oPersonAndPhones"> Структура, съдържаща абонат и неговите номера </param>
	/// <param name="oCitiesMap"> Карта с градовете, които да се заредят в ComboBox </param>
	/// <param name="oPhoneTypesMap"> Карта с видовете номера, които да се заредят в ListCtrl и ComboBox на CPhoneNumebersDlg  </param>
		/// <param name="pParent"> Указател към родителския прозорец </param>
	CPersonsDlg(CPerson& oPersonAndPhones, CCitiesMap& oCitiesMap, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent = nullptr);

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPersonsDlg();


// MFC Overrides
// ----------------

private:
	/// <summary> Свързва ресурсите на диалоговия прозорец със съответните им мембъри </summary>
	void DoDataExchange(CDataExchange* pDX) override;


// Overrides
// ----------------

	/// <summary> Инициализира диалога и извършва операции, подготвящи го за работа </summary>
	virtual BOOL OnInitDialog();


// Methods
// ----------------

private:
	/// <summary> Запазва промените върху данните, направени в рамките на диалоговия прозорец </summary>
	virtual void OnOK();

	/// <summary> Метод, изпълняващ се при Десен бутон->Add. Позволява добавяне на нов телефонен номер към абоната </summary>
	virtual void OnAdd();

	/// <summary> Метод, изпълняващ се при Десен бутон->Edit. Позволява модифициране на избран от списъка номер </summary>
	virtual void OnEdit();

	/// <summary> Метод, изпълняващ се при Десен бутон->Delete. Осъществява изтриване на избран от списъка номер </summary>
	virtual void OnDelete();

	/// <summary> Метод, изрисуващ контекстно меню при натиснат десен бутон в рамките на ресурса от тип ListCtrl </summary>
	/// <param name="pNMHDR"> Указател към структура, носеща информация за известяващо съобщение </param>
	/// <param name="pResult"> Указател към цяло число, означаващ определен резултат </param>
	afx_msg void MenuOnRightClick(NMHDR* pNMHDR, LRESULT* pResult);

	/// <summary> Метод за проверка на въведените от потребителя данни </summary>
	/// <returns> Функцията TRUE при коректно въведени данни и FALSE при некоректно въведени </returns>
	BOOL CheckInput();


// Members
// ----------------

private:
	/// <summary> Мембър, съответстващ на ресурс EDB_FIRST_NAME </summary>
	CEdit m_edbFirstName;
	
	/// <summary> Мембър, съответстващ на ресурс EDB_SECOND_NAME </summary>
	CEdit m_edbSecondName;
	
	/// <summary> Мембър, съответстващ на ресурс EDB_THIRD_NAME </summary>
	CEdit m_edbThirdName;
	
	/// <summary> Мембър, съответстващ на ресурс EDB_EGN </summary>
	CEdit m_edbEGN;
	
	/// <summary> Мембър, съответстващ на ресурс EDB_ADRESS </summary>
	CEdit m_edbAdress;
	
	/// <summary> Мембър, съответстващ на ресурс CMB_CITY </summary>
	CComboBox m_cmbCity;

	/// <summary> Мембър, съответстващ на ресурс LSC_PHONE_NUMBERS </summary>
	CListCtrl m_lscPhoneNumbers;

	/// <summary> Карта с градовете, които се зареждат в ComboBox </summary>
	CCitiesMap& m_oCitiesMap;

	/// <summary> Карта с видовете номера, които се зареждат в ListCtrl и ComboBox в диалога CPhoneNumbersDlg </summary>
	CPhoneTypesMap& m_oPhoneTypesMap;

	/// <summary> Структура, обединяваща абонат и телефонните му номера </summary>
	CPerson& m_oPersonAndPhones;
};


