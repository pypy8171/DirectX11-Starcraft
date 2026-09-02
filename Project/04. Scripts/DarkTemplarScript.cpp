#include "stdafx.h"
#include "DarkTemplarScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"

CDarkTemplarScript::CDarkTemplarScript()
{
	m_iShield = 80;
	m_iHp = 40;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 40;
	m_iAttSpeed = 2;
	m_fSpeed = 70.f;
	SetScriptType((UINT)SCRIPT_TYPE::DARKTEMPLARSCRIPT);
}


CDarkTemplarScript::~CDarkTemplarScript()
{
}

int CDarkTemplarScript::update()
{
	if (Object()->GetClicked())
	{
	}
	return 0;
}

int CDarkTemplarScript::lateupdate()
{
	return 0;
}
