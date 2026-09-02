#pragma once
#include "UnitScript.h"
class CArchonScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CArchonScript);

public:
	CArchonScript();
	virtual ~CArchonScript();
};

