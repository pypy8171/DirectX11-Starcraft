#include "stdafx.h"

#include "BuildingScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Transform.h"
#include "YongEngine/Animation2D.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Collider.h"
#include "YongEngine/Grid.h"


#include "YongEngine/KeyMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Layer.h"

#include "YongEngine/Texture.h"
#include "YongEngine/Material.h"

#include "MouseScript.h"

#include "UnitScript.h"
#include "BuildingMgr.h"
#include "ScriptMgr.h"
#include "UnitMgr.h"
#include "UIMgr.h"

CBuildingScript::CBuildingScript()
	: m_bBuildComplete(false)
	, m_bCreated(false)
	, m_bKeyComplete(false)
	, m_bSetChapter(false)
	, m_bProduce(false)
	, m_fAccDT(0.f)
	, m_vInstanciatedPos(Vec3(0, 0, 0))
	, m_pMyself(nullptr)
	, m_bProduceOut(false)
	, m_iBuildingCount(0)
	, m_iShield(0)
	, m_iHp(0)
	, m_iMineralCost(0)
	, m_iGasCost(0)
	, m_bExplosion(false)
	, m_fAccExplosionDT(0.f)
{
	SetScriptType((UINT)SCRIPT_TYPE::BUILDINGSCRIPT);
}


CBuildingScript::~CBuildingScript()
{
}

int CBuildingScript::update()
{

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Ally")->GetIdx())
	{
		if (L"Std2DMtrl" == Object()->MeshRender()->GetSharedMaterial()->GetName())
		{
			Object()->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		}
	}
	else if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Opponent")->GetIdx())
	{
		if (L"Std2DMtrl" != Object()->MeshRender()->GetSharedMaterial()->GetName())
		{
			Object()->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));
		}
	}


	if (Object()->GetTargetted())
	{
		if (L"Nexus" == Object()->GetName())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::NEXUS);
		}
		else if (L"Gateway" == Object()->GetName())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::GATEWAY);
		}
		else if (L"Robotics Facility" == Object()->GetName())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::ROBOTICS);
		}
		else if (L"Stargate" == Object()->GetName())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::STARGATE);
		}
		else
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::EMPTY);
		}
	}

	if (true == GetProduceOut())
	{
		if (0 != m_pClickedPrefab.size())
		{
			ProduceUnit();
			SetProduceOut(false);
		}
	}


	Animation();
	return 0;
}

int CBuildingScript::lateupdate()
{
	return 0;
}

