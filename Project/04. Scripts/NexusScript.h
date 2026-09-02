#pragma once
#include "YongEngine/Script.h"

class CGameObject;

class CNexusScript
	: public CScript
{

public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CNexusScript);

public:
	CNexusScript();
	virtual ~CNexusScript();
};

