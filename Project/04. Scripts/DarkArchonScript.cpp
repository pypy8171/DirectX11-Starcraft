#include "stdafx.h"
#include "DarkArchonScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CDarkArchonScript::CDarkArchonScript()
{
	m_iShield = 150;
	m_iHp = 250;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 0;
	m_iAttSpeed = 0;
	m_fSpeed = 70.f;
	SetScriptType((UINT)SCRIPT_TYPE::DARKARCHONSCRIPT);
}


CDarkArchonScript::~CDarkArchonScript()
{
}

int CDarkArchonScript::update()
{
	if (Object()->GetClicked())
	{

	}
	return 0;
}

int CDarkArchonScript::lateupdate()
{
	return 0;
}
