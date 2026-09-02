#include "stdafx.h"
#include "ScoutScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"

CScoutScript::CScoutScript()
{
	m_iShield = 150;
	m_iHp = 250;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 10;
	m_iAttSpeed = 1;
	m_fSpeed = 50.f;
	SetScriptType((UINT)SCRIPT_TYPE::SCOUTSCRIPT);
}

CScoutScript::~CScoutScript()
{

}

int CScoutScript::update()
{
	if (Object()->GetClicked())
	{

	}
	return 0;
}

int CScoutScript::lateupdate()
{
	return 0;
}
