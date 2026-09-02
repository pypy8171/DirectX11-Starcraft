#include "stdafx.h"
#include "ReaverScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CReaverScript::CReaverScript()
{
	m_iShield = 150;
	m_iHp = 250;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 80;
	m_iAttSpeed = 3;
	m_fSpeed = 10.f;
	SetScriptType((UINT)SCRIPT_TYPE::REAVERSCRIPT);
}


CReaverScript::~CReaverScript()
{
}

int CReaverScript::update()
{
	if (Object()->GetClicked())
	{

	}
	return 0;
}

int CReaverScript::lateupdate()
{
	return 0;
}

