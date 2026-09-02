#include "stdafx.h"
#include "UpgradeMgr.h"

#include "ScriptMgr.h"

int CUpgradeMgr::update()
{
	return 0;
}

int CUpgradeMgr::lateupdate()
{
	return 0;
}

CUpgradeMgr::CUpgradeMgr()
{
	SetScriptType((UINT)SCRIPT_TYPE::UPGRADEMGR);
}


CUpgradeMgr::~CUpgradeMgr()
{
}
