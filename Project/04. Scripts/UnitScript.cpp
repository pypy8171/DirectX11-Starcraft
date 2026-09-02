#include "stdafx.h"
#include "UnitScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Collider.h"
#include "YongEngine/Grid.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/Sound.h"

#include "YongEngine/Layer.h"
#include "YongEngine/Scene.h"
#include "YongEngine/Animation2D.h"

#include "BuildingScript.h"
#include "Scripts/TileScript.h"
#include "MouseScript.h"

#include "UnitMgr.h"
#include "ScriptMgr.h"
#include "UIMgr.h"
#include "BuildingMgr.h"
#include "TileMgr.h"
#include "NumberMgr.h"

CUnitScript::CUnitScript()
	: m_iShield(0)
	, m_iHp(0)
	, m_iGroundAtt(0)
	, m_iAirAtt(0)
	, m_iAttSpeed(0)
	, m_iRange(0)
	, m_fSpeed(0)
	, m_vDir(Vec3(0.f, 0.f, 0.f))
	, m_vMarkPos(Vec3(0.f, 0.f, 0.f))
	, m_iMaxCount(0)
	, m_iBeforeMaxCount(0)
	, m_iCurTex(0)
	, m_fAccDT(0.f)
	, m_szBeforeAnimName{}
	, m_iStartX(0)
	, m_iStartY(0)
	, m_iEndX(0)
	, m_iEndY(0)
	, m_vLaterPos(Vec3(0,0,0))
	, m_vAccPos(Vec3(0, 0, 0))
	, m_vStructurePos(Vec3(0, 0, 0))
	, m_bSetChapter(false)
	, m_bAlly(false)
	, m_bWait(false)
	, m_fAccelator(0.f)
	, m_fAccelatorDT(0.f)
	, m_vDestPos(Vec3(0, 0, 0))
	, m_bFrozen(false)
	, m_bDead(false)
	, m_bFinish(false)
	, m_fAccFlozenDT(0.f)
	, m_vRecallCastingPos(Vec3(0, 0, 0))
	, m_vArmyBeforePos(Vec3(0, 0, 0))
	, m_fStopSpeed(0.f)
	, m_bRequestHpUI(false)
	, m_bCycle(false)
	, m_iMineralCost(0)
	, m_iGasCost(0)
	, m_vBeforeNodePos(Vec3(0, 0, 0))
	, m_bStart(false)
	, m_fAnimDT(0.f)
	, m_fAttDT(0.f)
	, m_bAttackOn(true)
	, m_fFloatPos(0.f)
	, m_bFloatUp(false)
	, m_iMaxHp(0)
	, m_iMaxShield(0)
	, m_bHold(false)
	, m_bReadyToAtt(false)
	, m_bStartToFind(false)
	, m_iSoundCount(0)
	, m_bFix(false)
	, m_bBallOn(false)
	, m_fRecallDT(0.f)
	, m_bFrozenReset(false)
	, m_pMtrl(nullptr)
{
	SetScriptType((UINT)SCRIPT_TYPE::UNITSCRIPT);
	
}

CUnitScript::~CUnitScript()
{
}

int CUnitScript::update()
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

	if (m_bDead)
	{
		if (!m_bFinish)
		{
			wstring dieanim = Object()->GetName();
			if (L"DarkTemplar" == Object()->GetName())
			{
				dieanim = L"Dark Templar";
			}
			else if (L"HighTemplar" == Object()->GetName())
			{
				dieanim = L"High Templar";
			}
			else if (L"DarkArchon" == Object()->GetName())
			{
				dieanim = L"Dark Archon";
			}
			dieanim += L"Die";


			Object()->Animator2D()->PlayAnim(dieanim, true);

			CAnimation2D* pCurAnim = Object()->Animator2D()->GetAnimation();
			if (pCurAnim->GetCurFrm() == pCurAnim->GetFrame().size() - 1)
			{
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object() ,NULL });
				m_bFinish = true;

				wstring SoundName = Object()->GetName();
				SoundName += L"Die";
				if (L"Probe" == Object()->GetName())
				{
					CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeDie", L"Sound\\ProbeDie.wav");
					pSound->Play(1);
				}
				else
				{
					CSound* pSound = CResMgr::GetInst()->Load<CSound>(SoundName);
					pSound->Play(1);
				}
			}
		}
		return 0;
	}

	if (Object()->GetTargetted())
	{
		//if (!m_bRequestHpUI)
		//{
		//	CNumberMgr::GetInst()->SetHpRequest(true);
		//	CNumberMgr::GetInst()->SetShieldRequest(true);
		//	CNumberMgr::GetInst()->SetObject(Object());
		//	m_bRequestHpUI = true;
		//}

		SetBtnUI();

		vector<CGameObject*> vec = CUnitMgr::GetInst()->GetTargetObjVec();

		OBJ_TYPE eType = Object()->GetObjType();
		UNIT_TYPE eUnitType = GetUnitType();

		if (OBJ_TYPE::GROUNDUNIT == Object()->GetObjType() && UNIT_TYPE::SHUTTLE != eUnitType && UNIT_TYPE::OBSERVER != eUnitType
			&& UNIT_TYPE::CORSAIR != eUnitType && UNIT_TYPE::SCOUT != eUnitType && UNIT_TYPE::CARRIER != eUnitType
			&& UNIT_TYPE::ARBITER != eUnitType && UNIT_TYPE::INTERCEPTOR != eUnitType)
		{
			if (KEYTAB(KEY_TYPE::KEY_RBTN) && Object()->GetUnitStatus() != UNIT_STATUS::FROZEN) // 
			{
				m_bWait = false;
				wstring strAnimName = Object()->GetName();
				strAnimName += L"Move";
				Object()->Animator2D()->SetCurAnimName(strAnimName);
				Reset();
				AstarKey();

				wstring SoundName = Object()->GetName();
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
		}
		else if (UNIT_TYPE::SHUTTLE == eUnitType || UNIT_TYPE::OBSERVER == eUnitType
			|| UNIT_TYPE::CORSAIR == eUnitType || UNIT_TYPE::SCOUT == eUnitType || UNIT_TYPE::CARRIER == eUnitType
			|| UNIT_TYPE::ARBITER == eUnitType || UNIT_TYPE::INTERCEPTOR == eUnitType)
		{
			if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
				m_iMaxCount = 0;

			AirUnitAnimation();
			m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();

			Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();
			if (KEYTAB(KEY_TYPE::KEY_RBTN) && Object()->GetUnitStatus() != UNIT_STATUS::FROZEN)
			{
				m_vMarkPos = CKeyMgr::GetInst()->GetMousePos();
			}
		}

		MakeAlly();
	}

	if (!m_vecNodePos.empty() && !m_bWait)
	{
		MoveByAstar();
	}

	vector<CGameObject*> vecFollow = pCurScene->GetCurTargetObjVec();

	if (nullptr != CBuildingMgr::GetInst()->GetClickedPrefab() && L"Probe" == Object()->GetName()) // 파일런 위일때
	{
		CGameObject* pPrefab = CBuildingMgr::GetInst()->GetClickedPrefab()->GetOriginObj();
		vector<CGameObject*> vecP = CSceneMgr::GetInst()->GetCurrentScene()->GetCurTargetObjVec();
		for (size_t i = 0; i < vecP.size(); ++i)
		{
			if (Object() == vecP[i])
			{
				if (L"Nexus" == pPrefab->GetName() || L"Pylon" == pPrefab->GetName() || L"Assimilator" == pPrefab->GetName())
					BuildStructure();
				else
				{
					if (CBuildingMgr::GetInst()->GetBuildAvailable())
					{
						BuildStructure();
					}
					else
					{
						if (KEYAWAY(KEY_TYPE::KEY_LBTN))
						{
							CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"CantBuild", L"Sound\\CantBuild.wav");
							pSound->Play(1);
						}
					}
				}
			}
		}
	}

	UNIT_TYPE eObjUnitType = GetUnitType();

	if (UNIT_TYPE::SHUTTLE != eObjUnitType && UNIT_TYPE::OBSERVER != eObjUnitType
		&& UNIT_TYPE::CORSAIR != eObjUnitType && UNIT_TYPE::SCOUT != eObjUnitType && UNIT_TYPE::CARRIER != eObjUnitType
		&& UNIT_TYPE::ARBITER != eObjUnitType && UNIT_TYPE::INTERCEPTOR != eObjUnitType)
	{
		if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
			m_iMaxCount = 0;

		GroundUnitAnimation(); // 0~16이 가만히 있는 상태
		m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();
	}
	else
	{
		if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
			m_iMaxCount = 0;

		AirUnitAnimation();
		m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();

		Move();
	}

	if (Object()->GetName() != L"Arbiter")
	{
		ArbiterRad();
	}

	if (UNIT_STATUS::FROZEN == Object()->GetUnitStatus())
	{
		Frozen();
	}

	if (UNIT_STATUS::RECALL == Object()->GetUnitStatus())
	{
		Recall();
	}

	if (UNIT_STATUS::STORM == Object()->GetUnitStatus())
	{
		Storm();
	}

	if (!m_bDead && L"Probe" != Object()->GetName()&& L"Shuttle" != Object()->GetName()
		&& L"Observer" != Object()->GetName() && Object()->GetUnitStatus() != UNIT_STATUS::FROZEN)
	{
		if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Opponent")->GetIdx())
			FindOpponent();
		else if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Ally")->GetIdx() )
		{
			if(m_bStartToFind)
				FindOpponent();
			else if (Object()->GetUnitStatus() == UNIT_STATUS::IDLE)
				FindOpponent();
			else if (Object()->GetUnitStatus() == UNIT_STATUS::ATTACK)
				FindOpponent();
		}

	}

	if (nullptr != Object()->GetTargetObj() && !m_bDead && UNIT_STATUS::DIE != Object()->GetTargetObj()->GetUnitStatus()
		&& Object()->GetUnitStatus() != UNIT_STATUS::FROZEN)
	{
		Attack();
	}


	if (m_iHp <= 0 && !m_bDead )
	{
		Die();
	}


	if (KEYTAB(KEY_TYPE::KEY_5))
	{
		Object()->SetTargetted(false);
		pCurScene->SetCurTargetObjVecClear();
		pCurScene->EmptyTargetObjList();
	}

	if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Ally")->GetIdx())
	{
		vector<CGameObject*> vecSelected = pCurScene->GetCurTargetObjVec();
		for (size_t i = 0; i < vecSelected.size(); ++i)
		{
			if(Object() == vecSelected[i] && Object()->GetUnitStatus() != UNIT_STATUS::FROZEN)
				InputKey();
		}
	}

	for (size_t i = 0; i < Object()->GetChild().size(); ++i)
	{
		if (L"Ally" == Object()->GetChild()[i]->GetName())
		{
			Vec3 vObjPos = Object()->Transform()->GetLocalPos();

			if (OBJ_TYPE::GROUNDUNIT == Object()->GetObjType())
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y - 10.f, vObjPos.z - 5.f));
			else if (OBJ_TYPE::AIRUNIT == Object()->GetObjType())
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y - 20.f, vObjPos.z - 5.f));
		}
	}

	if (Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT)
	{
		Vec3 vMPos = Object()->Transform()->GetLocalPos();
		Object()->Transform()->SetLocalPos(Vec3(vMPos.x, vMPos.y, 100.f));
	}
	else if (Object()->GetObjType() == OBJ_TYPE::AIRUNIT)
	{
		Vec3 vMPos = Object()->Transform()->GetLocalPos();
		Object()->Transform()->SetLocalPos(Vec3(vMPos.x, vMPos.y, 95.f));
	}

	return 0;
}

