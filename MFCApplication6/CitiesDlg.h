// CitiesDlg.h 
//

#pragma once
#include "PhoneBook_Header.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

/// <summary> Диалогов клас за таблица CITIES, чрез който се добавя нов ред или се редактира съществуващ такъв </summary>
class CCitiesDlg : public CDialog
{

// Macros
// ----------------

	DECLARE_DYNAMIC(CCitiesDlg) 
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------

private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_DIALOG };  // Определя поведението на кой ресурсен файл този клас описва
#endif


// Constructor / Destructor
// ----------------

public:
	/// <summary> Подразбиращ се конструктор </summary>
	/// <param name="recCity"> Подаден от View град, чиито данни ще се заредят в Edit Control-ите при инициализация на диалога </param>
	/// <param name="pParent"> Указател към родителския прозорец </param>
	CCitiesDlg(CITIES& recCity, CWnd* pParent = nullptr);

	/// <summary> Подразбиращ се деструктор </summary>
	virtual ~CCitiesDlg();


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
	/// <summary> Запазва въведените данни в мембъра-град </summary>
	virtual void OnOK();

	/// <summary> Метод за проверка на въведените от потребителя думи </summary>
	/// <returns> Функцията TRUE при коректно въведени имена и FALSE при наличие на празен интервал в началото на (не)въведена дума </returns>
	const BOOL CheckInput() const;
	

// Members
// ----------------

private:
	/// <summary> Мембър, съответстващ на ресурс EDB_CITY_NAME </summary>
	CEdit m_edbCityName;

	/// <summary> Мембър, съответстващ на ресурс EDB_REGION_NAME </summary>
	CEdit m_edbRegionName;

	/// <summary> Референция към град, съхраняваща въведените стойности </summary>
	CITIES& m_recCity;
};

