#include "stdafx.h"
#include "ArchonScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CArchonScript::CArchonScript()
{
	m_iShield = 350;
	m_iHp = 10;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 30;
	m_iAttSpeed = 1;
	m_fSpeed = 70.f;
	SetScriptType((UINT)SCRIPT_TYPE::ARCHONSCRIPT);
}


CArchonScript::~CArchonScript()
{
}

int CArchonScript::update()
{
	if (Object()->GetClicked())
	{
	}
	return 0;
}

int CArchonScript::lateupdate()
{
	return 0;
}
