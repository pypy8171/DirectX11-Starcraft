#include "stdafx.h"
#include "UnitEffectScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "UnitScript.h"
#include "ScriptMgr.h"

// 쉐이드 스크립트랑 구분은 해놨지만 같은 코드임 바뀔 가능성 있어서 따로 해놓은것.

CUnitEffectScript::CUnitEffectScript()
	: m_iMaxCount(0)
	, m_iCurTex(0)
	, m_fAccDT(0.f)
	, m_szBeforeAnimName{}
	, m_vDir(Vec3(0.f, 0.f, 0.f))
	, m_vMarkPos(Vec3(0.f, 0.f, 0.f))
{
	SetScriptType((UINT)SCRIPT_TYPE::UNITEFFECTSCRIPT);
}


CUnitEffectScript::~CUnitEffectScript()
{
}

int CUnitEffectScript::update()
{
	//if (Object()->GetParent()->GetTargetted())
	//{
		if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
			m_iMaxCount = 0;

		Animation(); // 0~16이 가만히 있는 상태
		m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();
	//}
	//if (KEYTAB(KEY_TYPE::KEY_5))
	//{
	//	Object()->SetClicked(false);
	//	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	//	Object()->SetTargetted(false);
	//	pCurScene->SetCurTargetObjVecClear();
	//}

	return 0;
}

int CUnitEffectScript::lateupdate()
{
	return 0;
}

void CUnitEffectScript::Animation()
{
	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Object()->Transform()->GetLocalPos();

	//if (KEYTAB(KEY_TYPE::KEY_RBTN))
	//{
	//	Object()->SetUnitStatus(UNIT_STATUS::MOVE);
	//	m_vMarkPos = CKeyMgr::GetInst()->GetMousePos();// ((CMarkScript*)m_pMark)->GetMarkPos(); // 마우스 우클릭땔때
	//}

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

	m_vDir = pUnitScript->GetAnimDir();

	Vec3 vUp = Vec3(0.f, 1.f, 0.f);

	Vec3 vRot = Transform()->GetLocalAngle();

	if (vMousePos.z == 0.f)
		return;

	//if (sqrt(m_vDir.x*m_vDir.x + m_vDir.y*m_vDir.y) < 1)
	//	return;

	//m_vDir.Normalize();

	Vec3 vAngle = (Vec3)XMVector3AngleBetweenNormals(vUp, m_vDir); // 사잇각

	float fAngle = (float)(vAngle.z *180.f / 3.14);

	if (fAngle > 180.f)
	{
		fAngle -= 180.f;
	}
	map<wstring, CAnimation2D*> maps = Object()->Animator2D()->GetAnimationMap();
	wstring a = Object()->Animator2D()->GetCurAnimName();

	map<wstring, CAnimation2D*>::iterator iter = maps.find(Object()->Animator2D()->GetCurAnimName());

	if (iter == maps.end())
		return;

	size_t iFrmCount = iter->second->GetFrame().size();

	int iTex = (int)(fAngle / (180.f / 17));

	if (m_iMaxCount > (iFrmCount / 17) - 1)
	{
		m_iMaxCount = 0;
	}

	m_iCurTex = iTex;

	// 움직이는상태라면
	if (UNIT_STATUS::MOVE == Object()->GetUnitStatus() || UNIT_STATUS::ATTACK == Object()->GetUnitStatus())
	{
		if (m_iMaxCount == (iFrmCount / 17) - 1)
			m_iMaxCount -= 1;
		if (m_iMaxCount < 0)
			m_iMaxCount = 0;

		if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y < 0))
		{
			vRot.y = 0.f;

			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
		}
		else
		{
			wstring a = Object()->Animator2D()->GetCurAnimName();
			vRot.y = XM_PI;
			iTex = (int)((180.f - fAngle) / (180.f / 17));

			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iFrmCount - 1 - iTex - 17 * m_iMaxCount); // 텍스쳐는 1인거 쓰고 180도 회전
		}
	}
	else if (UNIT_STATUS::IDLE == Object()->GetUnitStatus())
	{
		if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y < 0))
		{
			vRot.y = 0.f;
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex);
		}
		else
		{
			vRot.y = XM_PI;
			iTex = (int)((180.f - fAngle) / (180.f / 17));
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, 17 - 1 - iTex); // 텍스쳐는 1인거 쓰고 180도 회전
		}
	}
	// 가만히 있는 상태라면 구현해주어야 함. 방향에 따라 0~16 텍스쳐 사용

	++m_iMaxCount;

	Object()->Transform()->SetLocalRotate(vRot);
	//Object()->Transform()->SetLocalScale(Object()->GetParent()->Transform()->GetLocalScale());
	Vec3 vObjPos = Object()->GetParent()->Transform()->GetLocalPos();
	Object()->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y, vObjPos.z));

	m_fAccDT = 0.f;
}