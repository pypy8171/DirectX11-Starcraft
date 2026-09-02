#include "stdafx.h"
#include "ProduceScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/MeshRender.h"
#include "Transform.h"

#include "YongEngine/Core.h"

#include "Animator2D.h"
#include "Animation2D.h"

#include "YongEngine/ResMgr.h"
#include "YongEngine/PathMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/EventMgr.h"

#include "StatusScript.h"
#include "MouseScript.h"

#include "UnitMgr.h"
#include "UIMgr.h"
#include "ScriptMgr.h"
#include "BuildingScript.h"

CProduceScript::CProduceScript()
	: m_fAccDT(0)
	, m_pBuildingScript(nullptr)
	, m_pBeforeObj(nullptr)
{
	SetScriptType((UINT)SCRIPT_TYPE::PRODUCESCRIPT);
	for (int i = 0; i < 5; ++i)
	{
		m_pMtrl[i] = nullptr;
	}
	init();
}


CProduceScript::~CProduceScript()
{
	for (int i = 0; i < 5; ++i)
	{
		m_pMtrl[i] = nullptr;
	}
}

void CProduceScript::init()
{
	wstring strProducePath = L"Texture\\Texture\\Protoss\\UI\\Produce\\Frame\\frame_0.png";
	if (nullptr != CResMgr::GetInst()->Load<CTexture>(L"Frame.png"))
		return;

	CTexture* pFrameTex = CResMgr::GetInst()->Load<CTexture>(L"Frame.png", strProducePath);

	strProducePath = L"Texture\\Texture\\Protoss\\UI\\Produce\\Bar\\bar_0.png";
	pFrameTex = CResMgr::GetInst()->Load<CTexture>(L"Bar1.png", strProducePath);

	strProducePath = L"Texture\\Texture\\Protoss\\UI\\Produce\\Bar\\bar_1.png";
	pFrameTex = CResMgr::GetInst()->Load<CTexture>(L"Bar2.png", strProducePath);

	//
	wstring strIconFolderPath = CPathMgr::GetResPath();

	strIconFolderPath += L"Texture\\Texture\\Protoss\\UI\\Produce\\Icon\\";

	wstring strIconPngPath = strIconFolderPath + L"*.png";

	wstring strIconRelativePath;
	WIN32_FIND_DATA Icondata{};
	HANDLE hIconFind = FindFirstFile(strIconPngPath.c_str(), &Icondata);


	map<wstring, CRes*> pIconTexture = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);
	while (FindNextFile(hIconFind, &Icondata))
	{
		strIconRelativePath = wstring(strIconPngPath + Icondata.cFileName);

		map<wstring, CRes*>::iterator iconiter = pIconTexture.find(strIconRelativePath);

		wstring strMidPath = L"Texture\\Texture\\Protoss\\UI\\Produce\\Icon\\";
		strMidPath += Icondata.cFileName;

		map<wstring, CRes*>::iterator iter2 = pIconTexture.find(Icondata.cFileName);
		if (iter2 != pIconTexture.end())
			continue;

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(Icondata.cFileName, strMidPath);
	}

	FindClose(hIconFind);

}

