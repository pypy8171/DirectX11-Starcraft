#pragma once
#include "UnitScript.h"
class CCarrierScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CCarrierScript);

public:
	CCarrierScript();
	virtual ~CCarrierScript();
};