void CBuildingScript::Animation()
{
	if (!m_bKeyComplete)
	{
		m_strKey = Object()->GetName().c_str();

	}
	map<wstring, CAnimation2D*> maps = Object()->Animator2D()->GetAnimationMap();
	wstring a = Object()->Animator2D()->GetCurAnimName();
	map<wstring, CAnimation2D*>::iterator iter = maps.find(Object()->Animator2D()->GetCurAnimName());

	if (L"Pylon" == Object()->GetName())
	{
		for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		{
			if (L"PylonRadius" == Object()->GetChild()[i]->GetName())
			{
				if (!Object()->GetTargetted())
					Object()->GetChild()[i]->MeshRender()->SetRender(false);
				else if (Object()->GetTargetted())
					Object()->GetChild()[i]->MeshRender()->SetRender(true);
			}
		}
	}

	CLayer* pMouseLayers = CSceneMgr::GetInst()->GetLayer(L"Mouse");
	vector<CGameObject*> pMouseObjects = pMouseLayers->GetObjVec();
	CMouseScript* pMouseScript = nullptr;
	if (pMouseScript == nullptr)
	{
		for (size_t i = 0; i < pMouseObjects[0]->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::MOUSESCRIPT == pMouseObjects[0]->Script()[i]->GetScriptType())
			{
				pMouseScript = (CMouseScript*)pMouseObjects[0]->Script()[i];
			}
		}
	}
	if (nullptr != pMouseScript)
	{
		if (pMouseScript->GetStructure())
		{
			for (size_t i = 0; i < Object()->GetChild().size(); ++i)
			{
				if (L"PylonRadius" == Object()->GetChild()[i]->GetName())
				{
					Object()->GetChild()[i]->MeshRender()->SetRender(true);
				}
			}
		}
		else
		{
			for (size_t i = 0; i < Object()->GetChild().size(); ++i)
			{
				if (L"PylonRadius" == Object()->GetChild()[i]->GetName())
				{
					Object()->GetChild()[i]->MeshRender()->SetRender(false);
				}
			}
		}
	}
	// 여기까지 파일런


	if (m_iHp <= 0 && !m_bExplosion)
	{
		CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"StructureExplosion");
		pSound->Play(1);

		Object()->Animator2D()->SetCurAnimName(L"Explosion_L");

		CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();

		if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Opponent")->GetIdx())
		{
			vector<CGameObject*> vecAlly = pCurScene->GetLayer(L"Ally")->GetObjVec();
			for (size_t i = 0; i < vecAlly.size(); ++i)
			{
				if (Object() == vecAlly[i]->GetTargetObj())
				{
					vecAlly[i]->SetTarget(nullptr);
					vecAlly[i]->SetUnitStatus(UNIT_STATUS::IDLE);
				}
			}
		}
		else if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Ally")->GetIdx())
		{
			vector<CGameObject*> vecOpponent = pCurScene->GetLayer(L"Opponent")->GetObjVec();
			for (size_t i = 0; i < vecOpponent.size(); ++i)
			{
				if (Object() == vecOpponent[i]->GetTargetObj())
				{
					vecOpponent[i]->SetTarget(nullptr);
					vecOpponent[i]->SetUnitStatus(UNIT_STATUS::IDLE);
				}
			}
		}
		Object()->SetTarget(nullptr);

		// 

		m_bExplosion = true;
	}

	if (m_bExplosion)
	{

		if (L"Explosion_L" == Object()->Animator2D()->GetCurAnimName())
		{
			Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);
			size_t iCurFrameSize = Object()->Animator2D()->GetAnimation()->GetFrame().size() - 1;
			int iCurfrm = Object()->Animator2D()->GetAnimation()->GetCurFrm();
			if (iCurFrameSize == iCurfrm)
			{
				CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();

				if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Opponent")->GetIdx())
				{
					vector<CGameObject*> vecAlly = pCurScene->GetLayer(L"Ally")->GetObjVec();
					for (size_t i = 0; i < vecAlly.size(); ++i)
					{
						if (Object() == vecAlly[i]->GetTargetObj())
						{
							vecAlly[i]->SetTarget(nullptr);
							vecAlly[i]->SetUnitStatus(UNIT_STATUS::IDLE);
						}
					}
				}
				if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Ally")->GetIdx())
				{
					vector<CGameObject*> vecOpponent = pCurScene->GetLayer(L"Opponent")->GetObjVec();
					for (size_t i = 0; i < vecOpponent.size(); ++i)
					{
						if (Object() == vecOpponent[i]->GetTargetObj())
						{
							vecOpponent[i]->SetTarget(nullptr);
							vecOpponent[i]->SetUnitStatus(UNIT_STATUS::IDLE);
						}
					}
				}

				CLayer* pMouseLayers = CSceneMgr::GetInst()->GetLayer(L"Mouse");
				vector<CGameObject*> pMouseObjects = pMouseLayers->GetObjVec();
				CMouseScript* pMouseScript = nullptr;
				if (pMouseScript == nullptr)
				{
					for (size_t i = 0; i < pMouseObjects[0]->Script().size(); ++i)
					{
						if ((UINT)SCRIPT_TYPE::MOUSESCRIPT == pMouseObjects[0]->Script()[i]->GetScriptType())
						{
							pMouseScript = (CMouseScript*)pMouseObjects[0]->Script()[i];
						}
					}
				}
				if (pMouseScript->GetTargetObj() == Object())
					pMouseScript->SetTargetObj(nullptr);


				if (Object() == CUnitMgr::GetInst()->GetButtonOwner())
				{
					CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::NONE);
					CUnitMgr::GetInst()->SetButtonOwner(nullptr);
				}

				CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
				vector<CGameObject*> vec = pScene->GetCurTargetObjVec();

				for (size_t i = 0; i < vec.size(); ++i)
				{
					if (Object() == vec[i])
					{
						vec[i] = nullptr;
					}
				}

				vector<CGameObject*> vecTemp;

				for (size_t i = 0; i < vec.size(); ++i)
				{
					if (vec[i] != nullptr)
					{
						vecTemp.push_back(vec[i]);
					}
				}

				pScene->SetCurTargetObjVecClear();

				for (size_t i = 0; i < vecTemp.size(); ++i)
				{
					pScene->AddTargetObj(vecTemp[i]);
				}

				Object()->Animator2D()->SetCurAnimName(L"Vestige");
			}
		}
		else if (L"Vestige" == Object()->Animator2D()->GetCurAnimName())
		{
			Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), false);

			if (m_fAccExplosionDT > 3.f)
			{
				

				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object() ,NULL });
				m_fAccExplosionDT = 0.f;
			}
		}

		m_fAccExplosionDT += DT;
	}

	bool bSetTex = false;

	if (iter == maps.end())
		return;

	if (m_bBuildComplete && !m_bExplosion)
	{
		Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), false);

		if (L"Nexus" == Object()->GetName())
		{
			CBuildingMgr::GetInst()->SetSTartingPoint(Vec3(Object()->Transform()->GetLocalPos().x, Object()->Transform()->GetLocalPos().y,100.f));
		}

		if (0 == Object()->GetChild().size())
		{
			CString strShadName = Object()->GetName().c_str();
			strShadName += L"Shad";

			CTexture* pTex = CResMgr::GetInst()->Load<CTexture>((wstring)strShadName);

			CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
			CGameObject* pGameObject = new CGameObject;
			pGameObject->SetName(strShadName.GetBuffer());
			pGameObject->AddComponent(new CMeshRender);

			CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

			pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
			pGameObject->MeshRender()->SetMaterial(pMtrl);
			pGameObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);

			pGameObject->Transform()->SetLocalPos(Vec3(Object()->Transform()->GetLocalPos().x,Object()->Transform()->GetLocalPos().y,105.f));
			pGameObject->Transform()->SetLocalScale(Vec3(pTex->GetWidth(), pTex->GetHeight(), 1.f));

			Object()->AddChild(pGameObject);

			if (L"Pylon" == Object()->GetName()) // 눌렀을때만 보이게 해야하는데
			{
				CString strRadName = Object()->GetName().c_str();
				strRadName += L"Radius";

				CTexture* pTex = CResMgr::GetInst()->Load<CTexture>((wstring)strRadName);

				CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
				CGameObject* pGameObject = new CGameObject;
				pGameObject->SetName(strRadName.GetBuffer());
				pGameObject->AddComponent(new CMeshRender);
				pGameObject->AddComponent(new CCollider);
				pGameObject->SetObjType(OBJ_TYPE::BUILDING);

				CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

				pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
				pGameObject->MeshRender()->SetMaterial(pMtrl);
				pGameObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);

				Vec3 vRadPos = Object()->Transform()->GetLocalPos();
				pGameObject->Transform()->SetLocalPos(Vec3(vRadPos.x, vRadPos.y,105.f));
				pGameObject->Transform()->SetLocalScale(Vec3(pTex->GetWidth(), pTex->GetHeight(), 1.f));

				pGameObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
				pGameObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

				Object()->AddChild(pGameObject);
			}
		}

		for (int i = 0; i < 1; ++i)
		{
			Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(Object()->Transform()->GetLocalPos().x, Object()->Transform()->GetLocalPos().y,
				105.f));
		}

		for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		{
			wstring name = Object()->GetChild()[i]->GetName();
			wstring pylonrad = Object()->GetChild()[i]->GetName();

			if (name == Object()->GetChild()[i]->GetName() || pylonrad == Object()->GetChild()[i]->GetName())
			{
				Vec3 vObjPos = Object()->Transform()->GetLocalPos();

				if (L"PylonRadius" == Object()->GetChild()[i]->GetName())
				{
					Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y, 105.f));
				}
				else
					Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y, 105.f));
			}
		}

		m_bKeyComplete = true;
	}
	else if (!m_bBuildComplete && !bSetTex)
	{
		if (m_fAccDT <= 5.f)
		{


			Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);
			if (Object()->Animator2D()->GetAnimation()->GetCurFrm() > 11)
				Object()->Animator2D()->GetAnimation()->SetFrmIdx(7);

			m_fAccDT += DT;
		}
		else if (m_fAccDT > 5.f) // 건물마다 빌드타임 따로 지정
		{
			Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);

			if (m_strKey == Object()->Animator2D()->GetCurAnimName().c_str())
			{
				size_t iCurFrameSize = Object()->Animator2D()->GetAnimation()->GetFrame().size() - 1;
				int iCurfrm = Object()->Animator2D()->GetAnimation()->GetCurFrm();
				if (iCurFrameSize == iCurfrm)
				{
					m_bBuildComplete = true;
					m_fAccDT = 0.f;
					SetBuildTree();
				}
			}

			if (Object()->Animator2D()->GetAnimation()->GetCurFrm() >= Object()->Animator2D()->GetAnimation()->GetFrame().size() - 1
				&& false == m_bCreated)
			{
				Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);
				int a = Object()->Animator2D()->GetAnimation()->GetCurFrm();
				Object()->Animator2D()->SetCurAnimName(m_strKey.GetBuffer());
				m_bCreated = true;

				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"BuildEnd");
				pSound->Play(1);
			}

		}
	}

	Vec3 vMy = Object()->Transform()->GetLocalPos();
	
	Object()->Transform()->SetLocalPos(Vec3(vMy.x, vMy.y, 100.f));

}

