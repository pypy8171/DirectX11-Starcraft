#include "stdafx.h"
#include "ArchonEffectScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"

#include "YongEngine/Layer.h"
#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "BuildingScript.h"
#include "UnitScript.h"

#include "ScriptMgr.h"

CArchonEffectScript::CArchonEffectScript()
	: m_szBeforeAnimName{}
	, m_iMaxCount(0)
	, m_vPos(Vec3(0,0,0))
	, m_fDelayDT(0.f)
	, m_fShockDT(0.f)
	, m_bAttack(true)
	, m_fDraAttDT(0.f)
{
	SetScriptType((UINT)SCRIPT_TYPE::ARCHONEFFECTSCRIPT);
}


CArchonEffectScript::~CArchonEffectScript()
{
}

int CArchonEffectScript::update()
{
	//L"ArchonAuraEffectPrefab" 
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	if (L"ArchonAuraEffectPrefab" == Object()->GetName())
	{
		if (Object()->GetParent()->GetLayerIdx() == pCurScene->GetLayer(L"Ally")->GetIdx())
		{
			if (L"Std2DMtrl" == Object()->MeshRender()->GetSharedMaterial()->GetName())
			{
				Object()->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
			}
		}
		else if (Object()->GetParent()->GetLayerIdx() == pCurScene->GetLayer(L"Opponent")->GetIdx())
		{
			if (L"Std2DMtrl" != Object()->MeshRender()->GetSharedMaterial()->GetName())
			{
				Object()->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));
			}
		}
	}

	if (L"ArchonShockwave" == Object()->Animator2D()->GetCurAnimName() )
	{
		MeshRender()->SetRender(false);
		//if (UNIT_STATUS::ATTACK == Object()->GetParent()->GetUnitStatus())
		//{
		//	CUnitScript* pObjUnitScript = nullptr;
		//	if (pObjUnitScript == nullptr)
		//	{
		//		for (int i = 0; i < Object()->GetParent()->Script().size(); ++i)
		//		{
		//			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->Script()[i]->GetScriptType())
		//			{
		//				pObjUnitScript = (CUnitScript*)Object()->GetParent()->Script()[i];
		//			}
		//		}
		//	}

		//	if (pObjUnitScript == nullptr)
		//		return 0;

		//	if (!pObjUnitScript->AttackOn())
		//	{
		//		MeshRender()->SetRender(false);
		//		return 0;
		//	}

		//	if (!MeshRender()->GetRender())
		//	{
		//		MeshRender()->SetRender(true);
		//	}

		//	AttAnim();
		//}
		//else
		//{
		//	if (MeshRender()->GetRender())
		//		MeshRender()->SetRender(false);
		//}
	}
	else if (L"ArchonShockball" == Object()->Animator2D()->GetCurAnimName() || L"Corsair_Splash" == Object()->Animator2D()->GetCurAnimName())
	{
		Splash();

	}
	else if (L"DragoonBall" == Object()->Animator2D()->GetCurAnimName() || L"ArbiterBall" == Object()->Animator2D()->GetCurAnimName()
		|| L"DragoonBallEx" == Object()->Animator2D()->GetCurAnimName() || L"ArbiterBallEx" == Object()->Animator2D()->GetCurAnimName()
		|| L"Scout_Air" == Object()->Animator2D()->GetCurAnimName())
	{
		Ball();
	}
	//else if (L"Scout_Ground" == Object()->Animator2D()->GetCurAnimName())
	//{
	//	Animation();
	//}
	else
	{
		Animation();
		Vec3 vObjPos = Object()->GetParent()->Transform()->GetLocalPos();
		Object()->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y, 101.f));
	}

	return 0;
}

int CArchonEffectScript::lateupdate()
{
	return 0;
}

