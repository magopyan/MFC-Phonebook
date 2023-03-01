// TypedPtrArrayAutoDelete.h
//

#pragma once


 /////////////////////////////////////////////////////////////////////////////
// CTypedPtrArrayAutoDelete

/// <summary>
/// ���� ��������� �� CTypedPtrArray, ����� ����������� ����������� ��, ���� �� �� �� ����������� ����������� ������� �� ������, ����� ���������� ����
/// ������������ �� template ����� �������� ������������ �� ���� ���� �� ����� CTypedPtrArray, ���������� �� ���� �� �������� ��������
/// </summary>
template <typename TYPE> 
class CTypedPtrArrayAutoDelete : public CTypedPtrArray<CPtrArray, TYPE*>
{

// Overrides Destructor

public:
	/// <summary> ������������ ����������, ����������� ������������ �������, ������ �� ���������� �� ������ </summary>
	~CTypedPtrArrayAutoDelete() override
	{
		for (INT_PTR i = 0; i < GetCount(); i++)
		{
			delete GetAt(i);
			RemoveAt(i);
		}
	}
};
