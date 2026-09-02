#include "stdafx.h"
#include "ButtonScript.h"

#include "YongEngine/Core.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Collider.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Texture.h"

#include "MouseScript.h"
#include "UnitScript.h"
#include "BuildingScript.h"

#include "UnitMgr.h"
#include "UIMgr.h"
#include "BuildingMgr.h"
#include "SkillMgr.h"

#include "YongEngine/Core.h"

#include "ScriptMgr.h"

CButtonScript::CButtonScript()
	: m_vBeforePos(Vec3(0, 0, 0))
	, m_vButtonOrgPos(Vec3(0, 0, 0))
	, m_vButtonIdxPos(Vec3(0, 0, 0))
	, m_eButtonChapter(BUTTON_CHAPTER::NONE)
	, m_iButtionIdx(-1)
	, m_bCollide(false)
	, m_pClickedObj(nullptr)
	, m_strClickedObjLayer{}
	, m_pCurTargetObj(nullptr)
	, m_eSkill(SKILL::NONE)
	, m_bScaleUp(false)

{
	SetScriptType((UINT)SCRIPT_TYPE::BUTTONSCRIPT);
}


CButtonScript::~CButtonScript()
{
}

int CButtonScript::update()
{
	// 클릭 된 경우
	// 프로브 일반인경우 // lbuild누른경우 // hbuild 누른 경우
	BUTTON_CHAPTER eButtonChapter = CUIMgr::GetInst()->GetButtonChapter();

	CLayer* pMouseLayer = CSceneMgr::GetInst()->GetLayer(L"Mouse");
	CGameObject* pMouseObject = pMouseLayer->GetObjVec()[0];

	CMouseScript* pMouseScript = (CMouseScript*)pMouseObject->Script()[0]; // 마우스 스크립트 추가시 변경
	m_pCurTargetObj = pMouseScript->GetTargetObj();

	tResolution tResolution = CCore::GetInst()->GetResoultion();

	if (!m_bScaleUp)
	{
		m_vScaleUp = Object()->Transform()->GetLocalScale()*1.7f;
		m_bScaleUp = true;
	}

	Object()->Transform()->SetLocalScale(Vec3(m_vScaleUp.x *tResolution.x / 760 * 0.75,
		m_vScaleUp.y *tResolution.y / 760 * 0.8, 1.f));
	Object()->Transform()->SetLocalPos(Vec3(Object()->GetParent()->Transform()->GetLocalPos().x + m_vButtonIdxPos.x*tResolution.x / 760,
		Object()->GetParent()->Transform()->GetLocalPos().y + (m_vButtonIdxPos.y + 4)*tResolution.y / 480, 1));


	if (CUnitMgr::GetInst()->GetButtonOwner() == nullptr)
		return 0;

	if (nullptr == m_pCurTargetObj)
		return 0;

	if (BUTTON_CHAPTER::PROBE_BASE == eButtonChapter)
	{
		ProbeBaseUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::PROBE_LBUILD == eButtonChapter)
	{
		ProbeLBuildUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::PROBE_HBUILD == eButtonChapter)
	{
		ProbeHBuildUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::NEXUS == eButtonChapter)
	{
		NexusButtonUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::GATEWAY == eButtonChapter)
	{
		GatewayButtonUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::ROBOTICS == eButtonChapter)
	{
		RoboticsButtonUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::STARGATE == eButtonChapter)
	{
		StargateButtonUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::ATT_UNIT == eButtonChapter)
	{
		AttUnitButtonUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::NATT_UNIT == eButtonChapter)
	{
		NAttUnitButtonUI(m_bPressed);
	}
	else if (BUTTON_CHAPTER::EMPTY == eButtonChapter)
	{
		EmptyButtonUI(m_bPressed);
	}



	

	return 0;
}

int CButtonScript::lateupdate()
{

	return 0;
}


