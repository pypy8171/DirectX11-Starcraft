#pragma once

#include "YongEngine/Script.h"

class CGameObject;

class CProtossUIScript
	: public CScript
{

public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CProtossUIScript);

public:
	CProtossUIScript();
	virtual ~CProtossUIScript();
};

