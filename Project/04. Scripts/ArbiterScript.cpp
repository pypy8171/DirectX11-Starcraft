#include "stdafx.h"
#include "ArbiterScript.h"

#include "ScriptMgr.h"


CArbiterScript::CArbiterScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::ARBITERSCRIPT);
}


CArbiterScript::~CArbiterScript()
{
}

int CArbiterScript::update()
{
	return 0;
}

int CArbiterScript::lateupdate()
{
	return 0;
}