void CButtonScript::ProbeBaseUI(bool _bool)
{
	CTexture* pTex = nullptr;
	if (0 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"LBuildBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"LBuildBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"HBuildBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"HBuildBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MiningBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MiningBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"AttBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"AttBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::ProbeLBuildUI(bool _bool)
{
	CTexture* pTex = nullptr;


	if (0 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::GATEWAY_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"CyberneticsCoreBtnMousePressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"CyberneticsCoreBtnMouseOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CyberneticsCoreBtnMouseOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::GATEWAY_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ShieldBatteryBtnMousePressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ShieldBatteryBtnMouseOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ShieldBatteryBtnMouseOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CancelBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CancelBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ForgeBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ForgeBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"GatewayBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"GatewayBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::FORGE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"PhotonCannonBtnMousePressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"PhotonCannonBtnMouseOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"PhotonCannonBtnMouseOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"NexusBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"NexusBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"PylonBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"PylonBtnMouseOn");
		
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"AssimilatorBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"AssimilatorBtnMouseOn");
		
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::ProbeHBuildUI(bool _bool)
{
	CTexture* pTex = nullptr;

	if (0 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ROBOTICS_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::STARGATE_LEVEL)
			&& CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CancelBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CancelBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ROBOTICS_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::STARGATE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ADUN_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"StargatePressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"StargateOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"StargateOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}


void CButtonScript::PressButton(bool _bool)
{
}

void CButtonScript::AttUnitButtonUI(bool _bool) // 아비터 커세어 닥템
{
	if (nullptr == m_pCurTargetObj)
		return;
	CTexture* pTex = nullptr;
	if (0 == GetButtonIdx())
	{
		if (_bool)
		{
			if (L"Arbiter" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"RecallPressed");
			else if (L"Corsair" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"WapOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}
		else
		{
			if (L"Arbiter" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"RecallOn");
			else if (L"Corsair" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"WapOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		if (_bool)
		{
			if (L"Arbiter" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"StasisFieldOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}
		else
		{
			if (L"Arbiter" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"StasisFieldOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		if (_bool)
		{
			if (L"DarkTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonCoalescencePressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}
		else
		{
			if (L"DarkTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonCoalescenceOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"PatrolPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"PatrolOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"HoldPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"HoldOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"AttBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"AttBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::NAttUnitButtonUI(bool _bool)
{
	CTexture* pTex = nullptr;

	if (nullptr == m_pCurTargetObj)
		return;

	if (0 == GetButtonIdx())
	{
		if (_bool)
		{
			if (L"HighTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"StormPressed");
			else if (L"DarkArchon" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"FeedBackOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}
		else
		{
			if (L"HighTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"StormOn");
			else if (L"DarkArchon" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"FeedBackOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		if (_bool)
		{
			if (L"HighTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"IllusionOn");
			else if (L"DarkArchon" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"MindControlPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}
		else
		{
			if (L"HighTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"IllusionOn");
			else if (L"DarkArchon" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"MindControlOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");

		}
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		if (_bool)
		{
			if (L"HighTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonCoalescencePressed");
			else if (L"DarkArchon" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ConfusionUpgradeOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}
		else
		{
			if (L"HighTemplar" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonCoalescenceOn");
			else if (L"DarkArchon" == m_pCurTargetObj->GetName())
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ConfusionUpgradeOn");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"PatrolPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"PatrolOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"HoldPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"HoldOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMousePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMouseOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::NexusButtonUI(bool _bool)
{
	CTexture* pTex = nullptr;
	if (0 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ProbePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ProbeOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::GatewayButtonUI(bool _bool)
{
	CTexture* pTex = nullptr;
	if (0 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"DarkTemplarPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"DarkTemplarOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"DarkTemplarOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ZealotPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ZealotOn");


		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"DragoonPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"DragoonOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"DragoonOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"HighTemplarPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"HighTemplarOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"HighTemplarOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::StargateButtonUI(bool _bool)
{
	CTexture* pTex = nullptr;
	if (0 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARBITER_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ArbiterPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ArbiterOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ArbiterOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyOn");

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyOn");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CorsairPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CorsairOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ScoutPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ScoutOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::BEACON_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"CarrierPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"CarrierOn");
		} 
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"CarrierOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::RoboticsButtonUI(bool _bool)
{
	CTexture* pTex = nullptr;
	if (0 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyPressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		if (_bool)
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ShuttlePressed");
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ShuttleOn");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::OBSERVATORY_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ObserverPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ObserverOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ObserverOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::SUPPORTBAY_LEVEL))
		{
			if (_bool)
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ReaverPressed");
			else
				pTex = CResMgr::GetInst()->Load<CTexture>(L"ReaverOn");
		}
		else
			pTex = CResMgr::GetInst()->Load<CTexture>(L"ReaverOff");

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::EmptyButtonUI(bool _bool)
{
	CTexture* pTex = nullptr;
	if (0 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(-56.f, -42.f, -5.f);
	}
	else if (1 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(0.f, -42.f, -5.f);
	}
	else if (2 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(56.f, -42.f, -5.f);
	}
	else if (3 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(-56.f, 0.f, -5.f);
	}
	else if (4 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(0.f, 0.f, -5.f);
	}
	else if (5 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(56.f, 0.f, -5.f);
	}
	else if (6 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(-56.f, 40.f, -5.f);
	}
	else if (7 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(0.f, 40.f, -5.f);
	}
	else if (8 == GetButtonIdx())
	{
		CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
		m_vButtonIdxPos = Vec3(+56.f, 40.f, -5.f);
	}
}

void CButtonScript::OnCollisionEnter(CCollider * _pOther)
{

}

void CButtonScript::OnCollision(CCollider * _pOther)
{
		//_pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx()
	CLayer* pLayer = CSceneMgr::GetInst()->GetLayer(L"Mouse");
	if (_pOther->Object()->GetLayerIdx() != pLayer->GetIdx())
		return;

	if (_pOther->Object()->GetName() == L"Drag" || _pOther->Object()->GetName() == L"Structure")
		return;

	if (KEYAWAY(KEY_TYPE::KEY_LBTN) && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		CSound* pSound;
		if (nullptr == CResMgr::GetInst()->Load<CSound>(L"Button"))
		{
			pSound = CResMgr::GetInst()->Load<CSound>(L"Button", L"Sound\\Button.wav");
		}
		else
			pSound = CResMgr::GetInst()->Load<CSound>(L"Button");
		pSound->Play(1);

		BUTTON_CHAPTER eButton = BUTTON_CHAPTER::NONE;

		m_eButtonChapter = CUIMgr::GetInst()->GetButtonChapter();


		if (BUTTON_CHAPTER::PROBE_BASE == CUIMgr::GetInst()->GetButtonChapter() && 0 == GetButtonIdx())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::PROBE_LBUILD);
		}
		else if (BUTTON_CHAPTER::PROBE_BASE == CUIMgr::GetInst()->GetButtonChapter() && 1 == GetButtonIdx())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::PROBE_HBUILD);
		}
		else if (BUTTON_CHAPTER::PROBE_LBUILD == CUIMgr::GetInst()->GetButtonChapter() && 2 == GetButtonIdx() || KEYTAB(KEY_TYPE::KEY_ESC))
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::PROBE_BASE);
		}
		else if (BUTTON_CHAPTER::PROBE_HBUILD == CUIMgr::GetInst()->GetButtonChapter() && 2 == GetButtonIdx())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::PROBE_BASE);
		}
		m_bPressed = false;
	}


	if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::PROBE_LBUILD == CUIMgr::GetInst()->GetButtonChapter()  && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		CPrefab* pPrefab = nullptr;
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::GATEWAY_LEVEL)){
			if (0 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Cybernetics Core"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::GATEWAY_LEVEL)){
			if (1 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Shield Battery"); }
		}
		if (3 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Forge"); }
		if (4 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Gateway"); }
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::FORGE_LEVEL)){
			if (5 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Photon Cannon"); }
		}
		if (6 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Nexus"); }
		if (7 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Pylon"); }
		if (8 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Assimilator"); }

		if (nullptr == pPrefab)
			return;

		CBuildingScript* pBuildScript = nullptr;
		if (pBuildScript == nullptr)
		{
			for (size_t i = 0; i < pPrefab->GetOriginObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == pPrefab->GetOriginObj()->Script()[i]->GetScriptType())
				{
					pBuildScript = (CBuildingScript*)pPrefab->GetOriginObj()->Script()[i];
				}
			}
		}
		if (pBuildScript != nullptr)
		{
			if (CUIMgr::GetInst()->GetMineral() < pBuildScript->GetMineralCost())
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"NotEnoughMineral", L"Sound\\NotEnoughMineral.wav");
				pSound->Play(1);
				return;
			}
			else
				CUIMgr::GetInst()->SetMineral(-(pBuildScript->GetMineralCost()*0.25));
		}

		m_strClickedObjLayer = L"Ally";
		m_pClickedObj = pPrefab;

		CBuildingMgr::GetInst()->SetStructureName(m_strClickedObjLayer);
		CBuildingMgr::GetInst()->SetClickedPrefab(m_pClickedObj);

		//CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::PROBE_BASE);
	}
	else if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::PROBE_HBUILD == CUIMgr::GetInst()->GetButtonChapter() && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		CPrefab* pPrefab = nullptr;
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ROBOTICS_LEVEL))
		{
			if (0 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Observatory"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::STARGATE_LEVEL)
			&& CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL))
		{
			if (1 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Arbiter Tribunal"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ROBOTICS_LEVEL))
		{
			if (3 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Robotics Support Bay"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::STARGATE_LEVEL))
		{
			if (4 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Fleet Beacon"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ADUN_LEVEL))
		{
			if (5 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Templar Archives"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (6 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Robotics Facility"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (7 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Stargate"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (8 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Citadel of Adun"); }
		}

		if (nullptr == pPrefab)
			return;

		CBuildingScript* pBuildScript = nullptr;
		if (pBuildScript == nullptr)
		{
			for (size_t i = 0; i < pPrefab->GetOriginObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == pPrefab->GetOriginObj()->Script()[i]->GetScriptType())
				{
					pBuildScript = (CBuildingScript*)pPrefab->GetOriginObj()->Script()[i];
				}
			}
		}
		if (pBuildScript != nullptr)
		{
			if (CUIMgr::GetInst()->GetMineral() < pBuildScript->GetMineralCost())
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"NotEnoughMineral", L"Sound\\NotEnoughMineral.wav");
				pSound->Play(1);
				return;
			}
			else
				CUIMgr::GetInst()->SetMineral(-(pBuildScript->GetMineralCost())*0.25);
		}

		m_strClickedObjLayer = L"Ally";
		m_pClickedObj = pPrefab;

		CBuildingMgr::GetInst()->SetStructureName(m_strClickedObjLayer);
		CBuildingMgr::GetInst()->SetClickedPrefab(m_pClickedObj);

		//CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::PROBE_BASE);
	}

	if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::NEXUS == CUIMgr::GetInst()->GetButtonChapter() && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		CPrefab* pPrefab = nullptr;

		if (CUIMgr::GetInst()->GetClick())
			return;

		if (6 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Probe"); }


		if (nullptr == pPrefab)
			return;
		CUnitScript* pUnitScript = nullptr;
		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < pPrefab->GetOriginObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == pPrefab->GetOriginObj()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)pPrefab->GetOriginObj()->Script()[i];
				}
			}
		}
		if (pUnitScript != nullptr)
		{
			if (CUIMgr::GetInst()->GetMineral() < pUnitScript->GetMineralCost())
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"NotEnoughMineral", L"Sound\\NotEnoughMineral.wav");
				pSound->Play(1);
				return;
			}
			else
				CUIMgr::GetInst()->SetMineral(-(pUnitScript->GetMineralCost()));
		}


		m_strClickedObjLayer = L"Ally";
		m_pClickedObj = pPrefab;

		CUnitMgr::GetInst()->SetUnitName(m_strClickedObjLayer);
		CUnitMgr::GetInst()->SetClickedPrefab(m_pClickedObj);

		CUIMgr::GetInst()->SetProduceBtnClick(true);
		CUIMgr::GetInst()->SetClick(true);
	}
	else if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::GATEWAY == CUIMgr::GetInst()->GetButtonChapter() && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		CPrefab* pPrefab = nullptr;
		if (CUIMgr::GetInst()->GetClick())
			return;

		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL))
		{
			if (3 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"DarkTemplar"); }
		}
		if (6 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Zealot"); }
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::CORE_LEVEL))
		{
			if (7 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Dragoon"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARCHIEVE_LEVEL))
		{
			if (8 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"HighTemplar"); }
		}

		if (nullptr == pPrefab)
			return;

		CUnitScript* pUnitScript = nullptr;
		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < pPrefab->GetOriginObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == pPrefab->GetOriginObj()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)pPrefab->GetOriginObj()->Script()[i];
				}
			}
		}
		if (pUnitScript != nullptr)
		{
			if (CUIMgr::GetInst()->GetMineral() < pUnitScript->GetMineralCost())
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"NotEnoughMineral", L"Sound\\NotEnoughMineral.wav");
				pSound->Play(1);
				return;
			}
			else
				CUIMgr::GetInst()->SetMineral(-(pUnitScript->GetMineralCost()));
		}

		m_strClickedObjLayer = L"Ally";
		m_pClickedObj = pPrefab;

		CUnitMgr::GetInst()->SetUnitName(m_strClickedObjLayer);
		CUnitMgr::GetInst()->SetClickedPrefab(m_pClickedObj);

		CUIMgr::GetInst()->SetProduceBtnClick(true);
		CUIMgr::GetInst()->SetClick(true);
	}
	else if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::ROBOTICS == CUIMgr::GetInst()->GetButtonChapter() && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		CPrefab* pPrefab = nullptr;

		if (CUIMgr::GetInst()->GetClick())
			return;

		if (6 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Shuttle"); }
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::OBSERVATORY_LEVEL))
		{
			if (7 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Observer"); }
		}
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::SUPPORTBAY_LEVEL))
		{
			if (8 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Reaver"); }
		}

		if (nullptr == pPrefab)
			return;

		CUnitScript* pUnitScript = nullptr;
		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < pPrefab->GetOriginObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == pPrefab->GetOriginObj()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)pPrefab->GetOriginObj()->Script()[i];
				}
			}
		}
		if (pUnitScript != nullptr)
		{
			if (CUIMgr::GetInst()->GetMineral() < pUnitScript->GetMineralCost())
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"NotEnoughMineral", L"Sound\\NotEnoughMineral.wav");
				pSound->Play(1);
				return;
			}
			else
				CUIMgr::GetInst()->SetMineral(-(pUnitScript->GetMineralCost()));
		}

		m_strClickedObjLayer = L"Ally";
		m_pClickedObj = pPrefab;

		CUnitMgr::GetInst()->SetUnitName(m_strClickedObjLayer);
		CUnitMgr::GetInst()->SetClickedPrefab(m_pClickedObj);

		CUIMgr::GetInst()->SetProduceBtnClick(true);
		CUIMgr::GetInst()->SetClick(true);
	}
	else if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::STARGATE == CUIMgr::GetInst()->GetButtonChapter() && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		CPrefab* pPrefab = nullptr;

		if (CUIMgr::GetInst()->GetClick())
			return;

		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::ARBITER_LEVEL))
		{
			if (3 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Arbiter"); }
		}
		if (6 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Corsair"); }
		if (7 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Scout"); }
		if (CBuildingMgr::GetInst()->GetBuildLevel((UINT)BUILD_LEVEL::BEACON_LEVEL))
		{
			if (8 == GetButtonIdx()) { pPrefab = CResMgr::GetInst()->Load<CPrefab>(L"Carrier"); }
		}

		if (nullptr == pPrefab)
			return;

		CUnitScript* pUnitScript = nullptr;
		if (pUnitScript == nullptr)
		{
			for (size_t i = 0; i < pPrefab->GetOriginObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == pPrefab->GetOriginObj()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)pPrefab->GetOriginObj()->Script()[i];
				}
			}
		}
		if (pUnitScript != nullptr)
		{
			if (CUIMgr::GetInst()->GetMineral() < pUnitScript->GetMineralCost())
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"NotEnoughMineral", L"Sound\\NotEnoughMineral.wav");
				pSound->Play(1);
				return;
			}
			else
				CUIMgr::GetInst()->SetMineral(-(pUnitScript->GetMineralCost()));
		}

		m_strClickedObjLayer = L"Ally";
		m_pClickedObj = pPrefab;

		CUnitMgr::GetInst()->SetUnitName(m_strClickedObjLayer);
		CUnitMgr::GetInst()->SetClickedPrefab(m_pClickedObj);

		CUIMgr::GetInst()->SetProduceBtnClick(true);
		CUIMgr::GetInst()->SetClick(true);
	}
	else if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::ATT_UNIT == CUIMgr::GetInst()->GetButtonChapter() && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		//if (SKILL::NONE != CSkillMgr::GetInst()->GetSkill())
		//{
		//	return;
		//}
		if (nullptr == m_pCurTargetObj)
			return;

		if (L"Arbiter" == m_pCurTargetObj->GetName())
		{
			if (0 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::RECALL); }
			if (1 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::STASISFIELD); }
		}
		else if (L"Corsair" == m_pCurTargetObj->GetName())
		{
			if (0 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::WAP); }
		}
		else if (L"DarkTemplar" == m_pCurTargetObj->GetName())
		{
			if (0 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::DARKARCHONCOALESCENCE);}
		}
		
		//if(7 == GetButtonIdx())
	}
	else if (KEYAWAY(KEY_TYPE::KEY_LBTN) && BUTTON_CHAPTER::NATT_UNIT == CUIMgr::GetInst()->GetButtonChapter() && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		if (nullptr == m_pCurTargetObj)
			return;

		if (L"HighTemplar" == m_pCurTargetObj->GetName())
		{
			if (0 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::STORM); }
			if (1 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::ILLUSION); }
			if (2 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::ARCHONCOALESCENCE); }
		}
		else if (L"DarkArchon" == m_pCurTargetObj->GetName())
		{
			if (0 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::FEEDBACK); }
			if (1 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::MINDCONTROL); }
			if (2 == GetButtonIdx()) { CSkillMgr::GetInst()->SetSkill(SKILL::CONFUSION); }
		}
	}

	if (KEYHOLD(KEY_TYPE::KEY_LBTN) && _pOther->Object()->GetLayerIdx() == CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"Mouse")->GetIdx())
	{
		BUTTON_CHAPTER eButton = BUTTON_CHAPTER::NONE;

		m_eButtonChapter = CUIMgr::GetInst()->GetButtonChapter();

		m_bPressed = true;
	}
}

void CButtonScript::OnCollisionExit(CCollider * _pOther)
{
}

void CButtonScript::Save(FILE * _pFile)
{
	fwrite(&m_vButtonIdxPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vBeforePos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vButtonOrgPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_bScaleUp, sizeof(bool), 1, _pFile);
	fwrite(&m_vScaleUp, sizeof(Vec3), 1, _pFile);
	fwrite(&m_iButtionIdx, sizeof(int), 1, _pFile);
}

void CButtonScript::Load(FILE * _pFile)
{
	fread(&m_vButtonIdxPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vBeforePos, sizeof(Vec3), 1, _pFile);
	fread(&m_vButtonOrgPos, sizeof(Vec3), 1, _pFile);
	fread(&m_bScaleUp, sizeof(bool), 1, _pFile);
	fread(&m_vScaleUp, sizeof(Vec3), 1, _pFile);
	fread(&m_iButtionIdx, sizeof(int), 1, _pFile);
}
