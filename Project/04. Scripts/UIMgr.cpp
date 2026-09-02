#include "stdafx.h"
#include "UIMgr.h"
#include "atlstr.h"

#include "YongEngine/Transform.h"
#include "YongEngine/Animator2D.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Scene.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/Layer.h"

#include "YongEngine/KeyMgr.h"

#include "NumberMgr.h"
#include "ScriptMgr.h"


CUIMgr::CUIMgr()
	: m_vCamPos(Vec3(0.f,0.f,0.f))
	, m_eButtonChapter(BUTTON_CHAPTER::NONE)
	, m_eBeforeButtonChapter(BUTTON_CHAPTER::NONE)
	, m_pTargetObj(nullptr)
	, m_bProduce(false)
	, m_bProduceOut(false)
	, m_bProduceBtnClick(false)
	, m_bClicked(false)
	, m_iMineral(50)
	, m_iGas(0)
	, m_bMineralRequest(false)
	, m_bGasRequest(false)
{
	SetScriptType((UINT)SCRIPT_TYPE::UIMGR);
}

int CUIMgr::m_iMineralOn = 0;
int CUIMgr::m_iGasOn = 0;

CUIMgr::~CUIMgr()
{
}


int CUIMgr::update()
{
	if (L"StudyScene" == CSceneMgr::GetInst()->GetCurrentScene()->GetName())
		return 0;

	if (KEYAWAY(KEY_TYPE::KEY_9))
	{
		m_iMineral += 2000;
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	CLayer* pCameraLayer = pCurScene->GetLayer(L"Camera");
	CGameObject* pCameraObject = pCameraLayer->GetObjVec()[0];
	m_vCamPos  = pCameraObject->Transform()->GetLocalPos();

	// 현재 누른 오브젝트
	vector<CGameObject*> vecTargetObj = pCurScene->GetCurTargetObjVec();
	m_vecTargetObj = vecTargetObj;//pCurScene->FindObject(pCurScene->GetCurTargetObjName());

	m_pTargetObj = pCurScene->GetTargetObj();

	if (0 == m_iMineralOn)
	{
		CNumberMgr::GetInst()->SetMineralRequest(true);
		//m_bMineralRequest = true;
		m_iMineralOn = 1;
	}

	if (0 == m_iGasOn)
	{
		CNumberMgr::GetInst()->SetGasRequest(true);
		//m_bGasRequest = true;
		m_iGasOn = 1;
	}

	return 0;
}

int CUIMgr::lateupdate()
{
	return 0;
}

const wstring & CUIMgr::SubtractName(wstring & SubtractName)
{
	CString szText = SubtractName.c_str();

	int iTextSize = szText.GetLength();
	CString szTemp = szText;

	if ((L"Move") == szTemp.Right(4) || (L"Body") == szTemp.Right(4) || (L"Aura") == szTemp.Right(4) || (L"Shad") == szTemp.Right(4))
	{
		szText = szText.Left(iTextSize - 4);
	}
	else if (L"Att" == szTemp.Right(3))
	{
		szText = szText.Left(iTextSize - 3);
	}
	else if (L"Normal" == szTemp.Right(6) || L"Create" == szTemp.Right(6) || L"Prefab" == szTemp.Right(6))
	{
		szText = szText.Left(iTextSize - 6);
	}
	if (L"Build" == szTemp.Left(5))
	{
		iTextSize = szText.GetLength();
		szText = szText.Right(iTextSize-5);
	}

	SubtractName = szText;
	return SubtractName;
}
