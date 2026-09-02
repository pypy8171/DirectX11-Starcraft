#include "stdafx.h"
#include "TileScript.h"

#include "ScriptMgr.h"

CTileScript::CTileScript()

{
	SetScriptType((UINT)SCRIPT_TYPE::TILESCRIPT);
}


CTileScript::~CTileScript()
{
}
int CTileScript::update()
{
	return 0;
}
