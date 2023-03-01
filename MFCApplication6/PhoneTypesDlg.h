// PhoneTypesDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDlg

/// <summary> Диалогов клас за таблица PHONE_TYPES, чрез който се добавя нов ред или се редактира съществуващ такъв </summary>
class CPhoneTypesDlg : public CDialog
{

// Macros
// ----------------

DECLARE_DYNAMIC(CPhoneTypesDlg)
DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_TYPES_DIALOG };  // Определя поведението на кой ресурсен файл този клас описва
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> Експлицитен конструктор </summary>
	/// <param name="recPhoneType"> Подаден от View вид номер, който ще се зареди в Edit Control-а при инициализацията на диалога </param>
	/// <param name="pParent"> Указател към родителския прозорец </param>
	CPhoneTypesDlg(PHONE_TYPES& recPhoneType, CWnd* pParent = nullptr);

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CPhoneTypesDlg();


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
	/// <summary> Запазва въведените данни в мембъра-референция към вид телефонен номер </summary>
	virtual void OnOK();

	/// <summary> Метод за проверка на въведената от потребителя дума </summary>
	/// <returns> Функцията TRUE при коректно въведена дума и FALSE при наличие на празен интервал в началото на (не)въведената дума </returns>
	BOOL CheckInput();


// Members
// ----------------

private:
	/// <summary> Мембър, съответстващ на ресурс EDB_PHONE_TYPE </summary>
	CEdit m_edbPhoneType;

	/// <summary> Референция към вид номер, в която се съхранява въведеното в диалога при натискане на бутон "Запис" </summary>
	PHONE_TYPES& m_recPhoneType;
};


