#pragma once

#include "global.h"

//PUN_BEGIN

class /*PUN_DLL*/ CThread
{
	friend class CThreadManager;

protected:
	CThread();

public:
	virtual ~CThread() = 0;

private:
	HANDLE	m_hThread;
	HANDLE	m_hStart;

public:
	bool Init();
	virtual void Run() = 0;

public:
	void wait();
	void awake();

public:
	static unsigned int __stdcall ThreadFunc(void* pArg);
};

//PUN_END
