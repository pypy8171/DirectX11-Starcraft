#pragma once
#include "UnitScript.h"
class CArbiterScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CArbiterScript);

public:
	CArbiterScript();
	virtual ~CArbiterScript();
};

