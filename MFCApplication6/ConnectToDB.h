// ConnectToDB.h
//

#pragma once
#include "atldbcli.h" // за CDBPropSet и CDataSource


/////////////////////////////////////////////////////////////////////////////
// CConnectToDB

/// <summary> Клас-Singleton за установяване на връзка с базата данни PhoneBook </summary>
class CConnectToDB
{

// Constructor / Destructor
// ----------------

private:
	/// <summary> Подразбиращ се конструктор  </summary>
	CConnectToDB();

	/// <summary> Подразбиращ се деструктор  </summary>
	~CConnectToDB();
	

// Methods
// ----------------

public:
	/// <summary> Статичен метод за еднократно инициализиране на статичния мембър-указател към класа </summary>
	/// <returns> Връща адреса, който статичният мембър-указател сочи </returns>
	static CConnectToDB* GetInstance();

	/// <summary> Метод за достъп до мембъра-обект за връзка с БД </summary>
	/// <returns> Връща референция към мембъра-връзка с БД  </returns>
	CDataSource& GetDataSource();

	/// <summary> Метод за установяване на връзка с БД </summary>
	/// <returns> Връща TRUE при успех и FALSE при възникнала грешка </returns>
	BOOL OpenConnection();

	/// <summary> Метод за промяна на връзката с БД, така че през нея да е възможно подаването на заявки UPDATE, INSERT и DELETE </summary>
	/// <param name="oUpdateDBPropSet"> Приема инициализиран обект от CDBPropSet, който трябва да бъде пренастроен </param>
	void UpdateDBPropSet(CDBPropSet& oUpdateDBPropSet);


// Members
// ----------------

private:
	/// <summary> Обект-връзка с БД </summary>
	CDataSource m_oConnection;

	/// <summary> Статичен указател към единствения обект за връзка с БД </summary>
	static CConnectToDB* _pInstance;
};

