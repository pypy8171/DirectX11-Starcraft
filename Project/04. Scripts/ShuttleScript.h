#pragma once
#include "UnitScript.h"
class CShuttleScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();



public:
	CLONE(CShuttleScript);

public:
	CShuttleScript();
	virtual ~CShuttleScript();
};

