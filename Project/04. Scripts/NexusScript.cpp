#include "stdafx.h"
#include "NexusScript.h"

#include "ScriptMgr.h"

CNexusScript::CNexusScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::NEXUSSCRIPT);
}


CNexusScript::~CNexusScript()
{
}

int CNexusScript::update()
{
	return 0;
}

int CNexusScript::lateupdate()
{
	return 0;
}