void CArchonEffectScript::Ball()
{
	CUnitScript* pUnitScript = nullptr;
	if (pUnitScript == nullptr)
	{
		for (size_t i = 0; i < Object()->GetParent()->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)Object()->GetParent()->Script()[i];
			}
		}
	}

	if (nullptr == Object()->GetParent()->GetTargetObj())
		m_vPos = Vec3(0, 0, 0);

	if (UNIT_STATUS::ATTACK == Object()->GetParent()->GetUnitStatus())
	{
		CUnitScript* pObjUnitScript = nullptr;
		if (pObjUnitScript == nullptr)
		{
			for (size_t i = 0; i < Object()->GetParent()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->Script()[i]->GetScriptType())
				{
					pObjUnitScript = (CUnitScript*)Object()->GetParent()->Script()[i];
				}
			}
		}
		if (pObjUnitScript == nullptr)
			return;

		if (!MeshRender()->GetRender())
		{
			MeshRender()->SetRender(true);
		}
		BallAnimation();


		Vec3 vPos{};

		if (Vec3(0, 0, 0) == m_vPos)
		{
			m_fDraAttDT += DT;
		}

		if (m_fDraAttDT < 0.5f)
		{
			if (Object()->GetParent()->GetName() == L"Dragoon")
				Object()->Animator2D()->SetCurAnimName(L"DragoonBallEx");
			else if (Object()->GetParent()->GetName() == L"Arbiter")
				Object()->Animator2D()->SetCurAnimName(L"ArbiterBallEx");

			Vec3 vOtherPos = Object()->GetParent()->GetTargetObj()->Transform()->GetLocalPos();
			Object()->Transform()->SetLocalPos(Vec3(vOtherPos.x, vOtherPos.y, 90));
			return;
		}
		else if (m_fDraAttDT > 0.5f)
		{
			if (Object()->GetParent()->GetName() == L"Dragoon")
				Object()->Animator2D()->SetCurAnimName(L"DragoonBall");
			else if (Object()->GetParent()->GetName() == L"Arbiter")
				Object()->Animator2D()->SetCurAnimName(L"ArbiterBall");
		}

		if (Vec3(0, 0, 0) == m_vPos)
		{
			vPos = Object()->GetParent()->Transform()->GetLocalPos();

		}
		else
			vPos = Object()->Transform()->GetLocalPos();

		Vec3 vTargetPos = Object()->GetParent()->GetTargetObj()->Transform()->GetLocalPos();

		float fDist = sqrt((vTargetPos.x - vPos.x)*(vTargetPos.x - vPos.x)
			+ (vTargetPos.y - vPos.y)*(vTargetPos.y - vPos.y));

		Vec3 vDist = vTargetPos - vPos;

		Vec3 vDir = vTargetPos - (vPos);
		vDir.Normalize();

		m_vPos.x += vDir.x*DT* fDist*0.5f;
		m_vPos.y += vDir.y*DT* fDist*0.5f;
		m_vPos.z = -5.f;
		Object()->Transform()->SetLocalPos(vPos + m_vPos);

		Vec3 vOwnerPos = Object()->GetParent()->Transform()->GetLocalPos();
		float fOwnertToBallDist = sqrt((vOwnerPos.x - vPos.x)*(vOwnerPos.x - vPos.x) +
			(vOwnerPos.y - vPos.y)*(vOwnerPos.y - vPos.y));

		float fOwnerToTargetDist = sqrt((vOwnerPos.x - vTargetPos.x)*(vOwnerPos.x - vTargetPos.x) +
			(vOwnerPos.y - vTargetPos.y)*(vOwnerPos.y - vTargetPos.y));

		if (fDist<20.f || fOwnertToBallDist > fOwnerToTargetDist)
		{
			m_fDraAttDT = 0.f;
			m_vPos = Vec3(0, 0, 0); // 이때 뎀지 줌

			if (OBJ_TYPE::BUILDING != Object()->GetParent()->GetTargetObj()->GetObjType())
			{
				CUnitScript* pTargetUnitScript = nullptr;
				if (pTargetUnitScript == nullptr)
				{
					for (size_t i = 0; i < Object()->GetParent()->GetTargetObj()->Script().size(); ++i)
					{
						if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->GetTargetObj()->Script()[i]->GetScriptType())
						{
							pTargetUnitScript = (CUnitScript*)Object()->GetParent()->GetTargetObj()->Script()[i];
						}
					}
				}
				if (1 > pTargetUnitScript->GetShield())
					pTargetUnitScript->SetDamage(pObjUnitScript->GetGroundAttDamage());
				else
					pTargetUnitScript->SetShield(pObjUnitScript->GetGroundAttDamage());
			}
			else if (OBJ_TYPE::BUILDING == Object()->GetParent()->GetTargetObj()->GetObjType())
			{
				CBuildingScript* pBuildingScript = nullptr;
				for (size_t i = 0; i < Object()->GetParent()->GetTargetObj()->Script().size(); ++i)
				{
					if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == Object()->GetParent()->GetTargetObj()->Script()[i]->GetScriptType())
					{
						pBuildingScript = (CBuildingScript*)Object()->GetParent()->GetTargetObj()->Script()[i];
					}
				}

				CUnitScript* pObjUnitScript = nullptr;
				if (pObjUnitScript == nullptr)
				{
					for (size_t i = 0; i < Object()->GetParent()->Script().size(); ++i)
					{
						if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->Script()[i]->GetScriptType())
						{
							pObjUnitScript = (CUnitScript*)Object()->GetParent()->Script()[i];
						}
					}
				}

				if (1 > pBuildingScript->GetBuildingShield())
					pBuildingScript->SetHp(pObjUnitScript->GetGroundAttDamage());
				else
					pBuildingScript->SetShield(pObjUnitScript->GetGroundAttDamage());
			}
		}
	}
	else
	{
		if (MeshRender()->GetRender())
			MeshRender()->SetRender(false);
	}
}