int CUnitScript::lateupdate()
{
	return 0;
}

void CUnitScript::GroundUnitAnimation()
{
	if (UNIT_STATUS::FROZEN == Object()->GetUnitStatus())
		return;

	m_fAnimDT += DT;

	Vec3 vPos = Object()->Transform()->GetLocalPos();

	Vec3 vUp = Vec3(0.f, 1.f, 0.f);

	Vec3 vRot = Transform()->GetLocalAngle();

	//if (sqrt(m_vDir.x*m_vDir.x + m_vDir.y*m_vDir.y) < 0.9)
	//	return;

	m_vDir.Normalize();

	Vec3 vAngle = Vec3(0.f, 1.f, 0.f);
	vAngle = (Vec3)XMVector3AngleBetweenNormals(vUp, m_vDir); // 사잇각

	float fAngle = (float)(vAngle.z *180.f / 3.14);

	if (fAngle > 180.f)
	{
		fAngle -= 180.f;
	}

	if (L"DarkTemplarMove" == Object()->Animator2D()->GetCurAnimName())
	{
		Object()->Animator2D()->SetCurAnimName(L"Dark TemplarMove");
	}
	else if (L"HighTemplarMove" == Object()->Animator2D()->GetCurAnimName())
	{
		Object()->Animator2D()->SetCurAnimName(L"High TemplarMove");
	}
	else if (L"DarkArchonMove" == Object()->Animator2D()->GetCurAnimName())
	{
		Object()->Animator2D()->SetCurAnimName(L"Dark ArchonNormal");
	}
	else if (L"ArchonMove" == Object()->Animator2D()->GetCurAnimName())
	{
		Object()->Animator2D()->SetCurAnimName(L"ArchonNormal");
	}
	else if (L"ProbeMove" == Object()->Animator2D()->GetCurAnimName())
	{
		Object()->Animator2D()->SetCurAnimName(L"ProbeNormal");
	}


	if (nullptr != Object()->Animator2D()->GetAnimation())
	{
		if (m_fAnimDT < Object()->Animator2D()->GetAnimation()->GetFrame()[0].fDuration)
			return;
		else
			m_fAnimDT = 0.f;
	}

	map<wstring, CAnimation2D*> maps = Object()->Animator2D()->GetAnimationMap();
	map<wstring, CAnimation2D*>::iterator iter = maps.find(Object()->Animator2D()->GetCurAnimName());

	if(iter == maps.end() )
		return;

	size_t iFrmCount = iter->second->GetFrame().size();

	int iTex = (int)(fAngle / (180.f / 17));
	if (iTex == 17)
		iTex = 16;

	if (iFrmCount > 17)
	{
		if (m_iMaxCount > (iFrmCount / 17) - 1)  // 프레임이 17 이하인 애들이 문제
		{
			m_iMaxCount = 0;
		}
	}
	else
		m_iMaxCount = 0;
	m_iCurTex = iTex;

	if (m_vDir.y == -1 || m_vDir.y == 1)
	{
		m_vDir.x = 0;
	}

	// 움직이는상태라면
	if (UNIT_STATUS::MOVE == Object()->GetUnitStatus() || UNIT_STATUS::MINING == Object()->GetUnitStatus() )
	{
		if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y < 0) )
		{
			vRot.y = 0.f;

			if (m_vDir.y < -0.9 && iFrmCount>16)
				iTex = 16;

			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
		}
		else if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y == 0))
		{
			vRot.y = 0;

			if (m_vDir.y > 0)
				iTex = 0;
			else 
			{
				if(iFrmCount>16)
					iTex = 16;
			}
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
		}
		else
		{
			vRot.y = XM_PI;
			iTex = (int)((180.f - fAngle) / (180.f / 17));
			if (iFrmCount <= iTex || iFrmCount - 1 - iTex - 17 * m_iMaxCount < 0)
				return;
			if (iTex == 17 && iFrmCount>16)
				iTex = 16;
			if (m_vDir.y < -0.9)
				iTex = 0;
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iFrmCount - 1 - iTex - 17 * m_iMaxCount); // 
		}
	}
	else if (UNIT_STATUS::ATTACK == Object()->GetUnitStatus())
	{
		if (L"Corsair" != Object()->GetName())
		{
			if (!m_bAttackOn)
			{
				//m_bBallOn = true;
				m_fAttDT += DT;
			}

			if (m_fAttDT > 0.4f)
			{
				m_bAttackOn = true;
				m_fAttDT = 0.f;
				//m_bBallOn = false;
			}

			if (!m_bAttackOn)
				return;
		}
		else if (L"Corsair" == Object()->GetName())
		{
			if (!m_bAttackOn)
			{
				//m_bBallOn = true;
				m_fAttDT += DT;
			}

			if (m_fAttDT > 0.3f)
			{
				m_bAttackOn = true;
				m_fAttDT = 0.f;
				//m_bBallOn = false;
			}

			if (!m_bAttackOn)
				return;
		}

		if (L"Dragoon" == Object()->GetName() )
		{
			if (!m_bCycle && m_bAttackOn)
			{
				wstring soundname = Object()->GetName();
				soundname += L"Att";
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(soundname);
				if (pSound != nullptr)
					pSound->Play(1);
				Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);
			}
			//if (L"Dragoon" == Object()->GetName() || L"Arbiter" == Object()->GetName())
			//{
			//	size_t iCurFrameSize = Object()->Animator2D()->GetAnimation()->GetFrame().size() - 1;
			//	int iCurfrm = Object()->Animator2D()->GetAnimation()->GetCurFrm();
			//	
			//	if (iCurFrameSize == iCurfrm)
			//		m_bCycle = true;
			//}
		}
		else if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y < 0))
		{
			vRot.y = 0.f;

			if (m_vDir.y < -0.9 && iFrmCount>16)
				iTex = 16;

			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
		}
		else if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y == 0))
		{
			vRot.y = 0;

			if (m_vDir.y > 0)
				iTex = 0;
			else
			{
				if (iFrmCount>16)
					iTex = 16;
			}
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex + 17 * m_iMaxCount);
		}
		else
		{
			vRot.y = XM_PI;
			iTex = (int)((180.f - fAngle) / (180.f / 17));
			if (iFrmCount <= iTex || iFrmCount - 1 - iTex - 17 * m_iMaxCount < 0)
				return;
			if (iTex == 17 && iFrmCount>16)
				iTex = 16;
			if (m_vDir.y < -0.9)
				iTex = 0;
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iFrmCount - 1 - iTex - 17 * m_iMaxCount); // 
		}
	}
	else if (UNIT_STATUS::IDLE == Object()->GetUnitStatus())
	{
		if (L"Dragoon" == Object()->GetName())
		{
			Object()->Animator2D()->PlayAnim(L"DragoonNormal", true);
		}

		else if ((vUp.x*m_vDir.y - m_vDir.x*vUp.y < 0))
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
			Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, 17- 1 - iTex); // 텍스쳐는 1인거 쓰고 180도 회전
		}
		// RESET();
	}

	if (UNIT_STATUS::ATTACK == Object()->GetUnitStatus() && nullptr != Object()->GetTargetObj() && L"Dragoon" != Object()->GetName())
	{
		if (abs(m_iBeforeMaxCount - m_iMaxCount) > 1 && OBJ_TYPE::BUILDING != Object()->GetTargetObj()->GetObjType())
		{
			m_bAttackOn = false;

			CUnitScript* pUnitScript = nullptr;
			for (size_t i = 0; i < Object()->GetTargetObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetTargetObj()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)Object()->GetTargetObj()->Script()[i];
				}
			}

			if (1 > pUnitScript->GetUnitShield())
				pUnitScript->SetDamage(GetGroundAttDamage());
			else
				pUnitScript->SetShield(GetGroundAttDamage());

			int a = GetGroundAttDamage();

			wstring soundname = Object()->GetName();
			soundname += L"Att";

			if (Object()->GetName() == L"DarkTemplar")
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarAtt", L"Sound\\DarkTemplarAtt.wav");
				pSound->Play(1);
			}
			else
			{
				CSound* pSound = CResMgr::GetInst()->Load<CSound>(soundname);
				if (pSound != nullptr)
					pSound->Play(1);
			}
		}
		else if (OBJ_TYPE::BUILDING == Object()->GetTargetObj()->GetObjType())
		{
			CBuildingScript* pBuildingScript = nullptr;
			for (size_t i = 0; i < Object()->GetTargetObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == Object()->GetTargetObj()->Script()[i]->GetScriptType())
				{
					pBuildingScript = (CBuildingScript*)Object()->GetTargetObj()->Script()[i];
				}
			}

			if (1 > pBuildingScript->GetBuildingShield())
				pBuildingScript->SetHp(GetGroundAttDamage());
			else
				pBuildingScript->SetShield(GetGroundAttDamage());

			wstring soundname = Object()->GetName();
			soundname += L"Att";
			CSound* pSound = CResMgr::GetInst()->Load<CSound>(soundname);
			if (pSound != nullptr)
				pSound->Play(1);

			
		}
	}

	++m_iMaxCount;
	m_iBeforeMaxCount = m_iMaxCount;

	//Vec3 v = Object()->Transform()->GetLocalPos();
	//Vec3 v2 = Object()->Transform()->GetLocalAngle();
	Transform()->SetLocalRotate(vRot);
	//Transform()->SetLocalPos(Vec3(v.x,v.y, 110.f));

	m_fAccDT = 0.f;
}

