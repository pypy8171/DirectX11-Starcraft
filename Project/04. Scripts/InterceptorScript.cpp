#include "stdafx.h"
#include "InterceptorScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CInterceptorScript::CInterceptorScript()
{
	m_iShield = 30;
	m_iHp = 30;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 6;
	m_iAttSpeed = 2;
	m_fSpeed = 70.f;
	SetScriptType((UINT)SCRIPT_TYPE::INTERCEPTORSCRIPT);
}


CInterceptorScript::~CInterceptorScript()
{
}

int CInterceptorScript::update()
{
	if (Object()->GetClicked())
	{
	}
	return 0;
}

int CInterceptorScript::lateupdate()
{
	return 0;
}
