#include "stdafx.h"
#include "GasScript.h"

#include "ScriptMgr.h"

CGasScript::CGasScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::GASSCRIPT);

}


CGasScript::~CGasScript()
{
}

int CGasScript::update()
{
	return 0;
}

int CGasScript::lateupdate()
{
	return 0;
}
