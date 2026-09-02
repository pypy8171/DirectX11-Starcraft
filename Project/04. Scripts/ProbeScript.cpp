#include "stdafx.h"
#include "ProbeScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Transform.h"
#include "YongEngine/Collider.h"
#include "YongEngine/Grid.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"
#include "YongEngine/EventMgr.h"

#include "Scripts/TileScript.h"

#include "TileMgr.h"
#include "UIMgr.h"
#include "ScriptMgr.h"
#include "BuildingMgr.h"

CProbeScript::CProbeScript()
	//: m_iStartX(0)
	//, m_iStartY(0)
	//, m_iEndX(0)
	//, m_iEndY(0)
	//, m_vLaterPos(Vec3(0,0,0))
	//, m_vAccPos(Vec3(0, 0, 0))
	: m_bSetChapter(false)
	, m_vBeforePos(Vec3(0, 0, 0))
	, m_bHoldMineral(false)
	, m_bHoldGas(false)
	, m_bAtar(false)
	, m_vMiningPos(Vec3(0, 0, 0))
	, m_pTargetObj(nullptr)
	, m_pMineralObj(nullptr)
	, m_vProbeDir(Vec3(0, 0, 0))
	, m_bBacktoResource(false)
	, m_bAtt(false)

{
	m_iShield = 40;
	m_iHp = 40;
	// 공중공격 지상공격 구분해야함
	m_iGroundAtt = 5;
	m_iAttSpeed = 2;
	m_fSpeed = 110.f;
	SetScriptType((UINT)SCRIPT_TYPE::PROBESCRIPT);
}


CProbeScript::~CProbeScript()
{
}

int CProbeScript::update()
{
	Mining();

	if(KEYTAB(KEY_TYPE::KEY_RBTN) && Object()->GetTargetted())
	{
		Object()->SetUnitStatus(UNIT_STATUS::MOVE);
	}

	return 0;
}

int CProbeScript::lateupdate()
{
	return 0;
}

void CProbeScript::Key()
{

}

void CProbeScript::UIBtn()
{
}

void CProbeScript::Mining()
{
	if (UNIT_STATUS::MINING != Object()->GetUnitStatus())
	{
		for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		{
			if (Object()->GetChild()[i]->GetName() == L"ProbeMining")
			{
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT,(INT_PTR)Object()->GetChild()[i],NULL });
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object()->GetChild()[i] ,NULL });
				m_bAtt = false;
			}
		}
	}

	if (UNIT_STATUS::MINING ==Object()->GetUnitStatus()) // 왔다갔다 하면서 캐고있는 상태
	{
		if (!m_bAtt)
		{
			CString strProbeMining = Object()->GetName().c_str();
			strProbeMining += L"Att";

			CTexture* pTex = CResMgr::GetInst()->Load<CTexture>((wstring)strProbeMining);

			CGameObject* pGameObject = new CGameObject;
			pGameObject->SetName(L"ProbeMining");
			pGameObject->AddComponent(new CMeshRender);
			pGameObject->AddComponent(new CAnimator2D);

			CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

			pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
			pGameObject->MeshRender()->SetMaterial(pMtrl);


			pGameObject->Animator2D()->AddAnimation(L"Texture\\Animation2D\\Protoss\\Effect\\Probe_att\\", L"ProbeAtt", true);

			pGameObject->Transform()->SetLocalScale(Vec3(48.f, 32.f, 1.f));

			Object()->AddChild(pGameObject);

			m_bAtt = true;
		}


		if (m_bBacktoResource)
		{
			BacktoGas();
			BacktoMineral();
		}
		BacktoNexus();
	}

	for (size_t i = 0; i < Object()->GetChild().size(); ++i)
	{

		CUnitScript* pUnitScript = nullptr;

		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < Object()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)Object()->Script()[i];
				}
			}
		}

		m_vDir = pUnitScript->GetAnimDir();
		m_vLaterPos = Object()->Transform()->GetLocalPos();
		m_vDir.Normalize();



		Vec3 vPos = Object()->Transform()->GetLocalPos() + 24.f * m_vDir; // m_vdir 0임 unitscript에서 못가져옴

		if (L"ProbeMining" == Object()->GetChild()[i]->GetName())
		{
			Object()->GetChild()[i]->Animator2D()->PlayAnim(L"ProbeAtt", true);

		}

		if (L"OreMineral" == Object()->GetChild()[i]->GetName())
		{
			Object()->GetChild()[i]->Transform()->SetLocalPos(vPos);
		}
		Object()->GetChild()[i]->Transform()->SetLocalPos(vPos);
	}
}

