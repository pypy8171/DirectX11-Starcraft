#include "stdafx.h"
#include "DragoonScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"

#include "ScriptMgr.h"

CDragoonScript::CDragoonScript()
{
	m_iShield = 80;
	m_iHp = 100;
	m_iGroundAtt = 20;
	m_iAttSpeed = 1;
	m_fSpeed = 150.f;
	SetScriptType((UINT)SCRIPT_TYPE::DRAGOONSCRIPT);
}


CDragoonScript::~CDragoonScript()
{
}
int CDragoonScript::update()
{
	// 클릭하면 타게팅으로 바꾼다. 타게팅인 애만움직임
	if (Object()->GetClicked())
	{

	}

	return 0;
}

int CDragoonScript::lateupdate()
{
	return 0;
}
