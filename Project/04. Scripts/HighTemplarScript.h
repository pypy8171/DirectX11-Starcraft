#pragma once
#include "UnitScript.h"
class CHighTemplarScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CHighTemplarScript);

public:
	CHighTemplarScript();
	virtual ~CHighTemplarScript();
};

