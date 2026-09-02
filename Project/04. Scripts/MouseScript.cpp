#include "stdafx.h"
#include "MouseScript.h"
#include "YongEngine/GameObject.h"

#include "YongEngine/Core.h"
#include "YongEngine/Device.h"
#include "YongEngine/Script.h"

#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Collider.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Material.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/KeyMgr.h"
#include "YongEngine/ResMgr.h"


#include "YongEngine/Material.h"

#include "YongEngine/Animator2D.h"
#include "YongEngine/Animation2D.h"

#include "BuildingMgr.h"
#include "ScriptMgr.h"

#include "CameraScript.h"


CMouseScript::CMouseScript()
	: m_pMark(nullptr)
	, m_bCollide(false)
	, m_pTargetObj(nullptr)
	, m_pBeforeTargetObj(nullptr)
	, m_vDragPos(Vec3(1.f, 1.f, 1.f))
	, m_bDrag(false)
	, m_bStructure(false)
	, m_pBuildingPrefabObj(nullptr)
	, m_iSoundCount(0)
	, m_pVicMtrl(nullptr)
{
	SetScriptType((UINT)SCRIPT_TYPE::MOUSESCRIPT);
	init();
}


CMouseScript::~CMouseScript()
{
}


void CMouseScript::init()
{
	CTexture* pTex = nullptr;
	if (nullptr == CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalCompleted"))
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalCompleted", L"Texture\\Texture\\Protoss\\Building\\Arbiter Tribunal\\Arbiter Tribunal_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"AssimilatorCompleted", L"Texture\\Texture\\Protoss\\Building\\Assimilator\\Assimilator_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunCompleted", L"Texture\\Texture\\Protoss\\Building\\Citadel of Adun\\Citadel of Adun_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Cybernetics CoreCompleted", L"Texture\\Texture\\Protoss\\Building\\Cybernetics Core\\Cybernetics Core_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconCompleted", L"Texture\\Texture\\Protoss\\Building\\Fleet Beacon\\Fleet Beacon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ForgeCompleted", L"Texture\\Texture\\Protoss\\Building\\Forge\\Forge_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"GatewayCompleted", L"Texture\\Texture\\Protoss\\Building\\Gateway\\Gateway_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"NexusCompleted", L"Texture\\Texture\\Protoss\\Building\\Nexus\\Nexus_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryCompleted", L"Texture\\Texture\\Protoss\\Building\\Observatory\\Observatory_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Photon CannonCompleted", L"Texture\\Texture\\Protoss\\Building\\Photon Cannon\\Photon Cannon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"PylonCompleted", L"Texture\\Texture\\Protoss\\Building\\Pylon\\Pylon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityCompleted", L"Texture\\Texture\\Protoss\\Building\\Robotics Facility\\Robotics Facility_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Shield BatteryCompleted", L"Texture\\Texture\\Protoss\\Building\\Shield Battery\\Shield Battery_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StargateCompleted", L"Texture\\Texture\\Protoss\\Building\\Stargate\\Stargate_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesCompleted", L"Texture\\Texture\\Protoss\\Building\\Templar Archives\\Templar Archives_0.png");
	}
	if (nullptr == CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayCompleted"))
	{
		CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayCompleted", L"Texture\\Texture\\Protoss\\Building\\Robotics Support Bay\\Robotics Support Bay_0.png");
	}
}


int CMouseScript::update()
{
	//SetCursor(false);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	if (!pCurScene->CheckLayer(L"Camera"))
		return 0;

	CLayer* pLayer = CSceneMgr::GetInst()->GetLayer(L"Camera");

	if (0 == pLayer->GetObjVec().size())
		return 0;
	CGameObject* pCameraObject = pLayer->GetObjVec()[0];
	Vec3 vCamPos = pCameraObject->Transform()->GetLocalPos();
	Transform()->SetLocalPos(Vec3(CKeyMgr::GetInst()->GetMousePos().x + vCamPos.x,
		CKeyMgr::GetInst()->GetMousePos().y + vCamPos.y, 1));
	CKeyMgr::GetInst()->SetMousePos(Vec3(CKeyMgr::GetInst()->GetMousePos().x + vCamPos.x,
		CKeyMgr::GetInst()->GetMousePos().y + vCamPos.y, 1));

	if (nullptr == Object()->Animator2D())
		return false;

	if (false == Object()->Animator2D()->GetFileLoadOn())
		return false;

	CGameObject* pGameObject = Object();

	tResolution vResolution = CCore::GetInst()->GetResoultion();
	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	POINT tPoint = { (LONG)vMousePos.x, (LONG)vMousePos.y };

	ScreenToClient(CDevice::GetInst()->GetMainhWnd(), &tPoint);

	Vec3 vPos = Transform()->GetLocalPos();

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		m_vDragPos = Object()->Transform()->GetLocalPos();
	}
	else if (KEYHOLD(KEY_TYPE::KEY_LBTN) ) // 누르고 있으면 드래그
	{

		m_bDrag = true;
		Object()->Animator2D()->PlayAnim(L"DragCursor.png", true);
		if (0 == Object()->GetChild().size())
		{
			CGameObject* pGameObject = new CGameObject;
			pGameObject->SetName(L"Drag");
			pGameObject->AddComponent(new CMeshRender);
			pGameObject->AddComponent(new CCollider);

			pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
			pGameObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

			CTexture* pDragTex = CResMgr::GetInst()->Load<CTexture>(L"DragRect");
			if(nullptr == pDragTex)
				pDragTex = CResMgr::GetInst()->Load<CTexture>(L"DragRect", L"Texture\\Texture\\Protoss\\UI\\Mouse\\Drag\\DragRect01.png");

			pGameObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pDragTex);

			pGameObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
			pGameObject->Transform()->SetLocalScale(Object()->Transform()->GetLocalPos());
			pGameObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pGameObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
			Object()->AddChild(pGameObject);
	
		}
		if (0 != pGameObject->GetChild().size())
		{
			Vec3 vDragGap = Object()->Transform()->GetLocalPos() - m_vDragPos;
			Vec3 vDragPos = Object()->Transform()->GetLocalPos() - vDragGap * 0.5f;
			pGameObject->GetChild()[0]->Transform()->SetLocalPos(vDragPos);
			Vec3 vDragScale = pGameObject->GetChild()[0]->Transform()->GetLocalScale();
			pGameObject->GetChild()[0]->Transform()->SetLocalScale(vDragGap);
		}

		if (0 != Object()->GetChild().size())
		{
			Vec3 vDragScale = Object()->GetChild()[0]->Transform()->GetLocalScale();

			if (vDragScale.x < 10 && vDragScale.y < 10)
			{
				m_bDrag = false;
			}
		}
	}
	else if (KEYAWAY(KEY_TYPE::KEY_LBTN))
	{
		m_bDrag = false;
		if (0 != pGameObject->GetChild().size())
		{
			pGameObject->GetChild()[0]->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
			pGameObject->GetChild()[0]->Transform()->SetLocalPos(Object()->Transform()->GetLocalPos());
		}
	}
	else
	{
		CCameraScript* pCameraScript = nullptr;
		if (pCameraScript == nullptr)
		{
			for (size_t i = 0; i < pCameraObject->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::CAMERASCRIPT == pCameraObject->Script()[i]->GetScriptType())
				{
					pCameraScript = (CCameraScript*)pCameraObject->Script()[i];
				}
			}
		}
		UINT iCamDir = pCameraScript->GetCameraDir();
		// 구석탱이들 먼저 조건문 4개 추가
		if (iCamDir == (UINT)CAMERA_DIR::LEFT)
		{
			Object()->Animator2D()->PlayAnim(L"ArrowLeft", true);
		}
		else if (iCamDir == (UINT)CAMERA_DIR::RIGHT)
		{
			Object()->Animator2D()->PlayAnim(L"ArrowRight", true);
		}
		// 얘네 좀 이상
		else if (iCamDir == (UINT)CAMERA_DIR::UP) // GAMEVIEW_Y/2
		{
			Object()->Animator2D()->PlayAnim(L"ArrowUp", true);
		}
		else if (iCamDir == (UINT)CAMERA_DIR::DOWN)
		{
			Object()->Animator2D()->PlayAnim(L"ArrowDown", true);
		}
		else if(iCamDir == (UINT)CAMERA_DIR::NONE)
		{
			Object()->Animator2D()->PlayAnim(L"NormalCursor", true); // 텍스쳐는 1인거 쓰고 180도 회전
		}
	}

	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		CBuildingMgr::GetInst()->SetClickedPrefab(nullptr);
		CBuildingMgr::GetInst()->SetStructureName(L"");

	}

	// 건물
	if (nullptr == CBuildingMgr::GetInst()->GetClickedPrefab())
	{
		for (size_t i = 0; i < Object()->GetChild().size(); ++i)
		{
			if (L"Structure" == Object()->GetChild()[i]->GetName())
			{
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT,(INT_PTR)Object()->GetChild()[i],NULL });
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object()->GetChild()[i] ,NULL });
				m_bStructure = false;
			}
		}
	}

	if (nullptr != CBuildingMgr::GetInst()->GetClickedPrefab() && !m_bStructure)
	{
		CGameObject* pBuildPrefabObj = new CGameObject;
		pBuildPrefabObj->SetName(L"Structure");
		pBuildPrefabObj->AddComponent(new CMeshRender);
		pBuildPrefabObj->AddComponent(new CCollider);

		pBuildPrefabObj->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pBuildPrefabObj->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		wstring name = CBuildingMgr::GetInst()->GetClickedPrefab()->GetName();

		name += L"Completed";

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(name);

		if (pTex == nullptr)
			return 0;

		pBuildPrefabObj->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);

		pBuildPrefabObj->Transform()->SetLocalScale(Vec3(pTex->GetWidth(), pTex->GetHeight(), 1.f));

		pBuildPrefabObj->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
		pBuildPrefabObj->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

		Object()->AddChild(pBuildPrefabObj);

		m_bStructure = true;
	}

	for (size_t i = 0; i < Object()->GetChild().size(); ++i)
	{
		if (L"Structure" == Object()->GetChild()[i]->GetName())
		{
			Vec3 vOwn = Object()->Transform()->GetLocalPos();
			Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vOwn.x, vOwn.y,100.f));
		}
	}


	//Transform()->SetLocalPos(CKeyMgr::GetInst()->GetMousePos()+vCamPos );
	//CKeyMgr::GetInst()->SetMousePos(CKeyMgr::GetInst()->GetMousePos() + vCamPos);

	if(GetDrag())
		Drag();

	return 0;
}