void CUnitScript::AirUnitAnimation()
{
	if (UNIT_STATUS::FROZEN == Object()->GetUnitStatus())
		return;

	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Object()->Transform()->GetLocalPos();

	m_vDir = m_vMarkPos - vPos;

	if (UNIT_STATUS::ATTACK == Object()->GetUnitStatus())
	{
		m_vMarkPos = Object()->GetTargetObj()->Transform()->GetLocalPos();
		m_vDir = m_vMarkPos - Object()->Transform()->GetLocalPos();
	}

	Vec3 vUp = Vec3(0.f, 1.f, 0.f);

	Vec3 vRot = Transform()->GetLocalAngle();

	if (vMousePos.z == 0.f)
		return;

	if (sqrt(m_vDir.x*m_vDir.x + m_vDir.y*m_vDir.y) < 1)
		return;

	m_vDir.Normalize();

	Vec3 vAngle = (Vec3)XMVector3AngleBetweenNormals(vUp, m_vDir); // 사잇각

	float fAngle = (float)(vAngle.z *180.f / 3.14);

	if (fAngle > 180.f)
	{
		fAngle -= 180.f;
	}

	if (L"ArbiterAtt" == Object()->Animator2D()->GetCurAnimName() || L"ArbiterMove" == Object()->Animator2D()->GetCurAnimName())
		Object()->Animator2D()->SetCurAnimName(L"ArbiterNormal");

	if (L"CarrierAtt" == Object()->Animator2D()->GetCurAnimName() || L"CarrierMove" == Object()->Animator2D()->GetCurAnimName())
		Object()->Animator2D()->SetCurAnimName(L"CarrierNormal");

	if(L"CorsairMove" == Object()->Animator2D()->GetCurAnimName())
		Object()->Animator2D()->SetCurAnimName(L"CorsairNormal");

	if (L"ScoutMove" == Object()->Animator2D()->GetCurAnimName())
		Object()->Animator2D()->SetCurAnimName(L"ScoutNormal");

	if (L"ShuttleMove" == Object()->Animator2D()->GetCurAnimName())
		Object()->Animator2D()->SetCurAnimName(L"ShuttleNormal");

	if (L"ObserverMove" == Object()->Animator2D()->GetCurAnimName())
		Object()->Animator2D()->SetCurAnimName(L"ObserverNormal");

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

	m_iCurTex = iTex;

	// 움직이는상태라면
	if (UNIT_STATUS::MOVE == Object()->GetUnitStatus() || UNIT_STATUS::ATTACK == Object()->GetUnitStatus())
	{
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
	}
	else if (UNIT_STATUS::IDLE == Object()->GetUnitStatus()) // 가끔씩 뒤집히는거 있음
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

		if (!m_bFloatUp)
			m_fFloatPos -= DT;
		else
			m_fFloatPos += DT;


		if (m_fFloatPos > 0.4f)
			m_bFloatUp = false;
		if (m_fFloatPos < -0.4f)
			m_bFloatUp = true;

		vPos.y += m_fFloatPos;

		Object()->Transform()->SetLocalPos(Vec3(vPos.x,vPos.y,95.f));

		m_fAccelatorDT = 0.f;
	}

	if (UNIT_STATUS::ATTACK == Object()->GetUnitStatus())
	{
		if (abs(m_iBeforeMaxCount - m_iMaxCount) > 1)
		{
			CUnitScript* pUnitScript = nullptr;
			for (size_t i = 0; i < Object()->GetTargetObj()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == Object()->GetTargetObj()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)Object()->GetTargetObj()->Script()[i];
				}
			}
			if (1 > GetUnitShield())
				pUnitScript->SetHp(GetAirAttDamage());
			else
				pUnitScript->SetShield(GetAirAttDamage());

			wstring soundname = Object()->GetName();
			soundname += L"Att";

			CSound* pSound = CResMgr::GetInst()->Load<CSound>(soundname);
			pSound->Play(1);
		}
	}

	++m_iMaxCount;

	Transform()->SetLocalRotate(vRot);

	m_fAccDT = 0.f;
}

void CUnitScript::SetBtnUI()
{
	wstring ObjName = Object()->GetName();

	if ((L"Probe" == ObjName))
	{
		if (BUTTON_CHAPTER::PROBE_BASE != CUIMgr::GetInst()->GetButtonChapter() && BUTTON_CHAPTER::PROBE_LBUILD != CUIMgr::GetInst()->GetButtonChapter()
			&& BUTTON_CHAPTER::PROBE_HBUILD != CUIMgr::GetInst()->GetButtonChapter())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::PROBE_BASE);
			CUnitMgr::GetInst()->SetButtonOwner(Object());
		}
	}
	else if ((L"Zealot" == ObjName || L"Dragoon" == ObjName || L"DarkTemplar" == ObjName || L"Reaver" == ObjName
		|| L"Corsair" == ObjName || L"Scout" == ObjName || L"Carrier" == ObjName || L"Arbiter" == ObjName))
	{
		CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::ATT_UNIT);
		CUnitMgr::GetInst()->SetButtonOwner(Object());
	}
	else
	{
		CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::NATT_UNIT);
		CUnitMgr::GetInst()->SetButtonOwner(Object());
	}
}

void CUnitScript::Move()
{	
	if (UNIT_STATUS::FROZEN == Object()->GetUnitStatus())
		return;

	CWell512 random;
	int iColor = random.GetValue(0, 3);

	CScene* pCurScene = (CScene*)CSceneMgr::GetInst()->GetCurrentScene();

	Vec3 vPos = Object()->Transform()->GetLocalPos();

	if (UNIT_STATUS::ATTACK != Object()->GetUnitStatus())
	{
		m_fAccelator = 25.f;

		float fSpeed = m_fAccelator * m_fAccelatorDT;

		if (GetUnitSpeed()*1.4 > fSpeed)
			m_fAccelatorDT += DT;

		vPos.x += DT * fSpeed*1.4f *m_vDir.x; // 속도가 될 것이다.
		vPos.y += DT * fSpeed*1.4f *m_vDir.y;
	}

	if (sqrt((m_vMarkPos.x - vPos.x)*(m_vMarkPos.x - vPos.x) + (m_vMarkPos.y - vPos.y)*(m_vMarkPos.y - vPos.y)) < 7)
	{
		Object()->SetUnitStatus(UNIT_STATUS::IDLE);
		return;
	}
	Object()->Transform()->SetLocalPos(Vec3(vPos.x,vPos.y,95.f));
}

void CUnitScript::BuildStructure()
{
	CPrefab* pGameObject = CBuildingMgr::GetInst()->GetClickedPrefab();
	CGameObject* pOrgnObj = pGameObject->GetOriginObj();
	Vec3 vOrgScale = pOrgnObj->Transform()->GetLocalScale();
	Vec3 vColScale = pOrgnObj->Collider()->GetOffsetScale();
	Vec3 vRealScale = vOrgScale * vColScale;

	Vec3 vObjectPos = Object()->Transform()->GetLocalPos();
	float fDist = sqrt((m_vStructurePos.x - vObjectPos.x)*(m_vStructurePos.x - vObjectPos.x) + (m_vStructurePos.y - vObjectPos.y)*(m_vStructurePos.y - vObjectPos.y));
	float fScale = sqrt((vRealScale.x*vRealScale.x) + (vRealScale.y*vRealScale.y));
	if (fDist < fScale / 2)
	{
		CPrefab* pGameObject = CBuildingMgr::GetInst()->GetClickedPrefab();
		wstring strStructureName = CBuildingMgr::GetInst()->GetStructureName();

		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
		int iIdx = pScene->GetLayer(strStructureName)->GetIdx();
		if (nullptr != pGameObject)
		{
			// 103
			Instantiate(pGameObject, L"Ally", Vec3(m_vStructurePos.x, m_vStructurePos.y, 100.f), Vec3(0.f, 0.f, 0.f));

			CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"BuildStart");
			pSound->Play(1);
		}

		//
		CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
		CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

		int iTileSize = pGridObject->Grid()->GetTileSize();
		Vec3 vStructurePos = m_vStructurePos + pGridObject->Grid()->GetTransformed();
		Vec2 vIdx = Vec2((int)((vStructurePos.x + iTileSize / 2) / iTileSize), (int)((vStructurePos.y + iTileSize / 2) / iTileSize));

		Vec2 vTileNum = pGridObject->Grid()->GetTileNum();

		if (vIdx.x >= vTileNum.x || vIdx.x < 0 || vIdx.y >= vTileNum.y || vIdx.y < 0)
			return;

		CGameObject* pClickedTile = pGridObject->Grid()->GetClickedTile(Vec2(vIdx.x, vIdx.y));
		CGameObject* pOrgObject = pGameObject->GetOriginObj();

		Vec3 vPrefabScale = pOrgObject->Transform()->GetLocalScale();

		Vec2 iRestOfSize = {};
		iRestOfSize.x = (int)vPrefabScale.x % iTileSize;
		iRestOfSize.y = (int)vPrefabScale.y % iTileSize;

		int iIdxSizeX = vPrefabScale.x / iTileSize;
		int iIdxSizeY = vPrefabScale.y / iTileSize;

		map<wstring, CRes*> maap = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);
		map<wstring, CRes*>::iterator iter = maap.find(L"Tile_01.png");
		CTexture* pTex = (CTexture*)iter->second;

		int iRestX = 0;
		int iRestY = 0;
		if (iRestOfSize.x > 0.5f)
		{
			iRestX = 1;
		}
		if (iRestOfSize.y > 0.5f)
		{
			iRestY = 1;
		}
		for (int i = vIdx.y - iIdxSizeY / 2 + iRestY; i < vIdx.y + iIdxSizeY / 2 + iRestY; ++i)
		{
			for (int j = vIdx.x - iIdxSizeX / 2 + iRestX; j < vIdx.x + iIdxSizeX / 2 + iRestX+1; ++j)
			{
				pGridObject->Grid()->SetTileIdx(Vec2(j, i));

				CGameObject* pNewObject = new CGameObject;
				pNewObject->SetName(L"ColTile");
				pNewObject->AddComponent(new CCollider);
				pClickedTile = pGridObject->Grid()->GetClickedTile(Vec2(j, i));
				pGridObject->Grid()->SetColOccupied(pClickedTile, true);

				pNewObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
				pNewObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

				CSceneMgr::GetInst()->AddGameObject(L"ColTile", pNewObject);

				pNewObject->AddComponent(new CMeshRender);

				Vec3 vClickedTilePos = pClickedTile->Transform()->GetLocalPos();


				pNewObject->Transform()->SetLocalPos(Vec3(vClickedTilePos.x,
					vClickedTilePos.y, 110.f));

				pNewObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
				pNewObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

				pNewObject->MeshRender()->SetTexture(pTex);
				pNewObject->MeshRender()->SetRender(false);

				CMaterial* p = pNewObject->MeshRender()->GetCloneMaterial();

				Vec2 vSize = Vec2(int(pTex->GetWidth() / iTileSize), (int)(pTex->GetHeight() / iTileSize));

				Vec2 vInterpolationSize = Vec2(vSize.x*iTileSize, vSize.y*iTileSize);

				int i = 1;
				p->SetData(SHADER_PARAM::TEX_0, pTex);
				p->SetData(SHADER_PARAM::INT_0, &i);


				pNewObject->Transform()->SetLocalScale(Vec3(vInterpolationSize.x, vInterpolationSize.y, g_depthz));
			}
			//CTileMgr::GetInst()->SetMinX(j);
			//CTileMgr::GetInst()->SetMaxX(j);
			//CTileMgr::GetInst()->SetMinY(j);
			//CTileMgr::GetInst()->SetMaxY(j);
		}
		//

		m_vStructurePos = Vec3(0.f, 0.f, 0.f);
		CBuildingMgr::GetInst()->SetClickedPrefab(nullptr);
		CBuildingMgr::GetInst()->SetStructureName(L"");

		Object()->SetTargetted(true);

		Reset();
		Object()->SetUnitStatus(UNIT_STATUS::IDLE);
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
	if (KEYTAB(KEY_TYPE::KEY_LBTN) && OBJ_TYPE::UI != pMouseScript->GetTargetObj()->GetObjType())
	{
		m_vStructurePos = CKeyMgr::GetInst()->GetMousePos();
		m_vStructurePos.z = 103.f;
		Reset();
		AstarKey();
	}
}

