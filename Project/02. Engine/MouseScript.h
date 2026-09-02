#pragma once
#include "Script.h"
class CMouseScript :
	public CScript
{
private:
	CScript * m_pMark;

public:
	virtual int update();
	virtual void awake();

public:
	void SetMark(CScript* _pMark) { m_pMark = _pMark; }

public:
	CLONE(CMouseScript);

public:
	CMouseScript();
	virtual ~CMouseScript();
};

