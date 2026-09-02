#pragma once
#include "UnitScript.h"

class CDarkTemplarScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CDarkTemplarScript);

public:
	CDarkTemplarScript();
	virtual ~CDarkTemplarScript();
};
