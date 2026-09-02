#pragma once

#include "YongEngine/Script.h"

class CGameObject;

class CMineralScript
	: public CScript
{

public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CMineralScript);
public:
	CMineralScript();
	virtual ~CMineralScript();
};

