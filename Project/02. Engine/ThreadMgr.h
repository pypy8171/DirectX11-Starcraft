#pragma once

#include "global.h"
#include <unordered_map>
//PUN_BEGIN

class /*PUN_DLL*/ CThreadManager
{
private:
	unordered_map<string, class CThread*>	m_mapThread;
	unordered_map<string, CRITICAL_SECTION>	m_mapCriticalSection;

public:
	bool Init();
	class CThread* FindThread(const string& strName);
	bool DeleteThread(const string& strName);
	bool CreateCriticalSection(const string& strName);
	CRITICAL_SECTION* FindCriticalSection(const string& strName);

public:
	template <typename T>
	T* Create(const string& strName)
	{
		T*	pThread = FindThread(strName);

		if (pThread)
			return pThread;

		pThread = new T;

		if (!pThread->Init())
		{
			SAFE_DELETE(pThread);
			return nullptr;
		}

		m_mapThread.insert(make_pair(strName, pThread));

		return pThread;
	}

	SINGLE(CThreadManager)
};

//PUN_END