void CUnitScript::MakeAlly()
{// 반경 생성
	if (!m_bAlly)
	{
		CGameObject* pAlly = new CGameObject;
		pAlly->SetName(L"Ally");
		pAlly->AddComponent(new CMeshRender);

		pAlly->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pAlly->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly5");

		Vec3 vTargetObjScale = Object()->Transform()->GetLocalScale();

		pAlly->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);

		pAlly->Transform()->SetLocalScale(Object()->Transform()->GetLocalScale()*Object()->Collider()->GetOffsetScale());
		pAlly->Transform()->SetLocalPos(Object()->Transform()->GetLocalPos());

		Object()->AddChild(pAlly);

		m_bAlly = true;
	}
}

void CUnitScript::MoveByAstar()
{
	// 콜라이더 충돌시 반대 벡터로!
	if (Object()->GetTargetObj() != nullptr)
	{
		Reset();
		return;
	}

	if (m_bFrozen)
		return;

	Vec3 vObjPos = Object()->Transform()->GetLocalPos();

	Vec3 vPathPos;

	vPathPos = m_vecNodePos.front() - vObjPos;

	m_vDir = vPathPos; // 팝할때마다 이전노드와 현재 노드의 차이로 하는게 좋을거같다.

	Object()->SetUnitStatus(UNIT_STATUS::MOVE);

	if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
		m_iMaxCount = 0;

	GroundUnitAnimation(); // 0~16이 가만히 있는 상태
	m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();

	vPathPos.Normalize();
	vObjPos.x += DT * GetUnitSpeed()*1.4f * vPathPos.x; // 속도가 될 것이다.
	vObjPos.y += DT * GetUnitSpeed()*1.4f * vPathPos.y;

	if (sqrt((m_vecNodePos.front().x - vObjPos.x)*(m_vecNodePos.front().x - vObjPos.x)
		+ (m_vecNodePos.front().y - vObjPos.y)*(m_vecNodePos.front().y - vObjPos.y)) < 10)
	{
		m_vecNodePos.pop_front();
		if (m_vecNodePos.empty())
		{
			Reset();
			Object()->SetUnitStatus(UNIT_STATUS::IDLE);
		}
	}
	Object()->Transform()->SetLocalPos(Vec3(vObjPos.x,vObjPos.y,100.f));
}

void CUnitScript::InputKey()
{
	if (KEYTAB(KEY_TYPE::KEY_S))
	{
		Reset();
		Object()->SetTarget(false);
		Object()->SetUnitStatus(UNIT_STATUS::IDLE);
		// m_bStartToFind = true;
	}
	if (KEYTAB(KEY_TYPE::KEY_H))
	{
		Reset();
		Object()->SetTarget(false);
		Object()->SetUnitStatus(UNIT_STATUS::IDLE);
		// m_bStartToFind = true;
	}
	if (KEYTAB(KEY_TYPE::KEY_A))
	{
		m_bReadyToAtt = true;
	}

	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		m_bStartToFind = false;
		Object()->SetTarget(false);
		Object()->SetUnitStatus(UNIT_STATUS::MOVE);

		wstring name = Object()->GetName();
		name += L"Move";

		Object()->Animator2D()->SetCurAnimName(name);
	}

	if (KEYTAB(KEY_TYPE::KEY_LBTN) && m_bReadyToAtt)
	{
		m_bReadyToAtt = false;
		m_bStartToFind = true;

		if (OBJ_TYPE::GROUNDUNIT == Object()->GetObjType())
		{
			m_bWait = false;
			wstring strAnimName = Object()->GetName();
			strAnimName += L"Move";
			Object()->Animator2D()->SetCurAnimName(strAnimName);
			Reset();
			AstarKey();
		}
		else if (OBJ_TYPE::AIRUNIT == Object()->GetObjType())
		{
			m_vMarkPos = CKeyMgr::GetInst()->GetMousePos();
		}
	}
}

