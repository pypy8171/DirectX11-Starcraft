#pragma once
#include "YongEngine/Script.h"

class CGameObject;

class CPortraitScript
	: public CScript
{
public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CPortraitScript);

public:
	CPortraitScript();
	virtual ~CPortraitScript();
};

