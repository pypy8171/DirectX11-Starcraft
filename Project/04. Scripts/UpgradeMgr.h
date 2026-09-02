#pragma once
#include "SingleTonScript.h"
class CUpgradeMgr :
	public CSingleTonScript<CUpgradeMgr>
{
public:
	virtual int update();
	virtual int lateupdate();

	CLONE(CUpgradeMgr);

public:
	CUpgradeMgr();
	virtual ~CUpgradeMgr();
};

