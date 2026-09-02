#pragma once

#include "Thread.h"

//PUN_USING

class CLoadingThread :
	public CThread
{
public:
	CLoadingThread();
	~CLoadingThread();

private:
	int	m_iLoadingCount;
	int	m_iLoadingMaxCount;

public:
	void SetLoadingMaxCount(int iCount);
	void AddLoadingCount();
	int GetLoadingCount()	const;
	float GetPercent()	const;

public:
	virtual void Run();
};