void CUnitScript::AstarKey()
{
	if (KEYTAB(KEY_TYPE::KEY_RBTN) || m_bStartToFind) // KEYTAB(KEY_TYPE::KEY_RBTN)|| KEYTAB(KEY_TYPE::KEY_LBTN)&& nullptr != CBuildingMgr::GetInst()->GetClickedPrefab()
	{
		CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
		//vector<CGameObject*> vecArmy = pCurScene->GetLayer(L"Ally")->GetObjVec();

		vector<CGameObject*> vecArmy = pCurScene->GetCurTargetObjVec();
		vector<CGameObject*> vecGroundArmy;
		for (size_t i = 0; i < vecArmy.size(); ++i)
		{
			if (vecArmy[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT)
			{
				vecGroundArmy.push_back(vecArmy[i]);
			}
		}

		Vec3 vAver;

		for (size_t i = 0; i < vecGroundArmy.size(); ++i)
		{
			vAver += vecGroundArmy[i]->Transform()->GetLocalPos();
		}

		if (vecGroundArmy.size() == 0)
			return;

		vAver /= vecGroundArmy.size();

		Vec3 vGab = vAver - Object()->Transform()->GetLocalPos(); // 평균점으로부터 각자의 거리

		Vec3 vAverToDest = CKeyMgr::GetInst()->GetMousePos() - vAver; // 평균점으로부터 종점의 거리

		sort(vecGroundArmy.begin(), vecGroundArmy.end(), [](CGameObject* _pObj1, CGameObject* _pObj2)
		{
			CScene* pCurSceneL = CSceneMgr::GetInst()->GetCurrentScene();
			vector<CGameObject*> vecArmyL = pCurSceneL->GetLayer(L"Ally")->GetObjVec();
			vector<CGameObject*> vecGroundArmyL;
			for (size_t i = 0; i < vecArmyL.size(); ++i)
			{
				if (vecArmyL[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT)
				{
					vecGroundArmyL.push_back(vecArmyL[i]);
				}
			}
			Vec3 vAverL;

			for (size_t i = 0; i < vecGroundArmyL.size(); ++i)
			{
				vAverL += vecGroundArmyL[i]->Transform()->GetLocalPos();
			}
			vAverL /= vecGroundArmyL.size();

			return sqrt((_pObj1->Transform()->GetLocalPos().x - vAverL.x)*(_pObj1->Transform()->GetLocalPos().x - vAverL.x)
				+ (_pObj1->Transform()->GetLocalPos().y - vAverL.y)*(_pObj1->Transform()->GetLocalPos().y - vAverL.y))
				< sqrt((_pObj2->Transform()->GetLocalPos().x - vAverL.x)*(_pObj2->Transform()->GetLocalPos().x - vAverL.x)
					+ (_pObj2->Transform()->GetLocalPos().y - vAverL.y)*(_pObj2->Transform()->GetLocalPos().y - vAverL.y));
		});

		CGameObject* pNearObj = vecGroundArmy[0];// 평균점으로부터 가장 가까운 놈

		Vec3 vCenterHalfScale = vecGroundArmy[0]->Transform()->GetLocalScale()*vecGroundArmy[0]->Collider()->GetOffsetScale() *0.5f;
		Vec3 vMyHalfScale = Object()->Transform()->GetLocalScale()*Object()->Collider()->GetOffsetScale()*0.5f;
		Vec3 vScaleGab = vCenterHalfScale + vMyHalfScale;

		Vec3 vObjToCenterDist = pNearObj->Transform()->GetLocalPos() - Object()->Transform()->GetLocalPos();
		vObjToCenterDist = Vec3(abs(vObjToCenterDist.x), abs(vObjToCenterDist.y), 0.f);

		vObjToCenterDist -= vScaleGab;

		Vec3 vDivide = vObjToCenterDist / (vMyHalfScale*2);

		vDivide.x -= 1;
		vDivide.y -= 1;

		Vec3 vDirObjToAver =  vecGroundArmy[0]->Transform()->GetLocalPos() - Object()->Transform()->GetLocalPos();
		vDirObjToAver.Normalize();

		m_bWait = false;

		CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid"); // 어차피 그리드 컴포넌트는 하나니까
		CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

		int iTileSize = pGridObject->Grid()->GetTileSize();
		Vec3 vDestPos = Object()->Transform()->GetLocalPos() + vAverToDest+ vDivide * vMyHalfScale * 2 *vDirObjToAver + pGridObject->Grid()->GetTransformed();
		Vec2 vIdx = Vec2((int)((vDestPos.x + iTileSize / 2) / iTileSize), (int)((vDestPos.y + iTileSize / 2) / iTileSize));

		//// 인덱스 겹치면 idivide -= 1 하고 돌린다.
		//Vec3 vDestPos{};
		//Vec2 vIdx{};

		//while (1)
		//{
		//	bool bSame = false;

		//	vDivide.x -= 1;
		//	vDivide.y -= 1;

		//	vDestPos = Object()->Transform()->GetLocalPos() + vAverToDest + vDivide * vMyHalfScale * 2 * vDirObjToAver + pGridObject->Grid()->GetTransformed();
		//	vIdx = Vec2((int)((vDestPos.x + iTileSize / 2) / iTileSize), (int)((vDestPos.y + iTileSize / 2) / iTileSize));

		//	vector<Vec2> vecIdx = CUnitMgr::GetInst()->GetIdxVec();
		//	for (size_t i = 0; i < vecIdx.size(); ++i)
		//	{
		//		if (vIdx == vecIdx[i])
		//		{
		//			bSame = true;
		//		}
		//	}

		//	if (!bSame)
		//	{
		//		CUnitMgr::GetInst()->AddIdx(vIdx);
		//		break;
		//	}
		//}

		Vec3 vDist = vAverToDest + vDivide * vMyHalfScale * 2 * vDirObjToAver;

		vector<Vec2>& vecTile = pGridObject->Grid()->GetTileIdx();

		// 충돌 타일에 찍었으면 그냥 리턴
		for (size_t i = 0; i < vecTile.size(); ++i) // return 에서 continue 로 바꿨는데 문제 생기는지 확인해야함
		{
			if ((vIdx.x) == vecTile[i].x && (vIdx.y) == vecTile[i].y )
				return;
		}

		m_iStartX = (int)vIdx.x - (int)(vDist.x / iTileSize);
		m_iStartY = (int)vIdx.y - (int)(vDist.y / iTileSize);
		m_iEndX = vIdx.x;
		m_iEndY = vIdx.y;

		Astar();
	}

	if (KEYTAB(KEY_TYPE::KEY_LBTN)&& nullptr != CBuildingMgr::GetInst()->GetClickedPrefab())
	{
		CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
		CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

		int iTileSize = pGridObject->Grid()->GetTileSize();
		Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos() + pGridObject->Grid()->GetTransformed();
		Vec2 vIdx = Vec2((int)((vMousePos.x + iTileSize / 2) / iTileSize), (int)((vMousePos.y + iTileSize / 2) / iTileSize));

		Vec3 vDist = CKeyMgr::GetInst()->GetMousePos() - Transform()->GetLocalPos();

		m_iStartX = (int)vIdx.x - (int)(vDist.x / iTileSize);
		m_iStartY = (int)vIdx.y - (int)(vDist.y / iTileSize);
		m_iEndX = (int)vIdx.x;
		m_iEndY = (int)vIdx.y;

		Astar();
	}

	// 애들끼리 충돌했다면 m_iEndX 하고 m_iEndY 는 그대로 가져오고 startx,y 만 현재 위치로 
	//{
	//	CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
	//	CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

	//	int iTileSize = pGridObject->Grid()->GetTileSize();
	//	Vec3 vObjPos = Object()->Transform()->GetLocalPos() + pGridObject->Grid()->GetTransformed();
	//	Vec2 vIdx = Vec2((int)((vObjPos.x + iTileSize / 2) / iTileSize), (int)((vObjPos.y + iTileSize / 2) / iTileSize));

	//  처음 찍었을때 마우스 좌표를 사용해야 한다.
	//	Vec3 vDist = CKeyMgr::GetInst()->GetMousePos() - Transform()->GetLocalPos();

	//	m_iStartX = (int)vIdx.x - (int)(vDist.x / iTileSize);
	//	m_iStartY = (int)vIdx.y - (int)(vDist.y / iTileSize);
	//	m_iEndX = (int)vIdx.x;
	//	m_iEndY = (int)vIdx.y;

	//	Astar();
	//}
}

void CUnitScript::Astar()
{
	InitNode();
	FindPath();
	MoveToDest();
}

void CUnitScript::CalCost(int _iX, int _iY, int _iOrgX, int _iOrgY)
{	
	// 이전 노드까지의 비용, + 1칸 거리 == 현재 노드까지 오는 비용
	if (m_arrNode[_iY][_iX].bOpened)
	{
		//int iFromDist = (int)(10*sqrt((_iOrgY - _iY)*(_iOrgY - _iY) +(_iOrgX - _iX)*(_iOrgX - _iX)));
		int iFromDist = (int)(10 * (sqrt((_iOrgY - _iY)*(_iOrgY - _iY) + (_iOrgX - _iX)*(_iOrgX - _iX))));
		// 이번에 추가되는 루트가 더 좋은 루트였다.
		if (m_arrNode[_iY][_iX].fFrom >= m_arrNode[_iOrgY][_iOrgX].fFrom + iFromDist)
		{
			m_arrNode[_iY][_iX].fFrom = m_arrNode[_iOrgY][_iOrgX].fFrom + iFromDist;
			m_arrNode[_iY][_iX].iParentIdxX = _iOrgX;
			m_arrNode[_iY][_iX].iParentIdxY = _iOrgY;
		}
	}
	else // openlist 에 처음 추가되는 상황
	{
		//int iFromDist = (int)(10*sqrt((_iOrgY - _iY)*(_iOrgY - _iY) +(_iOrgX - _iX)*(_iOrgX - _iX)));
		int iFromDist = (int)(10 * (sqrt((_iOrgY - _iY)*(_iOrgY - _iY) + (_iOrgX - _iX)*(_iOrgX - _iX))));

		m_arrNode[_iY][_iX].fFrom = m_arrNode[_iOrgY][_iOrgX].fFrom + iFromDist;
		m_arrNode[_iY][_iX].fDest = abs(m_iEndX - m_arrNode[_iY][_iX].iCurIdxX) + abs(m_iEndY - m_arrNode[_iY][_iX].iCurIdxY);
		m_arrNode[_iY][_iX].fFinal = m_arrNode[_iY][_iX].fFrom + m_arrNode[_iY][_iX].fDest;

		m_arrNode[_iY][_iX].iParentIdxX = _iOrgX;
		m_arrNode[_iY][_iX].iParentIdxY = _iOrgY;
	}
}

void CUnitScript::InitNode()
{
	// abs(x 거리 /32) // abs(y 거리 /32)
	int iFirstY = 0, iSecondY = 0, iFirstX = 0, iSecondX = 0;

	if (m_iStartY > m_iEndY){iFirstY = m_iEndY;	iSecondY = m_iStartY;}
	else{iFirstY = m_iStartY;iSecondY = m_iEndY;}
	if (m_iStartX > m_iEndX){iFirstX = m_iEndX;	iSecondX = m_iStartX;}
	else{iFirstX = m_iStartX;iSecondX = m_iEndX;}

	for (int i = 0; i <= 99; ++i)
	{
		for (int j = 0; j <= 99; ++j)
		{
			m_arrNode[i][j].iCurIdxX = j;
			m_arrNode[i][j].iCurIdxY = i;
		}
	}

	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	CLayer* pColTileLayer = pScene->GetLayer(L"ColTile");
	vector<CGameObject*> pColTileObject = pColTileLayer->GetObjVec();

	CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
	CGameObject* pGridObject = pGridLayer->GetObjVec()[0];
	vector<Vec2>& vecTile = pGridObject->Grid()->GetTileIdx();

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		int a = (int)vecTile[i].y;
		int b = (int)vecTile[i].x;
		m_arrNode[a][b].bObstacle = true;
	}

	vector<CGameObject*> vecMyUnit = pScene->GetLayer(L"Ally")->GetObjVec();
	vector<CGameObject*> vecOppoUnit = pScene->GetLayer(L"Opponent")->GetObjVec();

	int iTileSize = pGridObject->Grid()->GetTileSize();

	Vec2 vTileNum = pGridObject->Grid()->GetTileNum();


	// 유닛들이 있는 위치를 그리드 좌표로 
	//for (size_t i = 0; i < vecMyUnit.size(); ++i)
	//{
	//	Vec3 vMyUnitPos = vecMyUnit[i]->Transform()->GetLocalPos() + pGridObject->Grid()->GetTransformed();
	//	Vec2 vIdx = Vec2((int)((vMyUnitPos.x + iTileSize / 2) / iTileSize), (int)((vMyUnitPos.y + iTileSize / 2) / iTileSize));

	//	if (vIdx.x >= vTileNum.x || vIdx.x < 0 || vIdx.y >= vTileNum.y || vIdx.y < 0)
	//		return;

	//	int a = vIdx.x;
	//	int b = vIdx.y;

	//	m_arrNode[a][b].bObstacle = true;
	//}

	//for (size_t i = 0; i < vecOppoUnit.size(); ++i)
	//{
	//	Vec3 vOppoUnitPos = vecOppoUnit[i]->Transform()->GetLocalPos() + pGridObject->Grid()->GetTransformed();
	//	Vec2 vIdx = Vec2((int)((vOppoUnitPos.x + iTileSize / 2) / iTileSize), (int)((vOppoUnitPos.y + iTileSize / 2) / iTileSize));

	//	if (vIdx.x >= vTileNum.x || vIdx.x < 0 || vIdx.y >= vTileNum.y || vIdx.y < 0)
	//		return;

	//	int a = vIdx.x;
	//	int b = vIdx.y;

	//	m_arrNode[a][b].bObstacle = true;
	//}


}

void CUnitScript::FindPath()
{
	size_t a = m_openlist.size();
	
	while(!m_openlist.empty())
	{
		m_openlist.pop();
	}

	m_openlist.push(&m_arrNode[m_iStartY][m_iStartX]);
	m_arrNode[m_iStartY][m_iStartX].bOpened = false;

	tNode* node = {};
	while (1)
	{
		if (0 == m_openlist.size())
			return;

		node = m_openlist.top();
		m_openlist.pop();
		m_arrNode[node->iCurIdxY][node->iCurIdxX].bClosed = true;

		if (node->iCurIdxX == m_iEndX && node->iCurIdxY == m_iEndY)
		{
			break;
		}

		// 이부분은 고쳐야 한칸 왼쪽이 되나
		AddOpenlist(node->iCurIdxX, node->iCurIdxY + 1, node->iCurIdxX, node->iCurIdxY);
		AddOpenlist(node->iCurIdxX + 1, node->iCurIdxY + 1, node->iCurIdxX, node->iCurIdxY);
		AddOpenlist(node->iCurIdxX + 1, node->iCurIdxY, node->iCurIdxX, node->iCurIdxY);
		AddOpenlist(node->iCurIdxX + 1, node->iCurIdxY - 1, node->iCurIdxX, node->iCurIdxY);
		AddOpenlist(node->iCurIdxX, node->iCurIdxY - 1, node->iCurIdxX, node->iCurIdxY);
		AddOpenlist(node->iCurIdxX - 1, node->iCurIdxY - 1, node->iCurIdxX, node->iCurIdxY);
		AddOpenlist(node->iCurIdxX - 1, node->iCurIdxY, node->iCurIdxX, node->iCurIdxY);
		AddOpenlist(node->iCurIdxX - 1, node->iCurIdxY + 1, node->iCurIdxX, node->iCurIdxY);
	}

	m_listPath.push_front(&m_arrNode[node->iCurIdxY][node->iCurIdxX]);

	tNode* pNode = nullptr;
	while (true)
	{
		pNode = m_listPath.front();
		if (pNode->iCurIdxX == m_iStartX && pNode->iCurIdxY == m_iStartY)
			break;

		m_listPath.push_front(&m_arrNode[m_listPath.front()->iParentIdxY][m_listPath.front()->iParentIdxX]);
	}
}

void CUnitScript::AddOpenlist(int _iX, int _iY, int _iOrgX, int _iOrgY)
{
	// 여기서의 조건이 필요함
	if (_iX < 0 || 100 < _iX || _iY < 0 || 100 < _iY
		|| m_arrNode[_iY][_iX].bClosed || m_arrNode[_iY][_iX].bObstacle)
		return;

	CalCost(_iX, _iY, _iOrgX, _iOrgY);

	if (false == m_arrNode[_iY][_iX].bOpened)
	{
		m_openlist.push(&m_arrNode[_iY][_iX]);
		m_arrNode[_iY][_iX].bOpened = true;
	}
}

void CUnitScript::MoveToDest()
{
	Vec3 vObjPos = Object()->Transform()->GetLocalPos();

	int iFirstY = 0, iSecondY = 0, iFirstX = 0, iSecondX = 0;

	if (m_iStartY > m_iEndY) { iFirstY = m_iEndY;	iSecondY = m_iStartY; }
	else { iFirstY = m_iStartY; iSecondY = m_iEndY; }
	if (m_iStartX > m_iEndX) { iFirstX = m_iEndX;	iSecondX = m_iStartX; }
	else { iFirstX = m_iStartX; iSecondX = m_iEndX; }

	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	CLayer* pColTileLayer = pScene->GetLayer(L"ColTile");
	vector<CGameObject*> pColTileObject = pColTileLayer->GetObjVec();
	int iColTileNum = pColTileObject.size();

	while (1)
	{
		if (0 == m_listPath.size())
			break;

		//if (iSecondY + iColTileNum > 100 || iSecondX + iColTileNum > 100)
		//{
		//	if(iSecondY + iColTileNum > 100)
		//		iColTileNum = 99 - iSecondY;
		//	if(iSecondX + iColTileNum > 100)
		//		iColTileNum = 99 - iSecondX;
		//}
		// 0 부터 99 하면 그냥 해결되긴 할듯
		for (int i = 1; i <= 99; ++i)
		{
			for (int j = 1; j <= 99; ++j)
			{
				if (i == m_listPath.front()->iParentIdxY && j == m_listPath.front()->iParentIdxX)
				{
					int a = m_listPath.front()->iParentIdxY - m_listPath.front()->iCurIdxY;
					int b = m_listPath.front()->iParentIdxX - m_listPath.front()->iCurIdxX;

					m_vAccPos.x -= b * 32;
					m_vAccPos.y -= a * 32;

					int iObjX = (int)vObjPos.x;
					int iObjY = (int)vObjPos.y;

					Vec3 vObj = Vec3((int)iObjX, (int)iObjY, (int)vObjPos.z);

					m_vLaterPos = vObj + m_vAccPos;

					m_vecNodePos.push_back(m_vLaterPos);

					// 처음 노드에서 다음 노드 거리 구한다음 빼서 방향벡터 구하고 그 방향벡터로 속력만큼 곱해주면 됨
				}
			}
		}
		m_listPath.pop_front();
	}
}

void CUnitScript::Reset()
{
	int iFirstY = 0, iSecondY = 0, iFirstX = 0, iSecondX = 0;

	if (m_iStartY > m_iEndY) { iFirstY = m_iEndY;	iSecondY = m_iStartY; }
	else { iFirstY = m_iStartY; iSecondY = m_iEndY; }
	if (m_iStartX > m_iEndX) { iFirstX = m_iEndX;	iSecondX = m_iStartX; }
	else { iFirstX = m_iStartX; iSecondX = m_iEndX; }

	while (!m_vecNodePos.empty())
	{
		m_vecNodePos.pop_front();
	}

	if (m_vecNodePos.empty())
	{
		// 초기화 진행
		while (1)
		{
			if (m_openlist.size() == 0){break;}
			m_openlist.pop();
		}

		for (int i = 0; i < 100; ++i)
		{
			for (int j = 0; j < 100; ++j)
			{
				m_arrNode[j][i].bClosed = false;
				m_arrNode[j][i].bOpened = false;
				m_arrNode[j][i].bObstacle = false;

				m_arrNode[j][i].iCurIdxX = 0;
				m_arrNode[j][i].iCurIdxY = 0;

				m_arrNode[j][i].iParentIdxX = 0;
				m_arrNode[j][i].iParentIdxY = 0;

				m_arrNode[j][i].fFrom = 0;
				m_arrNode[j][i].fDest = 0;
				m_arrNode[j][i].fFinal = 0;
			}
		}

		m_iStartX = 0;
		m_iStartY = 0;

		m_iEndX = 0;
		m_iEndY = 0;

		m_vLaterPos = Vec3(0.f, 0.f, 0.f);
		m_vAccPos = Vec3(0.f, 0.f, 0.f);

		m_vBeforeNodePos = Vec3(0.f, 0.f, 0.f);
		m_bStart = false;
	}
}

void CUnitScript::FindOpponent() // 매니져에서 관리해주는게 맞을듯
{
	if (nullptr != Object()->GetTargetObj())
		return;

	CScene* pScene =  CSceneMgr::GetInst()->GetCurrentScene();

	Vec3 vPos = Object()->Transform()->GetLocalPos();
	Vec3 vScale = Object()->Transform()->GetLocalScale() * Object()->Collider()->GetOffsetScale();

	float fDist1 = 0.f;
	float fDist2 = 0.f;
	int iIdx = -1;

	if (Object()->GetLayerIdx() == pScene->GetLayer(L"Opponent")->GetIdx())
	{
		vector<CGameObject*> vecAlly = pScene->GetLayer(L"Ally")->GetObjVec();
		// ally와 비교
		if (vecAlly.size() == 0)
			return;

		for (size_t i = 0; i < vecAlly.size(); ++i)
		{
			if (vecAlly[i]->GetObjType() == OBJ_TYPE::NONE)
				continue;

			if (UNIT_STATUS::DIE == vecAlly[i]->GetUnitStatus())
				return;

			Vec3 vAllyPos = vecAlly[i]->Transform()->GetLocalPos();
			Vec3 vAllyScale = vecAlly[i]->Transform()->GetLocalScale()* vecAlly[i]->Collider()->GetOffsetScale();

			float fDistPos = sqrt((vPos.x - vAllyPos.x)*(vPos.x - vAllyPos.x) + (vPos.y - vAllyPos.y)*(vPos.y - vAllyPos.y));
			float fDistScale = sqrt((vScale.x * vScale.x) + (vScale.y - vScale.y)) + sqrt((vAllyScale.x * vAllyScale.x) + (vAllyScale.y* vAllyScale.y));

			if (m_iRange == 1)
				m_iRange = 1;

			if (fDistPos < fDistScale + 4 * 32.f)
			{
				if (vecAlly[i]->GetObjType() == OBJ_TYPE::AIRUNIT || vecAlly[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT)
				{
					if (UNIT_STATUS::FROZEN == vecAlly[i]->GetUnitStatus())
						continue;
				}

				fDist1 = fDistPos;

				if ((vecAlly[i]->GetObjType() == OBJ_TYPE::AIRUNIT || vecAlly[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT))
				{
					if (Object()->GetTargetObj() == nullptr && vecAlly[i]->GetUnitStatus() != UNIT_STATUS::DIE)
					{
						if (Object()->GetName() == L"Corsair")
						{
							if (vecAlly[i]->GetObjType() == OBJ_TYPE::AIRUNIT)
							{
								if (0.f == fDist2)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
								else if (fDist2 > fDist1)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
							}
								//Object()->SetTarget(vecAlly[i]);
						}
						else if (Object()->GetName() == L"Zealot" || Object()->GetName() == L"DarkTemplar")
						{
							if (vecAlly[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT || vecAlly[i]->GetObjType() == OBJ_TYPE::BUILDING)
							{
								if (0.f == fDist2)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
								else if (fDist2 > fDist1)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
							}
								//Object()->SetTarget(vecAlly[i]);
						}
						else
						{
							if (0.f == fDist2)
							{
								fDist2 = fDist1;
								iIdx = i;
							}
							else if (fDist2 > fDist1)
							{
								fDist2 = fDist1;
								iIdx = i;
							}
						}
					}
				}
				else if (vecAlly[i]->GetObjType() == OBJ_TYPE::BUILDING)
				{
					if (Object()->GetName() != L"Corsair")
					{

						CBuildingScript* pBuildingScript = nullptr;
						for (size_t j = 0; j < vecAlly[i]->Script().size(); ++j)
						{
							if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == vecAlly[i]->Script()[j]->GetScriptType())
							{
								pBuildingScript = (CBuildingScript*)vecAlly[i]->Script()[j];
							}
						}
						if (pBuildingScript->GetExplosion())
							continue;
						else
						{
							if (0.f == fDist2)
							{
								fDist2 = fDist1;
								iIdx = i;
							}
							else if (fDist2 > fDist1)
							{
								fDist2 = fDist1;
								iIdx = i;					
							}
						}
					}
				}
				
			}
		}

		if (-1 == iIdx)
			return;
		else
			Object()->SetTarget(vecAlly[iIdx]);
	}
	else if (Object()->GetLayerIdx() == pScene->GetLayer(L"Ally")->GetIdx())
	{
		vector<CGameObject*> vecOpponent = pScene->GetLayer(L"Opponent")->GetObjVec();

		if (vecOpponent.size() == 0)
			return;

		for (size_t i = 0; i < vecOpponent.size(); ++i)
		{
			if (vecOpponent[i]->GetObjType() == OBJ_TYPE::NONE)
				continue;

			if (UNIT_STATUS::DIE == vecOpponent[i]->GetUnitStatus())
				return;

			Vec3 vOpponentPos = vecOpponent[i]->Transform()->GetLocalPos();
			Vec3 vOpponentScale = vecOpponent[i]->Transform()->GetLocalScale()* vecOpponent[i]->Collider()->GetOffsetScale();

			float fDistPos = sqrt((vPos.x - vOpponentPos.x)*(vPos.x - vOpponentPos.x) + (vPos.y - vOpponentPos.y)*(vPos.y - vOpponentPos.y));
			float fDistScale = sqrt((vScale.x * vScale.x) + (vScale.y - vScale.y)) + sqrt((vOpponentScale.x * vOpponentScale.x) + (vOpponentScale.y* vOpponentScale.y));

			if (m_iRange == 1)
				m_iRange = 1;

			if (fDistPos < fDistScale + 4 * 32.f)
			{
				if (vecOpponent[i]->GetObjType() == OBJ_TYPE::AIRUNIT || vecOpponent[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT)
				{
					if (UNIT_STATUS::FROZEN == vecOpponent[i]->GetUnitStatus())
						continue;
				}

				fDist1 = fDistPos;

				if ((vecOpponent[i]->GetObjType() == OBJ_TYPE::AIRUNIT || vecOpponent[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT))
				{
					if (Object()->GetTargetObj() == nullptr&& vecOpponent[i]->GetUnitStatus() != UNIT_STATUS::DIE)
					{
						if (Object()->GetName() == L"Corsair")
						{
							if (vecOpponent[i]->GetObjType() == OBJ_TYPE::AIRUNIT)
							{
								if (0.f == fDist2)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
								else if (fDist2 > fDist1)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
							}
						}
						else if (Object()->GetName() == L"Zealot" || Object()->GetName() == L"DarkTemplar")
						{
							if (vecOpponent[i]->GetObjType() == OBJ_TYPE::GROUNDUNIT || vecOpponent[i]->GetObjType() == OBJ_TYPE::BUILDING)
							{
								if (0.f == fDist2)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
								else if (fDist2 > fDist1)
								{
									fDist2 = fDist1;
									iIdx = i;
								}
							}
						}
						else
						{
							if (0.f == fDist2)
							{
								fDist2 = fDist1;
								iIdx = i;
							}
							else if (fDist2 > fDist1)
							{
								fDist2 = fDist1;
								iIdx = i;
							}
						}
					}
				}
				if (vecOpponent[i]->GetObjType() == OBJ_TYPE::BUILDING)
				{
					if (L"Corsair" != Object()->GetName())
					{
						CBuildingScript* pBuildingScript = nullptr;
						for (size_t j = 0; j < vecOpponent[i]->Script().size(); ++j)
						{
							if ((UINT)SCRIPT_TYPE::BUILDINGSCRIPT == vecOpponent[i]->Script()[j]->GetScriptType())
							{
								pBuildingScript = (CBuildingScript*)vecOpponent[i]->Script()[j];
							}
						}
						if (pBuildingScript->GetExplosion())
							continue;
						else
						{
							if (0.f == fDist2)
							{
								fDist2 = fDist1;
								iIdx = i;
							}
							else if (fDist2 > fDist1)
							{
								fDist2 = fDist1;
								iIdx = i;
							}
						}
					}
				}
			}
		}
		if (-1 == iIdx)
			return;
		else
			Object()->SetTarget(vecOpponent[iIdx]);
	}
}

void CUnitScript::Attack()
{
	CGameObject* pTarget = Object()->GetTargetObj();

	Vec3 vObjPos = Object()->Transform()->GetLocalPos();
	Vec3 vObjScale = Object()->Transform()->GetLocalScale()* Object()->Collider()->GetOffsetScale();

	Vec3 vOpponentPos = Object()->GetTargetObj()->Transform()->GetLocalPos();
	Vec3 vOpponentScale = Object()->GetTargetObj()->Transform()->GetLocalScale()* Object()->GetTargetObj()->Collider()->GetOffsetScale();

	float fDistPos = sqrt((vObjPos.x - vOpponentPos.x)*(vObjPos.x - vOpponentPos.x) + (vObjPos.y - vOpponentPos.y)*(vObjPos.y - vOpponentPos.y));
	float fDistScale = sqrt((vObjScale.x*0.5 * vObjScale.x*0.5) + (vObjScale.y*0.5 - vObjScale.y*0.5)) + sqrt((vOpponentScale.x*0.5 * vOpponentScale.x*0.5) + (vOpponentScale.y*0.5* vOpponentScale.y*0.5));

	m_vDir = Object()->GetTargetObj()->Transform()->GetLocalPos() - vObjPos;

	m_vDir.Normalize();

	// 건물은 가로 길이가 많이 달라서 그럼
	if ((UNIT_STATUS::IDLE == Object()->GetUnitStatus() || UNIT_STATUS::MOVE == Object()->GetUnitStatus()))
	{
		if (pTarget->GetObjType() != OBJ_TYPE::BUILDING)
		{
			if (m_iRange == 1)
			{
				if (fDistPos < fDistScale + 2.f* m_iRange)
				{
					Reset();
					Object()->SetUnitStatus(UNIT_STATUS::ATTACK);
				}
			}
			else
			{
				if (fDistPos < fDistScale + 32.f*(m_iRange - 1.f))
				{
					Reset();
					Object()->SetUnitStatus(UNIT_STATUS::ATTACK);
				}
			}
		}
		else
		{
			if (m_iRange == 1)
			{
				if (fDistPos < fDistScale +10*m_iRange)
				{
					Reset();
					Object()->SetUnitStatus(UNIT_STATUS::ATTACK);
				}

			}
			else
			{
				if (fDistPos < fDistScale + 32*( m_iRange-1))
				{
					Reset();
					Object()->SetUnitStatus(UNIT_STATUS::ATTACK);
				}
			}
		}
	}

	if (OBJ_TYPE::GROUNDUNIT == Object()->GetObjType())
	{
		if (pTarget->GetObjType() != OBJ_TYPE::BUILDING)
		{
			if (m_iRange == 1)
			{
				if (fDistPos > fDistScale + 2 * (m_iRange))
				{
					Object()->SetUnitStatus(UNIT_STATUS::MOVE);
					vObjPos.x += m_vDir.x * DT*GetUnitSpeed()*1.4f;
					vObjPos.y += m_vDir.y * DT*GetUnitSpeed()*1.4f;

					wstring name = Object()->GetName();
					name += L"Move";

					Object()->Animator2D()->SetCurAnimName(name);
				}
			}
			else
			{
				if (fDistPos > fDistScale + 32 * (m_iRange - 1))
				{
					Object()->SetUnitStatus(UNIT_STATUS::MOVE);
					vObjPos.x += m_vDir.x * DT*GetUnitSpeed()*1.4f;
					vObjPos.y += m_vDir.y * DT*GetUnitSpeed()*1.4f;

					wstring name = Object()->GetName();
					name += L"Move";

					Object()->Animator2D()->SetCurAnimName(name);
				}
			}

		}
		else
		{
			if (m_iRange == 1)
			{
				if (fDistPos > fDistScale + 10 * (m_iRange))
				{
					Object()->SetUnitStatus(UNIT_STATUS::MOVE);
					vObjPos.x += m_vDir.x * DT*GetUnitSpeed()*1.4f;
					vObjPos.y += m_vDir.y * DT*GetUnitSpeed()*1.4f;

					wstring name = Object()->GetName();
					name += L"Move";

					Object()->Animator2D()->SetCurAnimName(name);
				}
			}
			else
			{
				if (fDistPos > fDistScale + 32 * (m_iRange - 1))
				{
					Object()->SetUnitStatus(UNIT_STATUS::MOVE);
					vObjPos.x += m_vDir.x * DT*GetUnitSpeed()*1.4f;
					vObjPos.y += m_vDir.y * DT*GetUnitSpeed()*1.4f;

					wstring name = Object()->GetName();
					name += L"Move";

					Object()->Animator2D()->SetCurAnimName(name);
				}
			}
		}
	}
	else
	{
		if (fDistPos > fDistScale + 32 * (m_iRange - 1))
		{
			Object()->SetUnitStatus(UNIT_STATUS::MOVE);

			wstring name = Object()->GetName();
			name += L"Move";

			Object()->Animator2D()->SetCurAnimName(name);
		}
	}

	if (UNIT_STATUS::ATTACK == Object()->GetUnitStatus())
	{
		if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
			m_iMaxCount = 0;

		wstring AnimName = Object()->GetName();
		if (L"DarkTemplar" == AnimName)
		{
			AnimName = L"Dark Templar";
		}
		else if (L"HighTemplar" == AnimName) // 스킬이 장전되어있을때
		{
			AnimName = L"High Templar";
		}
		AnimName += L"Att";
		Object()->Animator2D()->SetCurAnimName(AnimName);

		if (UNIT_TYPE::CORSAIR == GetUnitType() || UNIT_TYPE::CARRIER == GetUnitType()
			|| UNIT_TYPE::ARBITER == GetUnitType() || UNIT_TYPE::SCOUT == GetUnitType() || UNIT_TYPE::OBSERVER == GetUnitType())
		{
			AirUnitAnimation(); // 0~16이 가만히 있는 상태
		}
		else
			GroundUnitAnimation(); // 0~16이 가만히 있는 상태

		m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();
	}
	else if (UNIT_STATUS::MOVE == Object()->GetUnitStatus())
	{
		if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
			m_iMaxCount = 0;

		wstring AnimName = Object()->GetName();

		AnimName += L"Move";
		Object()->Animator2D()->SetCurAnimName(AnimName);

		if (UNIT_TYPE::CORSAIR == GetUnitType() || UNIT_TYPE::CARRIER == GetUnitType()
			|| UNIT_TYPE::ARBITER == GetUnitType() || UNIT_TYPE::SCOUT == GetUnitType() || UNIT_TYPE::OBSERVER == GetUnitType())
		{
			AirUnitAnimation(); // 0~16이 가만히 있는 상태
		}
		else
			GroundUnitAnimation(); // 0~16이 가만히 있는 상태

		m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();
	}


	Object()->Transform()->SetLocalPos(Vec3(vObjPos.x,vObjPos.y,100.f));
}

void CUnitScript::Frozen()
{
	m_fAccFlozenDT += DT;
	if (!m_bFrozen)
	{
		m_bFrozenReset = false;

		CString strProbeMining = Object()->GetName().c_str();
		strProbeMining += L"Att";

		wstring strFrozenFolderPath = L"Texture\\Animation2D\\Protoss\\Effect\\Frozen\\";

		CGameObject* pGameObject = new CGameObject;
		pGameObject->SetName(L"Frozen");
		pGameObject->AddComponent(new CMeshRender);
		pGameObject->AddComponent(new CAnimator2D);

		pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pGameObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		pGameObject->Animator2D()->AddAnimation(strFrozenFolderPath, L"Frozen", true);
		pGameObject->Animator2D()->SetCurAnimName(L"Frozen");

		pGameObject->Transform()->SetLocalScale(Vec3(80.f, 80.f, 1.f));

		Object()->AddChild(pGameObject);

		m_bFrozen = true;
	}

	for (size_t i = 0; i < Object()->GetChild().size(); ++i)
	{
		Vec3 vPos = Object()->Transform()->GetLocalPos(); // m_vdir 0임 unitscript에서 못가져옴

		if (L"Frozen" == Object()->GetChild()[i]->GetName())
		{
			Object()->GetChild()[i]->Animator2D()->PlayAnim(L"Frozen", true);
			CAnimation2D* pCurAnim = Object()->GetChild()[i]->Animator2D()->GetAnimation();

			if (pCurAnim->GetCurFrm() == pCurAnim->GetFrame().size() - 1)
			{
				pCurAnim->SetFrmIdx(5);
			}
			Object()->GetChild()[i]->Transform()->SetLocalPos(vPos);

			if (m_fAccFlozenDT > 10.f)
			{
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT,(INT_PTR)Object()->GetChild()[i],NULL });
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object()->GetChild()[i] ,NULL });
				Object()->SetUnitStatus(UNIT_STATUS::IDLE);
				m_fAccFlozenDT = 0.f;
				m_bFrozen = false;
			}
		}
	}

	if (!m_bFrozenReset)
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

		Object()->SetTarget(nullptr);


		if (Object() == CUnitMgr::GetInst()->GetButtonOwner())
		{
			CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::NONE);
			CUnitMgr::GetInst()->SetButtonOwner(nullptr);
		}
		m_bFrozenReset = true;
	}
}

