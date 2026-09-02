#include "stdafx.h"
#include "HighTemplarScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CHighTemplarScript::CHighTemplarScript()
{
	m_iShield = 40;
	m_iHp = 40;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 0;
	m_iAttSpeed = 0;
	m_fSpeed = 70;
	SetScriptType((UINT)SCRIPT_TYPE::HIGHTEMPLARSCRIPT);
}


CHighTemplarScript::~CHighTemplarScript()
{
}

int CHighTemplarScript::update()
{
	if (Object()->GetClicked())
	{
	}
	return 0;
}

int CHighTemplarScript::lateupdate()
{
	return 0;
}
