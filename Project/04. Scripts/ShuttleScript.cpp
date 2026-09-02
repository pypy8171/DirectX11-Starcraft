#include "stdafx.h"
#include "ShuttleScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CShuttleScript::CShuttleScript()
{
	m_iShield = 100;
	m_iHp = 80;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 0;
	m_iAttSpeed = 0;
	m_fSpeed = 65.f;
	SetScriptType((UINT)SCRIPT_TYPE::SHUTTLESCRIPT);
}


CShuttleScript::~CShuttleScript()
{
}

int CShuttleScript::update()
{
	if (Object()->GetClicked())
	{

	}
	return 0;
}

int CShuttleScript::lateupdate()
{
	return 0;
}
