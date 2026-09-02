#include "stdafx.h"
#include "IconScript.h"

#include "YongEngine/Core.h"

#include "YongEngine/Transform.h"
#include "YongEngine/Camera.h"

#include "ScriptMgr.h"

#include "UIMgr.h"
CIconScript::CIconScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::ICONSCRIPT);
}


CIconScript::~CIconScript()
{
}

int CIconScript::update()
{
	tResolution vResolution = CCore::GetInst()->GetResoultion();
	Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
	Object()->Transform()->SetLocalPos(Vec3(295.f*vResolution.x/760.f+ vCamPos.x, 
		-100.f*vResolution.x / 480 + vCamPos.y, 1));
	return 0;
}

int CIconScript::lateupdate()
{
	return 0;
}