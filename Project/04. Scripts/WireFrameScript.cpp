#include "stdafx.h"
#include "WireFrameScript.h"

#include "YongEngine/Core.h"

#include "YongEngine/MeshRender.h"
#include "YongEngine/Collider.h"
#include "YongEngine/Transform.h"

#include "YongEngine/Animator2D.h"
#include "YongEngine/Animation2D.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"

#include "YongEngine/Scene.h"

#include "UnitScript.h"
#include "BuildingScript.h"

#include "UIMgr.h"
#include "ScriptMgr.h"

int CWireFrameScript::m_iWireIdx = 0;

CWireFrameScript::CWireFrameScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::WIREFRAMESCRIPT);
	SetWireFrameIdx(m_iWireIdx);
	++m_iWireIdx;
}

CWireFrameScript::~CWireFrameScript()
{
}

int CWireFrameScript::update()
{
	if (nullptr == Object()->Animator2D())
		return false;

	if (false == Object()->Animator2D()->GetFileLoadOn())
		return false;


	tResolution tResolution = CCore::GetInst()->GetResoultion();

	Vec3 vScale = Object()->Transform()->GetLocalScale();
	Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();

	Transform()->SetLocalScale(Vec3((float)(vScale.x*tResolution.x/760), (float)(vScale.y*tResolution.y/480), vScale.z));
	Object()->Transform()->SetLocalPos(Vec3(-150.f*tResolution.x / 760 + vCamPos.x, -290.f*tResolution.y / 480 + vCamPos.y, 1));

	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	vector<CGameObject*> vec = pScene->GetCurTargetObjVec();

	if (1 > vec.size())
	{
		Object()->MeshRender()->SetRender(false);
		return 0;
	}
	else if (1 == vec.size())
	{
		Object()->MeshRender()->SetRender(true);
		CGameObject* pTargetObj = vec[0]; // 단일타겟을 경우 BWF, 다중 SWF-> 아직 등록 안함

		if(pTargetObj == nullptr)
			return 0;

		CUnitScript* pUnitScript = nullptr;
		CBuildingScript* pBuilidingScript = nullptr;
	
		int iHp = 0;
		int iMaxHp = 0;
		int iDivide = 0;
		int iTex = 0;

		if (OBJ_TYPE::GROUNDUNIT == pTargetObj->GetObjType() || OBJ_TYPE::AIRUNIT == pTargetObj->GetObjType())
		{
			if (vec[0]->GetUnitStatus() == UNIT_STATUS::DIE)
				return 0;

			for (size_t j = 0; j < vec[0]->Script().size(); ++j)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == vec[0]->Script()[j]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)vec[0]->Script()[j];
				}
			}

			if (pUnitScript == nullptr)
				return 0;

			iHp = pUnitScript->GetHp();
			iMaxHp = pUnitScript->GetMaxHp();

			iDivide = (int)(iMaxHp / 6); // 나눌 값 // 인덱스가 0~6까지 나와야 한다.
			iTex = (int)((iMaxHp - iHp) / iDivide); // iTex는 0~6까지 나옴
		}
		else if (OBJ_TYPE::BUILDING == pTargetObj->GetObjType())
		{
			for (size_t j = 0; j < vec[0]->Script().size(); ++j)
			{
				if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == vec[0]->Script()[j]->GetScriptType())
				{
					pBuilidingScript = (CBuildingScript*)vec[0]->Script()[j];
				}
			}
			if (pBuilidingScript == nullptr)
				return 0;

			iHp = pBuilidingScript->GetBuildingHp();
			iMaxHp = pBuilidingScript->GetMaxHp();

			iDivide = (int)(iMaxHp / 6); // 나눌 값 // 인덱스가 0~6까지 나와야 한다.
			iTex = (int)((iMaxHp - iHp) / iDivide); // iTex는 0~6까지 나옴
		}

		if (iTex > 7)
			iTex = 7;
		if (iTex < 0)
			iTex = 0;

		wstring CurAnimName = pTargetObj->GetName();

		if (CurAnimName == L"DarkTemplar")
			CurAnimName = L"Dark Templar";
		else if (CurAnimName == L"HighTemplar")
			CurAnimName = L"High Templar";
		else if (CurAnimName == L"DarkArchon")
			CurAnimName = L"Dark Archon";
		else if (CurAnimName == L"PylonRadius")
			return 0;

		wstring WFAnimName = CurAnimName;
		WFAnimName = CUIMgr::GetInst()->SubtractName(WFAnimName);

		WFAnimName += L"BWF";

		// 워프할때 리턴?
		if (L"WarpBWF" == WFAnimName)
			return 0;

		if (m_iWireFrameIdx > 0)
		{
			Object()->MeshRender()->SetRender(false);
			return 0;
		}

		Object()->Animator2D()->PlayNumAnimation(WFAnimName, false, iTex); ;

		Transform()->SetLocalScale(Vec3((float)(vScale.x*tResolution.x/760), (float)(vScale.y*tResolution.y / 760), vScale.z));
		Object()->Transform()->SetLocalPos(Vec3(-150.f*tResolution.x / 760 + vCamPos.x, -290.f*tResolution.y / 760 + vCamPos.y, 1));
	}
	
	if(!m_bMulti)
	{
		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
		vector<CGameObject*> vecObj = pScene->GetLayer(L"ProtossUI")->GetObjVec();
		int iCount = 0;
		for (size_t i = 0; i < vecObj.size(); ++i)
		{
			if (L"WireFrame" == vecObj[i]->GetName())
			{
				++iCount;
			}
		}

		if (iCount > 1)
		{
			m_bMulti = true;
		}
		else
		{
			int a = 0;
			for (int i = 0; i < 11; ++i)
			{
				CWireFrameScript* pWireScript = new CWireFrameScript;

				//CAnimator2D* pAnimator = new CAnimator2D;
				//pAnimator = Object()->Animator2D()->Clone();

				CGameObject* pWireFrame = new CGameObject;
				pWireFrame->SetName(L"WireFrame");
				pWireFrame->AddComponent(new CMeshRender);
				pWireFrame->AddComponent(new CCollider);
				pWireFrame->AddComponent(Object()->Animator2D()->Clone());
				pWireFrame->AddComponent(pWireScript);

				pWireScript->Multi(true);

				pWireFrame->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
				pWireFrame->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

				pWireFrame->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
				pWireFrame->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::CREATE_OBJECT, (INT_PTR)pWireFrame, Object()->GetLayerIdx() });

			}
		}
		m_bMulti = true;
	}

	if (m_bMulti && vec.size() > 1)
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			CUnitScript* pUnitScript = nullptr;
		
			for (size_t j = 0; j < vec[i]->Script().size(); ++j)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == vec[i]->Script()[j]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)vec[i]->Script()[j];
				}
			}
			if (pUnitScript == nullptr)
				continue;
			
			int iHp = pUnitScript->GetHp();
			int iMaxHp = pUnitScript->GetMaxHp();

			int iDivide = (int)(iMaxHp / 6); // 나눌 값 // 인덱스가 0~6까지 나와야 한다.
			int iTex = (int)((iMaxHp - iHp) / iDivide); // iTex는 0~6까지 나옴

			wstring CurAnimName = vec[i]->GetName();

			wstring WFAnimName = CurAnimName;
			WFAnimName = CUIMgr::GetInst()->SubtractName(WFAnimName);

			if (WFAnimName == L"DarkTemplar")
				WFAnimName = L"Dark Templar";
			else if (WFAnimName == L"HighTemplar")
				WFAnimName = L"High Templar";
			else if (WFAnimName == L"DarkArchon")
				WFAnimName = L"Dark Archon";

			WFAnimName += L"SWF";

			Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();

			if (i == m_iWireFrameIdx)
			{

				if (iTex > 7)
					iTex = 7;
				if (iTex < 0)
					iTex = 0;
				Object()->MeshRender()->SetRender(true);
				Object()->Animator2D()->PlayNumAnimation(WFAnimName, false, iTex);

				if (0 == i % 2)
				{
					Object()->Transform()->SetLocalPos(Vec3((-168.f  + 42.f*(i / 2))*tResolution.x / 760 + vCamPos.x
						, -213.f*tResolution.y/480 + 40.f * tResolution.y / 480 + vCamPos.y, 1));
				}
				else
				{
					Object()->Transform()->SetLocalPos(Vec3((-168.f + 42.f*(i / 2))*tResolution.x / 760 + vCamPos.x,
						-213.f*tResolution.y/480  + vCamPos.y, 1));
				}

				Object()->Transform()->SetLocalScale(Vec3(42.f*tResolution.x/760, 40.f*tResolution.y / 480, 1.f));
			}
		}
	}

	return 0;
}

int CWireFrameScript::lateupdate()
{
	return 0;
}