void CBuildingScript::ProduceUnit()
{
	CLayer* pPrefabLayer = CSceneMgr::GetInst()->GetLayer(L"Ally");
	vector<CGameObject*> pPrefabObject = pPrefabLayer->GetObjVec();

	CPrefab* pGameObject = GetListPrefab().front();
	CGameObject* pOrgGameObject = pGameObject->GetOriginObj();
	Vec3 vOrgGameObjectScale = pOrgGameObject->Transform()->GetLocalScale()*pOrgGameObject->Collider()->GetOffsetScale();

	wstring strUnitName = CUnitMgr::GetInst()->GetUnitName();


	if (nullptr == pGameObject)
		return;

	CGameObject* pStructure = nullptr;
	if (pOrgGameObject->GetName() == L"Probe")
	{
		for (size_t i = 0; i < pPrefabObject.size(); ++i)
		{
			if (L"Nexus" == pPrefabObject[i]->GetName())
			{
				pStructure = pPrefabObject[i];
				break;
			}
		}
	}
	else if (pOrgGameObject->GetName() == L"Zealot" || pOrgGameObject->GetName() == L"Dragoon"
		|| pOrgGameObject->GetName() == L"DarkTemplar" || pOrgGameObject->GetName() == L"HighTemplar")
	{
		for (size_t i = 0; i < pPrefabObject.size(); ++i)
		{
			if (L"Gateway" == pPrefabObject[i]->GetName())
			{
				pStructure = pPrefabObject[i];
				break;
			}
		}
	}
	else if (pOrgGameObject->GetName() == L"Shuttle" || pOrgGameObject->GetName() == L"Reaver" || pOrgGameObject->GetName() == L"Observer")
	{
		for (size_t i = 0; i < pPrefabObject.size(); ++i)
		{
			if (L"Robotics Facility" == pPrefabObject[i]->GetName())
			{
				pStructure = pPrefabObject[i];
				break;
			}
		}
	}
	else if (pOrgGameObject->GetName() == L"Corsair" || pOrgGameObject->GetName() == L"Carrier"
		|| pOrgGameObject->GetName() == L"Arbiter"|| pOrgGameObject->GetName() == L"Scout")
	{
		for (size_t i = 0; i < pPrefabObject.size(); ++i)
		{
			if (L"Stargate" == pPrefabObject[i]->GetName())
			{
				pStructure = pPrefabObject[i];
				break;
			}
		}
	}

	Vec3 vPos = pStructure->Transform()->GetLocalPos();
	Vec3 vScale = pStructure->Collider()->GetOffsetScale()* pStructure->Transform()->GetLocalScale();

	vPos.y = pStructure->Transform()->GetLocalPos().y - vScale.y / 2 - vOrgGameObjectScale.y / 2.f;
	vPos.x = pStructure->Transform()->GetLocalPos().x - vScale.x / 2 + 20.f;

	m_vInstanciatedPos = vPos;
	bool bCount[5] = { 0,0,0,0,0 };
	int iBreakCount = 0;

	bool bBool = false;
	int iMid = 0;

	Vec3 vAddedPos{};
	
	// 기소서에 쓸거 // 소팅한 이유
	sort(pPrefabObject.begin(), pPrefabObject.end(), [](CGameObject* _pObj1, CGameObject* _pObj2)
	{
		return _pObj1->Transform()->GetLocalPos().x < _pObj2->Transform()->GetLocalPos().x;
	});


	for (size_t i = 0; i < pPrefabObject.size(); ++i)
	{
		if (OBJ_TYPE::GROUNDUNIT != pPrefabObject[i]->GetObjType() && OBJ_TYPE::AIRUNIT != pPrefabObject[i]->GetObjType())
		{
			continue;
		}

		Vec3 vPrefabPos = pPrefabObject[i]->Transform()->GetLocalPos();
		Vec3 vPrefabScale = pPrefabObject[i]->Transform()->GetLocalScale()*pPrefabObject[i]->Collider()->GetOffsetScale();

		if (((vPrefabPos.x + vPrefabScale.x / 2 >= m_vInstanciatedPos.x - vOrgGameObjectScale.x / 2 && vPrefabPos.x + vPrefabScale.x / 2 <= m_vInstanciatedPos.x + vOrgGameObjectScale.x / 2)
			&& (vPrefabPos.y <= m_vInstanciatedPos.y + vOrgGameObjectScale.y / 2 && vPrefabPos.y >= m_vInstanciatedPos.y - vOrgGameObjectScale.y / 2))
			|| ((vPrefabPos.x - vPrefabScale.x / 2 >= m_vInstanciatedPos.x - vOrgGameObjectScale.x / 2 && vPrefabPos.x - vPrefabScale.x / 2 <= m_vInstanciatedPos.x + vOrgGameObjectScale.x / 2)
				&& (vPrefabPos.y <= m_vInstanciatedPos.y + vOrgGameObjectScale.y / 2 && vPrefabPos.y >= m_vInstanciatedPos.y - vOrgGameObjectScale.y / 2))
			|| ((vPrefabPos.x <= m_vInstanciatedPos.x + vOrgGameObjectScale.x / 2 && vPrefabPos.x >= m_vInstanciatedPos.x - vOrgGameObjectScale.x / 2)
				&& (vPrefabPos.y >= m_vInstanciatedPos.y - vOrgGameObjectScale.y / 2 && vPrefabPos.y <= m_vInstanciatedPos.y + vOrgGameObjectScale.y / 2)))
		{
			m_vInstanciatedPos.x = vPrefabPos.x + vPrefabScale.x;
			if (!bBool)
			{
				iMid = i;
				bBool = true;
			}
		}
	}


	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();

	if (OBJ_TYPE::GROUNDUNIT == pOrgGameObject->GetObjType() || OBJ_TYPE::AIRUNIT == pOrgGameObject->GetObjType())
	{
		if (nullptr != pGameObject && OBJ_TYPE::GROUNDUNIT == pOrgGameObject->GetObjType())
		{
			m_vInstanciatedPos.z = 100.f;
			Instantiate(pGameObject, L"Ally", m_vInstanciatedPos, Vec3(0.f, 0.f, 0.f));


			// 유닛별 사운드
			wstring SoundName = pGameObject->GetOriginObj()->GetName();
			SoundName += L"Birth";
			CSound* pSound = CResMgr::GetInst()->Load<CSound>(SoundName);
			pSound->Play(1);
		}
		else if (nullptr != pGameObject && OBJ_TYPE::AIRUNIT == pOrgGameObject->GetObjType())
		{
			m_vInstanciatedPos.z = 95.f;
			Instantiate(pGameObject, L"Ally", m_vInstanciatedPos, Vec3(0.f, 0.f, 0.f));
			
			// 유닛별 사운드
			wstring SoundName = pGameObject->GetOriginObj()->GetName();
			SoundName += L"Birth";
			CSound* pSound = CResMgr::GetInst()->Load<CSound>(SoundName);
			pSound->Play(1);
		}
	}

	PopFirstPrefab();
	CUnitMgr::GetInst()->SetUnitName(L"");

}

