#pragma once
#include "UnitScript.h"
class CInterceptorScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CInterceptorScript);

public:
	CInterceptorScript();
	virtual ~CInterceptorScript();
};

