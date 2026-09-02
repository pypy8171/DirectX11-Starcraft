#include "stdafx.h"
#include "CorsairScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CCorsairScript::CCorsairScript()
{
	m_iShield = 60;
	m_iHp = 100;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 5;
	m_iAttSpeed = 1;
	m_fSpeed = 70.f;
	SetScriptType((UINT)SCRIPT_TYPE::CORSAIRSCRIPT);
}


CCorsairScript::~CCorsairScript()
{
}

int CCorsairScript::update()
{
	if (Object()->GetClicked())
	{
	}
	return 0;
}

int CCorsairScript::lateupdate()
{
	return 0;
}
