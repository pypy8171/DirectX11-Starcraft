#pragma once
#include "YongEngine/Script.h"

class CGameObject;

class CGasScript
	: public CScript
{

public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CGasScript);

public:
	CGasScript();
	virtual ~CGasScript();
};

