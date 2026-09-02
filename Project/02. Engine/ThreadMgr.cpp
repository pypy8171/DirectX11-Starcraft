#include "ThreadMgr.h"
#include "Thread.h"

//PUN_USING

//DEFINITION_SINGLE(CThreadManager)

CThreadManager::CThreadManager()
{
}


CThreadManager::~CThreadManager()
{
	unordered_map<string, CRITICAL_SECTION>::iterator	iter;
	unordered_map<string, CRITICAL_SECTION>::iterator	iterEnd = m_mapCriticalSection.end();

	for (iter = m_mapCriticalSection.begin(); iter != iterEnd; ++iter)
	{
		DeleteCriticalSection(&iter->second);
	}

	m_mapCriticalSection.clear();
	//Safe_Delete_Map(m_mapThread);
}

bool CThreadManager::Init()
{
	return true;
}

CThread * CThreadManager::FindThread(const string & strName)
{
	unordered_map<string, CThread*>::iterator	iter = m_mapThread.find(strName);

	if (iter == m_mapThread.end())
		return nullptr;

	return iter->second;
}

bool CThreadManager::DeleteThread(const string & strName)
{
	unordered_map<string, CThread*>::iterator	iter = m_mapThread.find(strName);

	if (iter == m_mapThread.end())
		return false;

	SAFE_DELETE(iter->second);

	m_mapThread.erase(iter);

	return true;
}

bool CThreadManager::CreateCriticalSection(const string & strName)
{
	if (FindCriticalSection(strName))
		return false;

	CRITICAL_SECTION	tCrt;

	InitializeCriticalSection(&tCrt);

	m_mapCriticalSection.insert(make_pair(strName, tCrt));

	return true;
}

CRITICAL_SECTION * CThreadManager::FindCriticalSection(const string & strName)
{
	unordered_map<string, CRITICAL_SECTION>::iterator	iter = m_mapCriticalSection.find(strName);

	if (iter == m_mapCriticalSection.end())
		return nullptr;

	return &iter->second;
}
