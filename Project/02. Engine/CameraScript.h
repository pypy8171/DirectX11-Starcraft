#pragma once
#include "Script.h"
class CCameraScript :
	public CScript
{

public:
	virtual int update();
	virtual void awake();

public:
	void RotateCam();
	void MoveCam();

public:
	CLONE(CCameraScript);

public:
	CCameraScript();
	virtual ~CCameraScript();
};

