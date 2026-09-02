#include "LoadingThread.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ThreadMgr.h"
//#include "Sync.h"

CLoadingThread::CLoadingThread() :
	m_iLoadingMaxCount(6),
	m_iLoadingCount(0)
{
	//GET_SINGLE(CThreadManager)->CreateCriticalSection("LoadingCount"); -> 무슨 함수?
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::SetLoadingMaxCount(int iCount)
{
	m_iLoadingMaxCount = iCount;
}

void CLoadingThread::AddLoadingCount()
{
	//CRITICAL_SECTION*	pCrt = GET_SINGLE(CThreadManager)->FindCriticalSection("LoadingCount");

	//CSync	sync(pCrt); // CSync 는 무슨 타입?

	//++m_iLoadingCount;
	//int	a = 0;

	//for (int i = 0; i < 10000; ++i)
	//{
	//	OutputDebugString(L"하지마\n");
	//}

	//Sleep(3000);
}

int CLoadingThread::GetLoadingCount() const
{
	//CRITICAL_SECTION*	pCrt = GET_SINGLE(CThreadManager)->FindCriticalSection("LoadingCount");

	//CSync	sync(pCrt);

	return m_iLoadingCount;
}

float CLoadingThread::GetPercent() const
{
	//CRITICAL_SECTION*	pCrt = GET_SINGLE(CThreadManager)->FindCriticalSection("LoadingCount");

	//CSync	sync(pCrt);

	return m_iLoadingCount / (float)m_iLoadingMaxCount;
}

void CLoadingThread::Run()
{
	//GET_SINGLE(CSceneManager)->CreateNextScene(false);

	//GET_SINGLE(CSceneManager)->AddSceneComponent<CMainScene>("MainScene", false); // 씬 컴포넌트에서 하는 역할?
}
