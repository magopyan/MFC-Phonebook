// TypedPtrArrayAutoDelete.h
//

#pragma once


 /////////////////////////////////////////////////////////////////////////////
// CTypedPtrArrayAutoDelete

/// <summary>
/// Клас наследник на CTypedPtrArray, който предефинира деструктора му, така че да се освобождава автоматично паметта на адреса, който указателят сочи
/// Използването на template прави възможно използването на този клас за всеки CTypedPtrArray, независимо от типа на сочените елементи
/// </summary>
template <typename TYPE> 
class CTypedPtrArrayAutoDelete : public CTypedPtrArray<CPtrArray, TYPE*>
{

// Overrides Destructor

public:
	/// <summary> Предефиниран деструктор, автоматично освобождаващ паметта, сочена от елементите на масива </summary>
	~CTypedPtrArrayAutoDelete() override
	{
		for (INT_PTR i = 0; i < GetCount(); i++)
		{
			delete GetAt(i);
			RemoveAt(i);
		}
	}
};