void CArchonEffectScript::Splash()
{
	if (UNIT_STATUS::ATTACK == Object()->GetParent()->GetUnitStatus())
	{
		CUnitScript* pObjUnitScript = nullptr;
		if (pObjUnitScript == nullptr)
		{
			for (size_t i = 0; i < Object()->GetParent()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->Script()[i]->GetScriptType())
				{
					pObjUnitScript = (CUnitScript*)Object()->GetParent()->Script()[i];
				}
			}
		}

		if (pObjUnitScript == nullptr)
			return;

		if (!pObjUnitScript->AttackOn())
		{
			MeshRender()->SetRender(false);
			return;
		}

		if (!MeshRender()->GetRender())
		{
			MeshRender()->SetRender(true);
		}

		Animation();
		Vec3 vObjPos = Object()->GetParent()->GetTargetObj()->Transform()->GetLocalPos();
		Object()->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y, 0));
	}
	else
	{
		if (MeshRender()->GetRender())
			MeshRender()->SetRender(false);
	}
}

void CArchonEffectScript::Animation()
{
	m_fShockDT += DT;
	if (L"ArchonShockball" == Object()->Animator2D()->GetCurAnimName())
	{
		if (nullptr != Object()->Animator2D()->GetAnimation())
		{
			if (m_fShockDT < Object()->Animator2D()->GetAnimation()->GetFrame()[0].fDuration)
				return;
			else
				m_fShockDT = 0.f;
		}
	}

	map<wstring, CAnimation2D*> maps = Object()->Animator2D()->GetAnimationMap();
	wstring a = Object()->Animator2D()->GetCurAnimName();


	map<wstring, CAnimation2D*>::iterator iter = maps.find(Object()->Animator2D()->GetCurAnimName());

	if (iter == maps.end())
		return;

	Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);
}

