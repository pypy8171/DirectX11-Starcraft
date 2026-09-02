#pragma once
#include "YongEngine/Script.h"
#include "UnitScript.h"
class CGameObject;

class CDragoonScript
	: public CUnitScript
{
public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CDragoonScript);

public:
	CDragoonScript();
	virtual ~CDragoonScript();
};