void CUnitScript::Recall()
{
	m_fRecallDT += DT;
	if (m_fRecallDT > 2)
	{
		Vec3 vCasterPos = CUnitMgr::GetInst()->GetButtonOwner()->Transform()->GetLocalPos();

		Vec3 vPos = Object()->Transform()->GetLocalPos();
		Vec3 vRecallCastingPos = m_vRecallCastingPos;
		Vec3 vDiff = vPos - vRecallCastingPos;

		Vec3 vDist = vPos - vCasterPos;

		vPos = vPos - vDist + vDiff;

		Object()->Transform()->SetLocalPos(Vec3(vPos.x,vPos.y, 100.f)); // 시젼하는 오브젝트를 알고 있어야 한다.
		Object()->SetUnitStatus(UNIT_STATUS::IDLE);
	}
}

void CUnitScript::Storm()
{
	// 초당으로 해야함.
	m_iHp -= 2;
}

void CUnitScript::Die()
{
	m_bDead = true;
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
	if(pMouseScript->GetTargetObj() == Object())
		pMouseScript->SetTargetObj(nullptr);

	Object()->SetTarget(nullptr);
	Object()->SetUnitStatus(UNIT_STATUS::DIE);


	if (Object() == CUnitMgr::GetInst()->GetButtonOwner())
	{
		CUIMgr::GetInst()->SetButtonChapter(BUTTON_CHAPTER::NONE);
		CUnitMgr::GetInst()->SetButtonOwner(nullptr);
	}

	if (Object() == pCurScene->GetHeadObj())
		pCurScene->SetHeadObj(nullptr);

}