void CMouseScript::Drag()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();

	vector<CGameObject*> vecTemp;

	for (size_t i = 0; i < pCurScene->GetCurTargetObjVec().size(); ++i)
	{
		vecTemp.push_back(pCurScene->GetCurTargetObjVec()[i]);
	}
	pCurScene->SetCurTargetObjVecClear();

	CLayer* pPrefabLayer = CSceneMgr::GetInst()->GetLayer(L"Ally");
	vector<CGameObject*> pPrefabObject = pPrefabLayer->GetObjVec();


	if (0 == pPrefabObject.size())
		return;

	for (size_t i = 0; i < pPrefabObject.size(); ++i)
	{
		pPrefabObject[i]->SetTargetted(false);
	}

	if (0 == Object()->GetChild().size())
		return;

	Vec3 vDragMousePos =Object()->GetChild()[0]->Transform()->GetLocalPos();
	Vec3 vDragMouseScale = Object()->GetChild()[0]->Transform()->GetLocalScale();

	int iCount = 0;
	CGameObject* pGameObject = nullptr;

	for (size_t i = 0; i < pPrefabObject.size(); ++i)
	{
		if (pPrefabObject[i]->GetObjType() != OBJ_TYPE::AIRUNIT && pPrefabObject[i]->GetObjType() != OBJ_TYPE::GROUNDUNIT
			&& pPrefabObject[i]->GetObjType() != OBJ_TYPE::BUILDING)
		{
			continue;
		}
		if (L"PylonRadius" == pPrefabObject[i]->GetName())
			continue;

		Vec3 vPrefabPos = pPrefabObject[i]->Transform()->GetLocalPos();
		float fFirstY = vDragMousePos.y + vDragMouseScale.y / 2.f;
		float fSecondY = vDragMousePos.y - vDragMouseScale.y / 2.f;
		float fUpY = 0.f;
		float fDownY = 0.f;
		float fFirstX = vDragMousePos.x + vDragMouseScale.x / 2.f;
		float fSecondX = vDragMousePos.x - vDragMouseScale.x / 2.f;
		float fLeftX = 0.f;
		float fRightX = 0.f;

		if (fFirstY - fSecondY > 0) { fUpY = fFirstY;	fDownY = fSecondY; }
		else { fDownY = fFirstY;	fUpY = fSecondY; }
		if (fFirstX - fSecondX > 0) { fRightX = fFirstX; fLeftX = fSecondX; }
		else { fLeftX = fFirstX; fRightX = fSecondX; }

		if (vPrefabPos.y <= fUpY && vPrefabPos.y >= fDownY && vPrefabPos.x <= fRightX && vPrefabPos.x >= fLeftX)
		{
			pCurScene->AddTargetObj(pPrefabObject[i]);
			pPrefabObject[i]->SetTargetted(true);
			++iCount;
			pGameObject = pPrefabObject[i];

			if (pPrefabObject[i]->GetObjType() == OBJ_TYPE::BUILDING)
			{
				pCurScene->SetCurTargetObjVecClear();
				pCurScene->AddTargetObj(pPrefabObject[i]);
				iCount = 1;
				pGameObject = pPrefabObject[i];
				break;
			}
		}
	}

	// iCount가 0이면 그대로 나감
	if (iCount == 0)
	{
		for (size_t i = 0; i < vecTemp.size(); ++i)
		{
			pCurScene->AddTargetObj(vecTemp[i]);
		}
	}
}

