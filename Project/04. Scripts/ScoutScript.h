#pragma once
#include "UnitScript.h"
class CScoutScript :
	public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CScoutScript);

public:
	CScoutScript();
	virtual ~CScoutScript();
};