void CBuildingScript::SetBuildTree()
{
	if (L"Gateway" == Object()->GetName())
	{
		++m_iBuildingCount;
		if(!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::GATEWAY_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::GATEWAY_LEVEL, true);
	}
	else if (L"Forge" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::FORGE_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::FORGE_LEVEL, true);
	}
	else if (L"Cybernetics Core" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL, true);
	}
	else if (L"Robotics Facility" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ROBOTICS_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::ROBOTICS_LEVEL, true);
	}
	else if (L"Stargate" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::STARGATE_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::STARGATE_LEVEL, true);
	}
	else if (L"Citadel of Adun" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ADUN_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::ADUN_LEVEL, true);
	}
	else if (L"Observatory" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::OBSERVATORY_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::OBSERVATORY_LEVEL, true);
	}
	else if (L"Robotics Support Bay" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::SUPPORTBAY_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::SUPPORTBAY_LEVEL, true);
	}
	else if (L"Fleet Beacon" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::BEACON_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::BEACON_LEVEL, true);
	}
	else if (L"Templar Archives" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL, true);
	}
	else if (L"Arbiter Tribunal" == Object()->GetName())
	{
		++m_iBuildingCount;
		if (!CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARBITER_LEVEL))
			CBuildingMgr::GetInst()->SetBuildLevel((UINT)BUILD_LEVEL::ARBITER_LEVEL, true);
	}
}

void CBuildingScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CBuildingScript::OnCollision(CCollider * _pOther)
{
}

void CBuildingScript::OnCollisionExit(CCollider * _pOther)
{

}
void CBuildingScript::Save(FILE * _pFile)
{
	bool temp = false;
	bool temp2 = false;
	bool temp3 = false;

	fwrite(&m_iBuildingCount, sizeof(int), 1, _pFile);
	fwrite(&temp, sizeof(bool), 1, _pFile);
	fwrite(&temp2, sizeof(bool), 1, _pFile);
	fwrite(&temp3, sizeof(bool), 1, _pFile);
	fwrite(&m_iShield, sizeof(int), 1, _pFile);
	fwrite(&m_iHp, sizeof(int), 1, _pFile);
	fwrite(&m_iMineralCost, sizeof(int), 1, _pFile);
	fwrite(&m_iGasCost, sizeof(int), 1, _pFile);
	fwrite(&m_bExplosion, sizeof(bool), 1, _pFile);
	fwrite(&m_iMaxHp, sizeof(int), 1, _pFile);
	fwrite(&m_iMaxShield, sizeof(int), 1, _pFile);
}
void CBuildingScript::Load(FILE * _pFile)
{
	bool temp = false;
	bool temp2 = false;
	bool temp3 = false;
	
	fread(&m_iBuildingCount, sizeof(int), 1, _pFile);
	fread(&temp, sizeof(bool), 1, _pFile);
	fread(&temp2, sizeof(bool), 1, _pFile);
	fread(&temp3, sizeof(bool), 1, _pFile);
	fread(&m_iShield, sizeof(int), 1, _pFile);
	fread(&m_iHp, sizeof(int), 1, _pFile);
	fread(&m_iMineralCost, sizeof(int), 1, _pFile);
	fread(&m_iGasCost, sizeof(int), 1, _pFile);
	fread(&m_bExplosion, sizeof(bool), 1, _pFile);
	fread(&m_iMaxHp, sizeof(int), 1, _pFile);
	fread(&m_iMaxShield, sizeof(int), 1, _pFile);
}
//for (int i = 0; i < pPrefabObject.size(); ++i)
//{
//	if (OBJ_TYPE::GROUNDUNIT != pPrefabObject[i]->GetObjType() && OBJ_TYPE::AIRUNIT != pPrefabObject[i]->GetObjType())
//	{
//		continue;
//	}