void CProbeScript::BacktoNexus()
{
	CUnitScript* pUnitScript = nullptr;

	if (m_bHoldMineral || m_bHoldGas)
	{
		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < Object()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)Object()->Script()[i];
				}
			}
		}

		Vec3 vOjbPos = Object()->Transform()->GetLocalPos();

		vector<Vec3> vecNexusPos = CBuildingMgr::GetInst()->GetStartingPoint();
		if (vecNexusPos.size() == 0)
			return;

		float fDist1 = 0.f;
		float fDist2 = 0.f;
		int iIdx = 0;

		for (size_t i = 0; i < vecNexusPos.size(); ++i)
		{
			fDist1 = sqrt((vecNexusPos[i].x - vOjbPos.x)*(vecNexusPos[i].x - vOjbPos.x) + (vecNexusPos[i].y - vOjbPos.y)*(vecNexusPos[i].y - vOjbPos.y));
			if (fDist2 == 0.f)
			{
				fDist2 = fDist1;
				iIdx = i;
			}
			else if (fDist2 < fDist1)
				continue;
			else if (fDist2 > fDist1)
			{
				fDist2 = fDist1;
				iIdx = i;
			}
		}

		m_vProbeDir = vecNexusPos[iIdx] - Object()->Transform()->GetLocalPos();

		pUnitScript->SetDir(m_vProbeDir);
		m_vProbeDir.Normalize();

		vOjbPos.x += m_vProbeDir.x *DT*pUnitScript->GetUnitSpeed();
		vOjbPos.y += m_vProbeDir.y *DT*pUnitScript->GetUnitSpeed();

		Object()->Transform()->SetLocalPos(vOjbPos);
		pUnitScript->GroundUnitAnimation();
	}
}

void CProbeScript::BacktoMineral()
{
	if (nullptr == m_pTargetObj || m_bHoldMineral)
		return;

	CUnitScript* pUnitScript = nullptr;

	if (pUnitScript == nullptr)
	{
		for (size_t i = 0; i < Object()->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)Object()->Script()[i];
			}
		}
	}

	if (L"Mineral" == m_pTargetObj->GetName()/* || L"Gas" == m_pTargetObj->GetName()*/)
	{
		CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
		CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

		int iTileSize = pGridObject->Grid()->GetTileSize();
		Vec3 vMineralPos = m_pTargetObj->Transform()->GetLocalPos() + pGridObject->Grid()->GetTransformed();
		Vec2 vIdx = Vec2((int)((vMineralPos.x + iTileSize / 2) / iTileSize), (int)((vMineralPos.y + iTileSize / 2) / iTileSize));

		Vec3 vDist = m_pTargetObj->Transform()->GetLocalPos() - Transform()->GetLocalPos();

		Vec3 vProbePos = Transform()->GetLocalPos();

		pUnitScript->m_iStartX = (int)vIdx.x - (int)(vDist.x / iTileSize);
		pUnitScript->m_iStartY = (int)vIdx.y - (int)(vDist.y / iTileSize);
		pUnitScript->m_iEndX = (int)vIdx.x;
		pUnitScript->m_iEndY = (int)vIdx.y;

		pUnitScript->Astar();
	}
}

void CProbeScript::BacktoGas()
{
	if (nullptr == m_pTargetObj || m_bHoldGas)
		return;

	CUnitScript* pUnitScript = nullptr;

	if (pUnitScript == nullptr)
	{
		for (size_t i = 0; i < Object()->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)Object()->Script()[i];
			}
		}
	}

	if (L"Gas" == m_pTargetObj->GetName())
	{
		CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
		CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

		int iTileSize = pGridObject->Grid()->GetTileSize();
		Vec3 vMineralPos = m_pTargetObj->Transform()->GetLocalPos() + pGridObject->Grid()->GetTransformed();
		Vec2 vIdx = Vec2((int)((vMineralPos.x + iTileSize / 2) / iTileSize), (int)((vMineralPos.y + iTileSize / 2) / iTileSize));

		Vec3 vDist = m_pTargetObj->Transform()->GetLocalPos() - Transform()->GetLocalPos();

		Vec3 vProbePos = Transform()->GetLocalPos();

		pUnitScript->m_iStartX = (int)vIdx.x - (int)(vDist.x / iTileSize);
		pUnitScript->m_iStartY = (int)vIdx.y - (int)(vDist.y / iTileSize);
		pUnitScript->m_iEndX = (int)vIdx.x;
		pUnitScript->m_iEndY = (int)vIdx.y;

		pUnitScript->Astar();
	}
}

