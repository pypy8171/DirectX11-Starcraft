#include "stdafx.h"
#include "BuildingMgr.h"

#include "YongEngine/Camera.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Collider.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/KeyMgr.h"

#include "YongEngine/Scene.h"

#include "LoadSciprtMgr.h"

#include "ScriptMgr.h"
#include "UIMgr.h"


CBuildingMgr::CBuildingMgr()
	: m_pClickedPrefab(nullptr)
	, m_strStructureName{}
	, m_arrBuildLevel{}
	, m_bBuildAvailable(false)
	, m_fDT(0.f)
	, m_bFinish(false)
{
	m_arrBuildLevel[0] = true;
	SetScriptType((UINT)SCRIPT_TYPE::BUILDINGMGR);
}


CBuildingMgr::~CBuildingMgr()
{
}

int CBuildingMgr::update()
{
	m_fDT += DT;


	if (m_fDT < 60)
	{
		//CSceneMgr::GetInst()->ChangeScene();
		//CLoadSciprtMgr::LoadScene(L"C:\\Users\\YongHwan\\source\\repos\\YongEngine\\Game_Release\\content\\Scene\\map-5.scene");
		return 0;

	}

	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	vector<CGameObject*> vec = CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Opponent")->GetObjVec();
	vector<CGameObject*> vecOppoBuilding;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i]->GetObjType() == OBJ_TYPE::BUILDING)
		{
			vecOppoBuilding.push_back(vec[i]);
		}
	}

	//if (vecOppoBuilding.size() == 0 && !m_bFinish)
	//{

	//	vector<CGameObject*> vecButton = CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Button")->GetObjVec();
	//	for (size_t i = 0; i < vecButton.size(); ++i)
	//	{
	//		if (L"Victory" == vecButton[i]->GetName())
	//			return 0;
	//	}

	//	CGameObject* pGameObject = new CGameObject;

	//	pGameObject->SetName(L"Victory");
	//	pGameObject->AddComponent(new CMeshRender);
	//	pGameObject->AddComponent(new CCollider);
	//	pGameObject->SetObjType(OBJ_TYPE::UI);

	//	pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	//	pGameObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

	//	CTexture* pTexVicOff = CResMgr::GetInst()->Load<CTexture>(L"VictoryOff");
	//	CTexture* pTexVecOn = CResMgr::GetInst()->Load<CTexture>(L"VictoryOn");
	//	if (nullptr == pTexVicOff)
	//	{
	//		pTexVicOff = CResMgr::GetInst()->Load<CTexture>(L"VictoryOff", L"Texture\\Texture\\Protoss\\UI\\Victory0.png");
	//		pTexVecOn = CResMgr::GetInst()->Load<CTexture>(L"VictoryOn", L"Texture\\Texture\\Protoss\\UI\\Victory1.png");
	//	}

	//	pGameObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexVicOff);

	//	pGameObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
	//	pGameObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

	//	pScene->AddGameObject(L"Button", pGameObject);
	//	Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();

	//	pGameObject->Transform()->SetLocalScale(Vec3(pTexVicOff->GetWidth(), pTexVicOff->GetHeight(),0.f));
	//	pGameObject->Transform()->SetLocalPos(vCamPos);

	//	CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"Victory");
	//	pSound->Play(1);
	//	m_bFinish = true;

	//	//Camera()-> // 카메라 휠 이동 안되게
	//}

	return 0;
}

int CBuildingMgr::lateupdate()
{
	return 0;
}
