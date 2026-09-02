#pragma once
#include "UnitScript.h"
class CObserverScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CObserverScript);

public:
	CObserverScript();
	virtual ~CObserverScript();
};