void CProbeScript::OnCollisionEnter(CCollider * _pOther)
{
	CUnitScript* pUnitScript = nullptr;

	if (Object()->Collider() != _pOther && (L"Mineral" == _pOther->Object()->GetName() ||
		L"Gas" == _pOther->Object()->GetName()))
	{
		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < Object()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)Object()->Script()[i];
				}
			}
		}
		pUnitScript->Reset();

		m_pTargetObj = _pOther->Object();
		m_bBacktoResource = false;
		m_vMiningPos = Object()->Transform()->GetLocalPos();

		Object()->SetUnitStatus(UNIT_STATUS::MINING);
	}

	if (Object()->Collider() != _pOther && L"Nexus" == _pOther->Object()->GetName() && (m_bHoldMineral || m_bHoldGas))
	{
		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < Object()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)Object()->Script()[i];
				}
			}
		}
		pUnitScript->Reset();
		for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		{
			CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT,(INT_PTR)Object()->GetChild()[i],NULL });
			CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object()->GetChild()[i] ,NULL });
		}
		if (m_bHoldMineral)
			CUIMgr::GetInst()->SetMineral(8);
		else if (m_bHoldGas)
			CUIMgr::GetInst()->SetGas(8);

		m_bHoldMineral = false;
		m_bHoldGas = false;
		m_bBacktoResource = true;

		// 여기서 미네랄, 가스 수치 올리면됨
	}
	m_fAccDT = 0.f;
}

void CProbeScript::OnCollision(CCollider * _pOther)
{
	if (Object()->Collider() != _pOther && L"Mineral" == _pOther->Object()->GetName() && !m_bHoldMineral)
	{
		m_fAccDT += DT;
		if (m_fAccDT > 5.f)
		{
			m_bHoldMineral = true;
		}

		//if(true == _pOther->Object()->GetOccupancied())
		//{	
		//	CLayer* pPrefabLayer = CSceneMgr::GetInst()->GetLayer(L"Prefab");
		//	vector<CGameObject*> pPrefabObject = pPrefabLayer->GetObjVec();
		//	for (int i = 0; i < pPrefabObject.size(); ++i)
		//	{
		//		if (pPrefabObject[i]->GetObjType() != OBJ_TYPE::RESOURCE|| pPrefabObject[i] == _pOther->Object())
		//		{
		//			continue;
		//		}

		//		Vec3 vPrefabPos = pPrefabObject[i]->Transform()->GetLocalPos(); // 
		//		Vec3 vPos = vPrefabPos - Object()->Transform()->GetLocalPos();

		//		Vec3 vDir = vPrefabPos - vPos;
		//		vPos.x += vDir * 속도*DT;
		//		vPos.y += vDir * 속도*DT;

		//		Object()->Transform()->SetLocalPos(vPos);
		//	}
		//}
	}

	if (Object()->Collider() != _pOther && L"Gas" == _pOther->Object()->GetName() && !m_bHoldGas)
	{
		m_fAccDT += DT;
		if (m_fAccDT > 5.f)
		{
			m_bHoldGas = true;
		}
	}
}

void CProbeScript::OnCollisionExit(CCollider * _pOther)
{
	if (Object()->Collider() != _pOther && L"Mineral" == _pOther->Object()->GetName())
	{
		//m_fAccDT = 0.f;

		for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		{
			if (Object()->GetChild()[i]->GetName() == (L"OreMineral"))
				return;
		}

		CString strProbeMining = L"MineralOreChunck00";

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>((wstring)strProbeMining);

		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
		CGameObject* pGameObject = new CGameObject;
		pGameObject->SetName(L"OreMineral");
		pGameObject->AddComponent(new CMeshRender);

		CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

		pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pGameObject->MeshRender()->SetMaterial(pMtrl);
		pGameObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);

		pGameObject->Transform()->SetLocalScale(Vec3(32.f, 32.f, 1.f));

		Object()->AddChild(pGameObject);

	}
	//CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::ADD_CHILD,(INT_PTR)Object(),(INT_PTR)pGameObject });

	if (Object()->Collider() != _pOther && L"Gas" == _pOther->Object()->GetName())
	{
		//m_fAccDT = 0.f;

		for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		{
			if (Object()->GetChild()[i]->GetName() == (L"OreGas"))
				return;
		}

		CString strProbeMining = L"GasOreChunck00";

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>((wstring)strProbeMining);

		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
		CGameObject* pGameObject = new CGameObject;
		pGameObject->SetName(L"OreGas");
		pGameObject->AddComponent(new CMeshRender);

		CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

		pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pGameObject->MeshRender()->SetMaterial(pMtrl);
		pGameObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);

		pGameObject->Transform()->SetLocalScale(Vec3(32.f, 32.f, 1.f));

		Object()->AddChild(pGameObject);
		//CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::ADD_CHILD,(INT_PTR)Object(),(INT_PTR)pGameObject });
	}
}

