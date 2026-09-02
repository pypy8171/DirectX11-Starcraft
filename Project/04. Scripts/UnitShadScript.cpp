#include "stdafx.h"
#include "UnitShadScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "UnitScript.h"

#include "ScriptMgr.h"

CUnitShadScript::CUnitShadScript()
	: m_iMaxCount(0)
	, m_iCurTex(0)
	, m_fAccDT(0.f)
	, m_szBeforeAnimName{}
	, m_vDir(Vec3(0.f,0.f,0.f))
	, m_vMarkPos(Vec3(0.f, 0.f, 0.f))
{ 
	SetScriptType((UINT)SCRIPT_TYPE::UNITSHADSCRIPT);
}


CUnitShadScript::~CUnitShadScript()
{
}

int CUnitShadScript::update()
{

		if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
			m_iMaxCount = 0;

		Animation(); // 0~16이 가만히 있는 상태
		m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();


	if (OBJ_TYPE::BUILDING == Object()->GetParent()->GetObjType())
	{
		//map<wstring, CRes*> maps = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);

		//CString a = Object()->Animator2D()->GetCurAnimName();

		//map<wstring, CAnimation2D*>::iterator iter = maps.find(Object()->Animator2D()->GetCurAnimName());

		//CTexture* pTex = maps.find(L"NexusShad");
		//Object()->MeshRender()->SetTexture();
	}

	if (KEYTAB(KEY_TYPE::KEY_5))
	{
		Object()->SetClicked(false);
		CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
		Object()->SetTargetted(false);
		pCurScene->SetCurTargetObjVecClear();
	}

	return 0;
}

int CUnitShadScript::lateupdate()
{
	return 0;
}

void CUnitShadScript::Animation()
{
	Vec3 vPos = Object()->Transform()->GetLocalPos();

	vector<CScript*>& vecScript = Object()->GetParent()->Script();
	CUnitScript* pUnitScript= (CUnitScript*)vecScript[1];

	Vec3 vDir = pUnitScript->GetAnimDir();

	Vec3 vUp = Vec3(0.f, 1.f, 0.f);

	Vec3 vRot = Transform()->GetLocalAngle();

	//if (sqrt(vDir.x*vDir.x + vDir.y*m_vDir.y) < 1)
	//	return;

	//vDir.Normalize();

	Vec3 vAngle = (Vec3)XMVector3AngleBetweenNormals(vUp, vDir); // 사잇각

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
	if (UNIT_STATUS::MOVE == Object()->GetUnitStatus())
	{
		if ((vUp.x*vDir.y - vDir.x*vUp.y < 0))
		{
			vRot.y = 0.f;
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
		}
		else if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y == 0))
		{
			if (m_vDir.y > 0)
			{
				Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
			}
			else
			{
				iTex = (int)((180.f - fAngle) / (180.f / 17));
				if (iFrmCount <= iTex || iFrmCount - 1 - iTex - 17 * m_iMaxCount < 0)
					return;
				Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount); //
			}
		}
		else
		{
			wstring a = Object()->Animator2D()->GetCurAnimName();
			vRot.y = XM_PI;
			iTex = (int)((180.f - fAngle) / (180.f / 17));
			if (iFrmCount <= iTex || iFrmCount - 1 - iTex - 17 * m_iMaxCount < 0)
				return;
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iFrmCount - 1 - iTex - 17 * m_iMaxCount); // 텍스쳐는 1인거 쓰고 180도 회전
		}
	}
	else if (UNIT_STATUS::IDLE == Object()->GetUnitStatus())
	{
		if ((vUp.x*vDir.y - vDir.x*vUp.y < 0))
		{
			vRot.y = 0.f;
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex);
		}
		else
		{
			vRot.y = XM_PI;
			iTex = (int)((180.f - fAngle) / (180.f / 17));
			if (iTex == 17)
				iTex = 16;
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, 17 - 1 - iTex); // 텍스쳐는 1인거 쓰고 180도 회전
		}
	}
	// 가만히 있는 상태라면 구현해주어야 함. 방향에 따라 0~16 텍스쳐 사용

	++m_iMaxCount;

	Object()->Transform()->SetLocalRotate(vRot);

	Vec3 vObjPos = Object()->GetParent()->Transform()->GetLocalPos();
	Object()->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y,106.f));
	
	m_fAccDT = 0.f;
}

// y값이 아래다 -> 먼저 그린다 (벡터 순서 sort(begi, end, []