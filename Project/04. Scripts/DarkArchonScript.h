#pragma once
#include "UnitScript.h"
class CDarkArchonScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CDarkArchonScript);

public:
	CDarkArchonScript();
	virtual ~CDarkArchonScript();
};

