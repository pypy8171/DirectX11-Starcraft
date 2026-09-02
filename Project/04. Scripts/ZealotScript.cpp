#include "stdafx.h"
#include "ZealotScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"

CZealotScript::CZealotScript()
	//: m_vDir(Vec3(0.f, 0.f, 0.f))
	//, m_vMarkPos(Vec3(0.f, 0.f, 0.f))
	//, m_iMaxCount(0)
	//, m_iCurTex(0)
	//, m_fAccDT(0.f)
	//, m_szBeforeAnimName{}
{
	m_iShield = 80;
	m_iHp = 100;
	m_iGroundAtt = 10;
	m_iAttSpeed = 1;
	m_fSpeed = 100.f;
	SetScriptType((UINT)SCRIPT_TYPE::ZEALOTSCRIPT);
}


CZealotScript::~CZealotScript()
{
}

int CZealotScript::update()
{
	// 클릭하면 타게팅으로 바꾼다. 타게팅인 애만움직임


	return 0;
}

int CZealotScript::lateupdate()
{
	return 0;
}
