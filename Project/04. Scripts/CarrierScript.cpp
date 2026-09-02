#include "stdafx.h"
#include "CarrierScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"


CCarrierScript::CCarrierScript()
{
	m_iShield = 250;
	m_iHp = 350;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 6;
	m_iAttSpeed = 1;
	m_fSpeed = 50.f;
	SetScriptType((UINT)SCRIPT_TYPE::CARRIERSCRIPT);
}


CCarrierScript::~CCarrierScript()
{
}

int CCarrierScript::update()
{
	if (Object()->GetClicked())
	{
	}
	return 0;
}

int CCarrierScript::lateupdate()
{
	return 0;
}
