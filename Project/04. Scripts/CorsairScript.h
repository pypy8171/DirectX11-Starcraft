#pragma once
#include "UnitScript.h"
class CCorsairScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CCorsairScript);

public:
	CCorsairScript();
	virtual ~CCorsairScript();
};