void CUnitScript::ArbiterRad()
{

	if (Object()->GetName() == L"DarkTemplar")
	{
		if (m_pMtrl == nullptr)
		{
			m_pMtrl = Object()->MeshRender()->GetCloneMaterial();
		}

		int bAlpha = true;
		m_pMtrl->SetData(SHADER_PARAM::INT_0, &bAlpha);
		return;
	}

	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	if (Object()->GetLayerIdx() == pScene->GetLayer(L"Opponent")->GetIdx())
	{
		return;
	}
	vector<CGameObject*> vecAlly = pScene->GetLayer(L"Ally")->GetObjVec();

	vector<CGameObject*> vecArbiter;

	for (size_t i = 0; i < vecAlly.size(); ++i)
	{
		if (vecAlly[i]->GetName() == L"Arbiter")
		{
			vecArbiter.push_back(vecAlly[i]);
		}
	}

	for (size_t i = 0; i < vecArbiter.size(); ++i)
	{
		Vec3 vMyPos = Object()->Transform()->GetLocalPos();
		Vec3 vArbiterPos = vecArbiter[i]->Transform()->GetLocalPos();
		float fDist = sqrt((vMyPos.x - vArbiterPos.x)*(vMyPos.x - vArbiterPos.x)
			+ ((vMyPos.y - vArbiterPos.y)*(vMyPos.y - vArbiterPos.y)));
		
		if (fDist < 250.f)
		{

			if (m_pMtrl == nullptr)
			{
				m_pMtrl = Object()->MeshRender()->GetCloneMaterial();
			}

			int bAlpha = true;
			m_pMtrl->SetData(SHADER_PARAM::INT_0, &bAlpha);

		}
		else
		{

			if (m_pMtrl == nullptr)
			{
				m_pMtrl = Object()->MeshRender()->GetCloneMaterial();
			}

			int bAlpha = false;
			m_pMtrl->SetData(SHADER_PARAM::INT_0, &bAlpha);
		}
	}
}

