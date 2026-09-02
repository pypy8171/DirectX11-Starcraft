#include "stdafx.h"
#include "SkillMgr.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Collider.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/KeyMgr.h"

#include "YongEngine/Layer.h"
#include "YongEngine/Scene.h"

#include "YongEngine/Texture.h"

#include "SkillScript.h"

#include "ScriptMgr.h"

CSkillMgr::CSkillMgr()
{
	SetScriptType((UINT)SCRIPT_TYPE::SKILLMGR);
}


CSkillMgr::~CSkillMgr()
{
}

int CSkillMgr::update()
{
	if (SKILL::NONE != m_eSkill)
	{
		if (m_eSkill == SKILL::ILLUSION)
		{
			return 0;
		}
		else if (m_eSkill == SKILL::ARCHONCOALESCENCE)
		{
			return 0;
		}
		else if (m_eSkill == SKILL::DARKARCHONCOALESCENCE)
		{
			return 0;
		}

		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();

		Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();

		CGameObject* pSkillObject = new CGameObject;
		pSkillObject->AddComponent(new CMeshRender);
		pSkillObject->AddComponent(new CCollider);
		pSkillObject->AddComponent(new CAnimator2D);
		pSkillObject->AddComponent(new CSkillScript);

		pSkillObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pSkillObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		wstring AnimPath{};
		wstring strFolderPath = L"Texture\\Animation2D\\Protoss\\Effect\\";
		if (m_eSkill == SKILL::STASISFIELD)
		{
			pSkillObject->SetName(L"StasisField");
			AnimPath = strFolderPath + L"Stasis\\";
			pSkillObject->Transform()->SetLocalScale(Vec3(128.f, 128.f,1.f));
			pSkillObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pSkillObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
			pSkillObject->Animator2D()->AddAnimation(AnimPath, L"StasisField", true);
			pSkillObject->Animator2D()->SetCurAnimName(L"StasisField");
		}
		else if (m_eSkill == SKILL::RECALL)
		{
			pSkillObject->SetName(L"Recall");
			AnimPath = strFolderPath + L"Recall\\";
			pSkillObject->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
			pSkillObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pSkillObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
			pSkillObject->Animator2D()->AddAnimation(AnimPath, L"Recall", true);
			pSkillObject->Animator2D()->SetCurAnimName(L"Recall");
		}
		else if (m_eSkill == SKILL::STORM)
		{
			pSkillObject->SetName(L"Storm");
			AnimPath = strFolderPath + L"Storm\\";
			pSkillObject->Transform()->SetLocalScale(Vec3(224.f, 224.f, 1.f));
			pSkillObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pSkillObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
			pSkillObject->Animator2D()->AddAnimation(AnimPath, L"Storm", true);
			pSkillObject->Animator2D()->SetCurAnimName(L"Storm");
		}
		else if (m_eSkill == SKILL::FEEDBACK) // 대상하나
		{
			pSkillObject->SetName(L"FeedBack");
			AnimPath = strFolderPath + L"FeedBack\\";
			pSkillObject->Transform()->SetLocalScale(Vec3(64.f, 64.f, 1.f));
			pSkillObject->Animator2D()->AddAnimation(AnimPath, L"FeedBack", true);
			pSkillObject->Animator2D()->SetCurAnimName(L"FeedBack");
		}
		else if (m_eSkill == SKILL::MINDCONTROL)  // 대상하나
		{
			pSkillObject->SetName(L"Mindcontrol");
			AnimPath = strFolderPath + L"Mindcontrol\\";
			pSkillObject->Transform()->SetLocalScale(Vec3(64.f, 64.f, 1.f));
			pSkillObject->Animator2D()->AddAnimation(AnimPath, L"Mindcontrol", true);
			pSkillObject->Animator2D()->SetCurAnimName(L"Mindcontrol");
		}
		else if (m_eSkill == SKILL::CONFUSION)
		{
			pSkillObject->SetName(L"maelhit");
			AnimPath = strFolderPath + L"maelhit\\";
			pSkillObject->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
			pSkillObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pSkillObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
			pSkillObject->Animator2D()->AddAnimation(AnimPath, L"maelhit", true);
			pSkillObject->Animator2D()->SetCurAnimName(L"maelhit");
		}
		else if (m_eSkill == SKILL::WAP)
		{
			pSkillObject->SetName(L"Web");
			AnimPath = strFolderPath + L"Web\\";
			pSkillObject->Transform()->SetLocalScale(Vec3(160.f, 160.f, 1.f));
			pSkillObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pSkillObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
			pSkillObject->Animator2D()->AddAnimation(AnimPath, L"Web", true);
			pSkillObject->Animator2D()->SetCurAnimName(L"Web");
		}



		pScene->AddGameObject(L"Skill", pSkillObject);

		m_eSkill = SKILL::NONE;
		// 애니메이션 끝나면 삭제
	}

	return 0;
}

int CSkillMgr::lateupdate()
{
	return 0;
}
