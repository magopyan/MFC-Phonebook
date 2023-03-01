// PhoneNumbersDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDlg

/// <summary> Диалогов клас за таблица PHONE_NUMBERS, чрез който се добавя нов ред или се редактира съществуващ такъв </summary>
class CPhoneNumbersDlg : public CDialog
{

// Macros
// ----------------

DECLARE_DYNAMIC(CPhoneNumbersDlg)
DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_DIALOG };  // Определя поведението на кой ресурсен файл този клас описва; 
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> Експлицитен конструктор </summary>
	/// <param name="recPhoneNumber"> Референция към номер, който да се зареди в полето за въвеждане при поискана промяна на номер </param>
	/// <param name="oPhoneTypesMap"> Референция към карта, съдържаща видовете телефонни номера, които да се заредят в ComboBox-а </param>
	/// <param name="pParent"> Указател към родителския прозорец </param>
	CPhoneNumbersDlg(PHONE_NUMBERS& recPhoneNumber, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent = nullptr);

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPhoneNumbersDlg();


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
	/// <summary> Запазва въведените данни в мембъра-номер </summary>
	virtual void OnOK();

	/// <summary> Метод за проверка на въведения от потребителя номер </summary>
	/// <returns> Функцията TRUE при коректно въведен номер и FALSE при наличие на празен интервал в началото на номера или неизбран вид </returns>
	BOOL CheckInput();


// Members
// ----------------

private:
	/// <summary> Мембър, съответстващ на ресурс EDB_PHONE_NUMBER </summary>
	CEdit m_edbPhoneNumber;

	/// <summary> Мембър, съответстващ на ресурс CMB_PHONE_TYPE </summary>
	CComboBox m_cmbPhoneType;

	/// <summary> Карта с ключ - ID-тата на видовете номера и стойност - обект от дисковата структура за вид номер </summary>
	CPhoneTypesMap& m_oPhoneTypesMap;

	/// <summary> Мембър-телефонен номер, в който се съхранява въведения в диалога номер при натискане на бутон "Запис" </summary>
	PHONE_NUMBERS& m_recPhoneNumber;
};