void CUnitScript::OnCollisionEnter(CCollider * _pOther)
{
	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();

	if (Object()->Collider() != _pOther && OBJ_TYPE::RESOURCE == _pOther->Object()->GetObjType() && L"Probe" == Object()->GetName())
	{
		Reset();
	}

	if ((Object()->Collider() != _pOther && L"StasisField" == _pOther->Object()->GetName()))
	{
		Object()->SetUnitStatus(UNIT_STATUS::FROZEN);
	}
	if ((Object()->Collider() != _pOther && L"Recall" == _pOther->Object()->GetName()))
	{
		if (Object()->GetLayerIdx() == pScene->GetLayer(L"Ally")->GetIdx())
		{
			m_fRecallDT = 0.f;
			Object()->SetUnitStatus(UNIT_STATUS::RECALL);
			m_vRecallCastingPos = _pOther->Object()->Transform()->GetLocalPos();
		}
	}


}

void CUnitScript::OnCollision(CCollider * _pOther)
{


	if ((Object()->Collider() != _pOther && L"Storm" == _pOther->Object()->GetName()))
	{
		Object()->SetUnitStatus(UNIT_STATUS::STORM);
	}

	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	// oncollision
	if (_pOther->Object()->GetUnitStatus() != UNIT_STATUS::MINING)
	{

		if (Object()->Collider() != _pOther && _pOther->Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT &&
			Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT)
		{

			Vec3 vObjPos = Object()->Transform()->GetLocalPos();
			Vec3 vOtherPos = _pOther->Object()->Transform()->GetLocalPos();

			Vec3 vMyDir = vObjPos - vOtherPos;
			Vec3 vOtherDir = vOtherPos - vObjPos;

			vMyDir.Normalize();
			vOtherDir.Normalize();

			CUnitScript* pUnitScript = nullptr;
			for (size_t i = 0; i < _pOther->Object()->Script().size(); ++i)
			{
				if ((UINT)SCRIPT_TYPE::UNITSCRIPT == _pOther->Object()->Script()[i]->GetScriptType())
				{
					pUnitScript = (CUnitScript*)(_pOther->Object()->Script()[i]);
				}
			}

			if (UNIT_STATUS::ATTACK != Object()->GetUnitStatus())
				vObjPos += vMyDir * DT*2.5;
			if (UNIT_STATUS::ATTACK != _pOther->Object()->GetUnitStatus())
				vOtherPos += vOtherDir * DT*2.5;

			//if(UNIT_STATUS::ATTACK == Object()->GetUnitStatus())
			//	vObjPos += vMyDir * DT;
			//if (UNIT_STATUS::ATTACK == _pOther->Object()->GetUnitStatus())
			//	vOtherPos += vOtherDir * DT;

			Object()->Transform()->SetLocalPos(Vec3(vObjPos.x, vObjPos.y, 100.f));
			_pOther->Object()->Transform()->SetLocalPos(Vec3(vOtherPos.x, vOtherPos.y, 100.f));
		}
	}

	if (Object()->Collider() != _pOther && _pOther->Object()->GetObjType() == OBJ_TYPE::BUILDING &&
		Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT)
	{

		if (_pOther->Object()->GetName() == L"PylonRadius")
			return;

		//m_bFix = true;
		Vec3 vObjPos = Object()->Transform()->GetLocalPos();
		Vec3 vOtherPos = _pOther->Object()->Transform()->GetLocalPos();

		Vec3 vMyDir = vObjPos - vOtherPos;
		vMyDir.Normalize();

		vObjPos.x += vMyDir.x * DT*2.5f;
		vObjPos.y += vMyDir.y *DT*2.5f;

		Object()->Transform()->SetLocalPos(Vec3(vObjPos.x,vObjPos.y,100.f));
	}
}

void CUnitScript::OnCollisionExit(CCollider * _pOther)
{


	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();

	//if (Object()->Collider() != _pOther && _pOther->Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT &&
	//	Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT)
	//{
	//	if (m_bWait)
	//	{
	//		m_bWait = false;
	//		Object()->SetUnitStatus(UNIT_STATUS::MOVE);
	//	}

	//	CUnitScript* pUnitScript = nullptr;
	//	for (int i = 0; i < _pOther->Object()->Script().size(); ++i)
	//	{
	//		if ((UINT)SCRIPT_TYPE::UNITSCRIPT == _pOther->Object()->Script()[i]->GetScriptType())
	//		{
	//			pUnitScript = (CUnitScript*)(_pOther->Object()->Script()[i]);
	//		}
	//	}

	//	if (pUnitScript->GetWait())
	//	{
	//		pUnitScript->Wait(false);
	//		_pOther->Object()->SetUnitStatus(UNIT_STATUS::MOVE);
	//	}
	//}

}

void CUnitScript::Save(FILE * _pFile)
{
	fwrite(&m_fSpeed, sizeof(int), 1, _pFile);
	fwrite(&m_iHp, sizeof(int), 1, _pFile);
	fwrite(&m_iMaxHp, sizeof(int), 1, _pFile);
	fwrite(&m_iShield, sizeof(int), 1, _pFile);
	fwrite(&m_iMaxShield, sizeof(int), 1, _pFile);
	fwrite(&m_iGroundAtt, sizeof(int), 1, _pFile);
	fwrite(&m_iAirAtt, sizeof(int), 1, _pFile);
	fwrite(&m_iRange, sizeof(int), 1, _pFile);
	fwrite(&m_iMineralCost, sizeof(int), 1, _pFile);
	fwrite(&m_iGasCost, sizeof(int), 1, _pFile);
	fwrite(&m_eUnitType, sizeof(UINT), 1, _pFile);
}

void CUnitScript::Load(FILE * _pFile)
{
	fread(&m_fSpeed, sizeof(int), 1, _pFile);
	fread(&m_iHp, sizeof(int), 1, _pFile);
	fread(&m_iMaxHp, sizeof(int), 1, _pFile);
	fread(&m_iShield, sizeof(int), 1, _pFile);
	fread(&m_iMaxShield, sizeof(int), 1, _pFile);
	fread(&m_iGroundAtt, sizeof(int), 1, _pFile);
	fread(&m_iAirAtt, sizeof(int), 1, _pFile);
	fread(&m_iRange, sizeof(int), 1, _pFile);
	fread(&m_iMineralCost, sizeof(int), 1, _pFile);
	fread(&m_iGasCost, sizeof(int), 1, _pFile);
	fread(&m_eUnitType, sizeof(UINT), 1, _pFile);
}

////////////
//if (1 < vecGroundArmy.size())
//{
//	m_vDestPos = CKeyMgr::GetInst()->GetMousePos();

//	sort(vecGroundArmy.begin(), vecGroundArmy.end(), [](CGameObject* _pObj1, CGameObject* _pObj2)
//	{
//		Vec3 vDestPos = CKeyMgr::GetInst()->GetMousePos();
//		return sqrt((_pObj1->Transform()->GetLocalPos().x - vDestPos.x)*(_pObj1->Transform()->GetLocalPos().x - vDestPos.x)
//			+ (_pObj1->Transform()->GetLocalPos().y - vDestPos.y)*(_pObj1->Transform()->GetLocalPos().y - vDestPos.y))
//			< sqrt((_pObj2->Transform()->GetLocalPos().x - vDestPos.x)*(_pObj2->Transform()->GetLocalPos().x - vDestPos.x)
//				+ (_pObj2->Transform()->GetLocalPos().y - vDestPos.y)*(_pObj2->Transform()->GetLocalPos().y - vDestPos.y));
//	});

//	if (Object() == vecGroundArmy[0])
//	{
//		pCurScene->SetHeadObj(Object());
//	}
//	else // 이건 오 ㅐ있는거지?
//		return;
//} // 벽과 충돌중일때 a스타 돌림
////////

//if (Object()->Collider() != _pOther && _pOther->Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT &&
//	Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT)
//{
//
//	Vec3 vObjPos = Object()->Transform()->GetLocalPos();
//	Vec3 vOtherPos = _pOther->Object()->Transform()->GetLocalPos();
//	float fObjDist = sqrt((vObjPos.x - m_vDestPos.x)*(vObjPos.x - m_vDestPos.x) + (vObjPos.y - m_vDestPos.y)*(vObjPos.y - m_vDestPos.y));
//	float fOtherDist = sqrt((vOtherPos.x - m_vDestPos.x)*(vOtherPos.x - m_vDestPos.x) + (vOtherPos.y - m_vDestPos.y)*(vOtherPos.y - m_vDestPos.y));
//
//	CUnitScript* pUnitScript = nullptr;
//	for (int i = 0; i < _pOther->Object()->Script().size(); ++i)
//	{
//		if ((UINT)SCRIPT_TYPE::UNITSCRIPT == _pOther->Object()->Script()[i]->GetScriptType())
//		{
//			pUnitScript = (CUnitScript*)(_pOther->Object()->Script()[i]);
//		}
//	}
//
//	if (fObjDist < fOtherDist)
//	{
//		pUnitScript->Wait(true);
//		_pOther->Object()->SetUnitStatus(UNIT_STATUS::IDLE);
//		m_bWait = false;
//	}
//	else
//	{
//		m_bWait = true;
//		pUnitScript->Wait(false);
//		Object()->SetUnitStatus(UNIT_STATUS::IDLE);
//	}
//
//}


// 따라 다니는 놈들
//if (Object() != pCurScene->GetHeadObj() && nullptr != pCurScene->GetHeadObj() && !m_bWait)
//{
//	for (size_t i = 0; i < vecFollow.size(); ++i)
//	{
//		if (Object() == vecFollow[i] && Object()->GetLayerIdx() == pCurScene->GetLayer(L"Ally")->GetIdx() && Object()->GetObjType() == OBJ_TYPE::GROUNDUNIT)
//		{
//			Vec3 vFollowPos = Object()->Transform()->GetLocalPos();
//			m_vDir = pCurScene->GetHeadObj()->Transform()->GetLocalPos() - vFollowPos;

//			Object()->SetUnitStatus(UNIT_STATUS::MOVE);

//			if (m_szBeforeAnimName != Object()->Animator2D()->GetCurAnimName())
//				m_iMaxCount = 0;

//			GroundUnitAnimation(); // 0~16이 가만히 있는 상태
//			m_szBeforeAnimName = Object()->Animator2D()->GetCurAnimName();

//			//Vec3 vFlock = Clustering();
//			//m_vDir += vFlock;

//			m_vDir.Normalize();

//			vFollowPos.x += DT * m_vDir.x*GetUnitSpeed();
//			vFollowPos.y += DT * m_vDir.y*GetUnitSpeed();

//			Object()->Transform()->SetLocalPos(vFollowPos);
//		}
//	}
//}
///