//	Vec3 vPrefabPos = pPrefabObject[i]->Transform()->GetLocalPos();
//	Vec3 vPrefabScale = pPrefabObject[i]->Transform()->GetLocalScale()*pPrefabObject[i]->Collider()->GetOffsetScale();

//if (((vPrefabPos.y + vPrefabScale.y / 2 >= vPos.y - vOrgGameObjectScale.y / 2 && vPrefabPos.y + vPrefabScale.y / 2 <= vPos.y + vOrgGameObjectScale.y / 2)
//	&& (vPrefabPos.x + vPrefabScale.x / 2 + vAddedPos.x/2>= vPos.x - vOrgGameObjectScale.x / 2 && vPrefabPos.x + vPrefabScale.x / 2 <= vPos.x + vOrgGameObjectScale.x / 2 + vAddedPos.x / 2))
//	|| ((vPrefabPos.y - vPrefabScale.y / 2 >= vPos.y - vOrgGameObjectScale.y / 2 && vPrefabPos.y - vPrefabScale.y / 2 <= vPos.y + vOrgGameObjectScale.y / 2)
//		&& (vPrefabPos.x + vPrefabScale.x / 2 + vAddedPos.x / 2 >= vPos.x - vOrgGameObjectScale.x / 2 && vPrefabPos.x + vPrefabScale.x / 2 <= vPos.x + vOrgGameObjectScale.x / 2 + vAddedPos.x / 2))
//	|| ((vPrefabPos.y + vPrefabScale.y / 2 >= vPos.y - vOrgGameObjectScale.y / 2 && vPrefabPos.y + vPrefabScale.y / 2 <= vPos.y + vOrgGameObjectScale.y / 2)
//		&& (vPrefabPos.x - vPrefabScale.x / 2 + vAddedPos.x / 2 >= vPos.x - vOrgGameObjectScale.x / 2 && vPrefabPos.x - vPrefabScale.x / 2 <= vPos.x + vOrgGameObjectScale.x / 2 + vAddedPos.x / 2))
//	|| ((vPrefabPos.y - vPrefabScale.y / 2 >= vPos.y - vOrgGameObjectScale.y / 2 && vPrefabPos.y - vPrefabScale.y / 2 <= vPos.y + vOrgGameObjectScale.y / 2)
//		&& (vPrefabPos.x - vPrefabScale.x / 2 + vAddedPos.x / 2 >= vPos.x - vOrgGameObjectScale.x / 2 && vPrefabPos.x - vPrefabScale.x / 2 <= vPos.x + vOrgGameObjectScale.x / 2 + vAddedPos.x / 2)))
//{
//m_vInstanciatedPos.x += vPrefabScale.x / 2;
//vAddedPos.x += vPrefabScale.x;
//vAddedPos.x += vOrgGameObjectScale.x / 2;
//}	

//for (int i = 0; i < 5; ++i)
//{
//if ((vPrefabPos.y >= vPos.y - vOrgGameObjectScale.y && vPrefabPos.y <= vPos.y + vOrgGameObjectScale.y)
//	&& (vPrefabPos.x >= vPos.x + vOrgGameObjectScale.x*i  && vPrefabPos.x <= vPos.x + vOrgGameObjectScale.x*(i + 1)))
//{
//	if (bCount[i])
//		continue;

//	bCount[i] = true;

//	if (i > 0 && !bCount[i - 1])
//	{
//		bCount[i] = false;
//		break;
//	}

//	++iBreakCount;

//	m_vInstanciatedPos.x += vPrefabScale.x/2;
//	break;
//}
//}
//for (int i = 4; i >= 0; --i)
//{
//	if (bCount[i])
//	{
//		m_vInstanciatedPos.x += (i + 1) * vOrgGameObjectScale.x;
//		break;
//	}
//}
//m_vInstanciatedPos += vAddedPos;