int CProduceScript::update()
{
	if (nullptr == Object()->MeshRender())
		return false;

	// 타겟이 유닛일때 안보이게 해야함.

	//if (CUIMgr::GetInst()->IsTargetEmpty()) // 현재 타겟은 유닛이다 라고 조건 줘야 함
	//	return 0;
	tResolution vResolution = CCore::GetInst()->GetResoultion();


	CGameObject* pGameObject = Object();

	if (Object() != m_pBeforeObj)
	{
		// 전에 있던거 지움
		// 다시 돌아오면 오브젝트(빌드 스크립드)의 벡터 가져와서 
	}

	if (L"Nexus" != pGameObject->GetName() && L"Stargate" != pGameObject->GetName() && L"Gateway" != pGameObject->GetName()
		&& L"Robotics Facility" != pGameObject->GetName())
	{
		//for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		//{
		//	if (L"Icon" == Object()->GetChild()[i]->GetName())
		//	{
		//		Object()->GetChild()[i]->MeshRender()->SetRender(true);
		//	}
		//}
		return 0;
	}
	//else
	//{
	//	Object()->MeshRender()->SetRender(true);

	//}

	if (m_pBuildingScript == nullptr)
	{
		for (size_t i = 0; i < Object()->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == Object()->Script()[i]->GetScriptType())
			{
				m_pBuildingScript = (CBuildingScript*)Object()->Script()[i];
			}
		}
	}

	if (!m_pBuildingScript->GetBuildComplete())
		return 0;

	CLayer* pLayer = CSceneMgr::GetInst()->GetLayer(L"ProtossUI");
	vector<CGameObject*> vecObj = pLayer->GetObjVec();

	//CStatusScript* pScript = nullptr;
	CTexture* pTex = nullptr;
	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		if (L"Status" == vecObj[i]->GetName())
		{
			pTex = vecObj[i]->MeshRender()->GetSharedMaterial()->GetTexture();
		}
	}

	if (pTex != nullptr)
	{
		if (L"Frame.png" == pTex->GetName())
		{
			for (size_t i = 1; i < Object()->GetChild().size(); ++i)
			{
				Object()->GetChild()[i]->MeshRender()->SetRender(true);
			}
		}
		else
		{
			for (size_t i = 1; i < Object()->GetChild().size(); ++i)
			{
				Object()->GetChild()[i]->MeshRender()->SetRender(false);
			}
		}
	}


	if (CUIMgr::GetInst()->GetProduceBtnClick() && Object()->GetChild().size() < 6)
	{
		CUIMgr::GetInst()->SetProduce(true);

		CGameObject* pIcon = new CGameObject;
		pIcon->SetName(L"Icon");
		pIcon->AddComponent(new CMeshRender);

		pIcon->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pIcon->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		pIcon->Transform()->SetLocalScale(Vec3(32.f*vResolution.x / 760 *0.9, 32.f*vResolution.y / 480 * 0.8, 1.f));

		m_pMtrl[Object()->GetChild().size() - 1] = pIcon->MeshRender()->GetCloneMaterial();
		Object()->AddChild(pIcon);
		//CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::ADD_CHILD,(INT_PTR)Object() , (INT_PTR)pIcon });

		CUIMgr::GetInst()->SetProduceBtnClick(false);

		CPrefab* pPrefabObject = CUnitMgr::GetInst()->GetClickedPrefab();
		wstring strPrefabName = pPrefabObject->GetName();
		CUIMgr::GetInst()->SubtractName(strPrefabName);

		strPrefabName += L"Icon.png";

		CTexture* pIconTex = CResMgr::GetInst()->Load<CTexture>((wstring)strPrefabName);
		m_pMtrl[Object()->GetChild().size() - 2]->SetData(SHADER_PARAM::TEX_0, pIconTex);

		CUIMgr::GetInst()->SetClick(false);
		m_pBuildingScript->SetProduce(true);
		m_pBuildingScript->AddClickedPrefab(pPrefabObject);
		CUnitMgr::GetInst()->SetClickedPrefab(false);
	}


	m_pBeforeObj = Object();

	
	for (size_t i = 1; i < Object()->GetChild().size(); ++i)
	{
		CGameObject* pGameObjet = Object()->GetChild()[i];
		Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
		if (i == 1)
			Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vCamPos.x - 59.f*vResolution.x/760, -200 *vResolution.y / 480 + vCamPos.y + 20.f*vResolution.y / 480, 3.f));
		else if (i == 2)
			Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vCamPos.x - 59.f*vResolution.x / 760, -200 *vResolution.y / 480 + vCamPos.y - 17.f*vResolution.y / 480, 3.f));
		else
			Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vCamPos.x + 40*(i - 2)*vResolution.x / 760 - 60.f*vResolution.x / 760, -200 *vResolution.y / 480 + vCamPos.y - 17.f*vResolution.y / 480, 3.f));
	}
	

	if (nullptr != m_pMtrl[0] && true == CUIMgr::GetInst()->GetProduce())
		Produce();


	return 0;
}

void CProduceScript::Produce()
{
	m_fAccDT += DT;

	if (m_fAccDT > 3.f)
	{
		m_fAccDT = 0;

		if (1 == Object()->GetChild().size())
		{
			m_pBuildingScript->SetProduce(false);
			CUIMgr::GetInst()->SetProduce(false);
		}

		m_pBuildingScript->SetProduceOut(true);

		for (size_t i = 0; i < Object()->GetChild().size()-1; ++i)
		{
			if (Object()->GetChild().size() > 2)
			{
				if (i == Object()->GetChild().size() - 2)
				{
					CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT,(INT_PTR)Object()->GetChild()[i + 1],NULL });
					CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object()->GetChild()[i + 1] ,NULL });
				}
				else
				{
					m_pMtrl[i]->SetData(SHADER_PARAM::TEX_0, m_pMtrl[i + 1]->GetTexture());
				}
			}
			else if (Object()->GetChild().size() > 1 && Object()->GetChild().size() <= 2)
			{
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT,(INT_PTR)Object()->GetChild()[1],NULL });
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object()->GetChild()[1] ,NULL });
			}
			else if (Object()->GetChild().size() <= 1)
				return;
		}
		


	}
}


int CProduceScript::lateupdate()
{
	return 0;
}