void CMouseScript::awake()
{
}

void CMouseScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CMouseScript::OnCollision(CCollider * _pOther)
{
	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		if (OBJ_TYPE::UI == _pOther->Object()->GetObjType())
		{
			return;
		}

		if (nullptr != CBuildingMgr::GetInst()->GetClickedPrefab())
			return;

		//	if (L"Victory" == _pOther->Object()->GetName())
		//	{
		//		if (nullptr == _pOther->Object()->MeshRender())
		//			return;

		//		if (nullptr == m_pVicMtrl )
		//		{
		//			m_pVicMtrl = _pOther->Object()->MeshRender()->GetCloneMaterial();
		//		}
		//		CTexture* pTexVecOn = CResMgr::GetInst()->Load<CTexture>(L"VictoryOn");
		//		m_pVicMtrl->SetData(SHADER_PARAM::TEX_0, pTexVecOn);
		//	}
		//}
		//else

		if (L"PylonRadius" == _pOther->Object()->GetName())
			return;

		CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
		pCurScene->SetCurTargetObjVecClear();
		if (m_pTargetObj != _pOther->Object())
		{
			if(nullptr != m_pTargetObj)
				m_pTargetObj->SetTargetted(false);
			m_pTargetObj = _pOther->Object();
		}

		if (m_pTargetObj->GetObjType() == OBJ_TYPE::GROUNDUNIT || m_pTargetObj->GetObjType() == OBJ_TYPE::AIRUNIT)
		{
			wstring SoundName = m_pTargetObj->GetName();
			SoundName += L"Script";
			if (SoundName != L"ObserverScript")
			{
				srand(time(NULL));
				m_iSoundCount = rand() % 8;

				if (m_iSoundCount == 0) { SoundName += L"00"; }
				else if (m_iSoundCount == 1) { SoundName += L"01"; }
				else if (m_iSoundCount == 2) { SoundName += L"02"; }
				else if (m_iSoundCount == 3) { SoundName += L"03"; }
				else if (m_iSoundCount == 4) { SoundName += L"04"; }
				else if (m_iSoundCount == 5) { SoundName += L"05"; }
				else if (m_iSoundCount == 6) { SoundName += L"06"; }
				else if (m_iSoundCount == 7) { SoundName += L"07"; }
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(SoundName);
				pSound->Play(1);
			}
			else if (SoundName == L"ObserverScript")
			{
				srand(time(NULL));
				m_iSoundCount = rand() % 4;
				if (m_iSoundCount == 0) { SoundName += L"00"; }
				else if (m_iSoundCount == 1) { SoundName += L"01"; }
				else if (m_iSoundCount == 2) { SoundName += L"02"; }
				else if (m_iSoundCount == 3) { SoundName += L"03"; }
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(SoundName);
				pSound->Play(1);
			}
		}
		else if (m_pTargetObj->GetObjType() == OBJ_TYPE::BUILDING && L"PylonRadius" != _pOther->Object()->GetName())
		{
			wstring SoundName = m_pTargetObj->GetName();
			CSound* pSound = CResMgr::GetInst()->Load<CSound>(SoundName);
			pSound->Play(1);
		}
		m_pTargetObj = _pOther->Object();

		m_pTargetObj->SetTargetted(true);

		pCurScene->AddTargetObj(m_pTargetObj);

		m_bCollide = 1;
		_pOther->GetCloneMtrl()->SetData(SHADER_PARAM::INT_0, &m_bCollide);

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}

	if (L"PylonRadius" == _pOther->Object()->GetName())
	{
		if(_pOther->Object()->MeshRender()->GetRender())
			CBuildingMgr::GetInst()->SetBuildAvailable(true);
	}

	if (L"PylonRadius" != _pOther->Object()->GetName() && _pOther->Object()->GetObjType() == OBJ_TYPE::BUILDING)
	{
		CBuildingMgr::GetInst()->SetBuildAvailable(false);
	}



	if (nullptr == Object()->Animator2D())
		return;

	map<wstring, CAnimation2D*> mapMouse = Object()->Animator2D()->GetAnimationMap();
	map<wstring, CAnimation2D*>::iterator iter = mapMouse.find(L"PlayerCursor");

	if (_pOther->GetName() != L"PylonRadius") // 파일런 반경이 유닛보다 뒤 타일보다는 앞으로 해야함.  수정
		return;
	else
		Object()->Animator2D()->PlayAnim(L"PlayerCursor", true);

	if(iter != mapMouse.end())
		Object()->Animator2D()->PlayAnim(L"PlayerCursor", true);

}

void CMouseScript::OnCollisionExit(CCollider * _pOther)
{
	m_bCollide = 0;
	for (UINT i = 0; i < Script().size(); ++i)
	{
		CMaterial* pMtrl = Script()[i]->GetMaterial();
		if (pMtrl != nullptr)
			pMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}

	if (L"PylonRadius" == _pOther->Object()->GetName())
	{
		CBuildingMgr::GetInst()->SetBuildAvailable(false);
	}

	//if (L"Victory" == _pOther->Object()->GetName() && _pOther->Object()->GetObjType() == OBJ_TYPE::UI)
	//{
	//	if (nullptr == _pOther->Object()->MeshRender())
	//		return;

	//	if (m_pVicMtrl == nullptr)
	//	{
	//		m_pVicMtrl = _pOther->Object()->MeshRender()->GetCloneMaterial();
	//	}
	//	CTexture* pTexVecOff = CResMgr::GetInst()->Load<CTexture>(L"VictoryOff");
	//	m_pVicMtrl->SetData(SHADER_PARAM::TEX_0, &pTexVecOff);
	//}
}
// 프리팹 레이어 가져와서 그중에서 마우스 범위 안에 있는 애들 클릭