void CArchonEffectScript::BallAnimation()
{
	map<wstring, CAnimation2D*> maps = Object()->Animator2D()->GetAnimationMap();
	wstring strCurAnimName = Object()->Animator2D()->GetCurAnimName();


	map<wstring, CAnimation2D*>::iterator iter = maps.find(Object()->Animator2D()->GetCurAnimName());

	if (iter == maps.end())
		return;

	Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);

	//CUnitScript* pUbitScript = nullptr;
	//if (pUbitScript == nullptr)
	//{
	//	for (int i = 0; i < Object()->GetParent()->Script().size(); ++i)
	//	{
	//		if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->Script()[i]->GetScriptType())
	//		{
	//			pUbitScript = (CUnitScript*)Object()->GetParent()->Script()[i];
	//		}
	//	}
	//}

	//size_t iCurFrameSize = Object()->Animator2D()->GetAnimation()->GetFrame().size() - 1;
	//int iCurfrm = Object()->Animator2D()->GetAnimation()->GetCurFrm();
	//
	//if (strCurAnimName == L"DragoonBallEx" && iCurFrameSize == iCurfrm)
	//{
	//	pUbitScript->SetCycle(false);
	//	Object()->Animator2D()->SetCurAnimName(L"DragoonBall");
	//}
}

void CArchonEffectScript::AttAnim()
{
	m_fDelayDT += DT;

	if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
		m_iMaxCount = 0;

	Vec3 vUp = Vec3(0.f, 1.f, 0.f);

	Vec3 vRot = Transform()->GetLocalAngle();

	CUnitScript* pUbitScript = nullptr;
	if (pUbitScript == nullptr)
	{
		for (size_t i = 0; i < Object()->GetParent()->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetParent()->Script()[i]->GetScriptType())
			{
				pUbitScript = (CUnitScript*)Object()->GetParent()->Script()[i];
			}
		}
	}
	Vec3 m_vDir = pUbitScript->GetAnimDir();

	//if (sqrt(m_vDir.x*m_vDir.x + m_vDir.y*m_vDir.y) < 1)
	//	return;

	//m_vDir.Normalize();

	Vec3 vAngle = (Vec3)XMVector3AngleBetweenNormals(vUp, m_vDir); // 사잇각

	float fAngle = (float)(vAngle.z *180.f / 3.14);

	if (fAngle > 180.f)
	{
		fAngle -= 180.f;
	
	}


	if (nullptr != Object()->Animator2D()->GetAnimation())
	{
		if (m_fDelayDT < Object()->Animator2D()->GetAnimation()->GetFrame()[0].fDuration)
			return;
		else
			m_fDelayDT = 0.f;
	}

	map<wstring, CAnimation2D*> maps = Object()->Animator2D()->GetAnimationMap();
	map<wstring, CAnimation2D*>::iterator iter = maps.find(Object()->Animator2D()->GetCurAnimName());

	if (iter == maps.end())
		return;

	size_t iFrmCount = iter->second->GetFrame().size();

	int iTex = (int)(fAngle / (180.f / 17));

	if (m_iMaxCount > (iFrmCount / 17) - 1)
	{
		m_iMaxCount = 0;
	}

	int m_iCurTex = iTex;

	// 움직이는상태라면

	MeshRender()->SetRender(true);
	if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y < 0))
	{
		vRot.y = 0.f;
		Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
	}
	else
	{
		vRot.y = XM_PI;
		iTex = (int)((180.f - fAngle) / (180.f / 17));
		if (iFrmCount <= iTex || iFrmCount - 1 - iTex - 17 * m_iMaxCount < 0)
			return;
		Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iFrmCount - 1 - iTex - 17 * m_iMaxCount); // 
	}



	++m_iMaxCount;

	Transform()->SetLocalRotate(vRot);
	Transform()->SetLocalPos(Object()->GetParent()->Transform()->GetLocalPos());

	m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();
}

void CArchonEffectScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CArchonEffectScript::OnCollision(CCollider * _pOther)
{
}

void CArchonEffectScript::OnCollisionExit(CCollider * _pOther)
{
}
