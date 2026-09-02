#include "stdafx.h"
#include "SkillScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/Animation2D.h"

#include "YongEngine/EventMgr.h"
#include "YongEngine/KeyMgr.h"
#include "YongEngine/ResMgr.h"


#include "UnitScript.h"

#include "UnitMgr.h"
#include "ScriptMgr.h"


CSkillScript::CSkillScript()
	: m_bSkillOn(false)
	, m_vSkillPos(Vec3(0,0,0))
{
	SetScriptType((UINT)SCRIPT_TYPE::SKILLSCRIPT);
}


CSkillScript::~CSkillScript()
{
}

int CSkillScript::update()
{
	Animation();
	return 0;
}

int CSkillScript::lateupdate()
{
	return 0;
}

void CSkillScript::Animation()
{
	if (KEYTAB(KEY_TYPE::KEY_LBTN) && m_bSkillOn == false) 
	{
		if (Object()->GetName() == L"StasisField")
		{
			CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"StasisField", L"Sound\\ArbiterStasisField.wav");
			pSound->Play(1);
		}
		else if (Object()->GetName() == L"Recall")
		{
			CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"Recall", L"Sound\\ArbiterRecall.wav");
			pSound->Play(1);
		}
		else if (Object()->GetName() == L"Storm")
		{
			CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"Storm", L"Sound\\Storm.wav");
			pSound->Play(1);
		}

		m_bSkillOn = true;
		m_vSkillPos = CKeyMgr::GetInst()->GetMousePos();
	}

	if (m_bSkillOn)
	{

		Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);

		CAnimation2D* pCurAnim = Object()->Animator2D()->GetAnimation();

		if (pCurAnim->GetCurFrm() == pCurAnim->GetFrame().size() - 1)
		{
			CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object() ,NULL });
			m_bSkillOn = false;
		}

		Object()->Transform()->SetLocalPos(m_vSkillPos); // z´Â 0À¸·Î
	}
}