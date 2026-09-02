#pragma once

#include "YongEngine/Script.h"

class CGameObject;

class CIconScript
	: public CScript
{
public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CIconScript);
public:
	CIconScript();
	~CIconScript();
};

