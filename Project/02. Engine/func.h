#pragma once

#include "global.h"

int GetSizeofFormat(DXGI_FORMAT _eFormat);

template<typename T>
void Safe_Delete_list(list<T> _list)
{
	typename list<T>::iterator iter = _list.begin();
	for (; iter != _list.end(); ++iter)
	{
		if (*iter != NULL)
			delete *iter;
	}
}

template<typename T>
void Safe_Delete_ListNode(list<T>& _list)
{
	if (0 != _list.size())
	{
		typename list<T>::iterator iter = _list.begin();

		if (NULL != *iter)
		{
			delete *iter;
			iter = _list.erase(iter); // _list.erase(iter);
		}
	}
}

template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (UINT i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
		{
			delete _vec[i];
			_vec[i] = nullptr;
		}
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		if (NULL != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}

}

//template<typename T1, typename T2>
//void Safe_Delete_UMap(unordered_map<T1, T2>& _map)
//{
//	typename unordered_map<T1, T2>::iterator iter = _map.begin();
//	for (; iter != _map.end(); ++iter)
//	{
//		if (NULL != iter->second)
//		{
//			delete iter->second;
//			iter->second = nullptr;
//		}
//	}
//}

template <typename T, int iSize>
void Safe_Delete_Array(T* (&_pArr)[iSize])
{
	for (int i = 0; i < iSize; ++i)
	{
		SAFE_DELETE(_pArr[i]);
	}
}

float Lerf(float _fStart, float _fDest, float _fRatio);

void SaveWString(const wstring& _str, FILE* _pFile);
wchar_t* LoadWString(FILE* _pFile);

//int iArr[10] = {};
//
//int* pArr = iArr;
//int (&test)[10] = iArr; // 배열 이름의 진짜 타입 // 가변으로는 의미가 없는 선언 // 하지만 템플릿 쓸때는 유용
//
//int iSize = sizeof(iArr); // 40
//iSize = sizeof(pArr); // 4