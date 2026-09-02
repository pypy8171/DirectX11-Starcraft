#pragma once
#include "UnitScript.h"
class CGameObject;

class CZealotScript
	: public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();

public:


public:
	CLONE(CZealotScript);

public:
	CZealotScript();
	virtual ~CZealotScript();
};

