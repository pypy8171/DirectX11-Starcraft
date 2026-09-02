#pragma once
#include "UnitScript.h"
class CReaverScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CReaverScript);

public:
	CReaverScript();
	virtual ~CReaverScript();
};

