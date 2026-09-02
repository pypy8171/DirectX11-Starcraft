#include "Thread.h"
#include <process.h>
//PUN_USING -> ¹«½¼ ¸ÅÅ©·Î?

CThread::CThread()
{
}


CThread::~CThread()
{
	if (m_hThread)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
	}
}

bool CThread::Init()
{
	m_hStart = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunc, this, 0, nullptr); // ??

	return true;
}

void CThread::wait()
{
	WaitForSingleObject(m_hStart, INFINITE);
}

void CThread::awake()
{
	SetEvent(m_hStart);
}

unsigned int CThread::ThreadFunc(void * pArg)
{
	CThread*	pThread = (CThread*)pArg;

	pThread->wait();

	pThread->Run();

	return 0;
}
