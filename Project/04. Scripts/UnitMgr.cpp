#include "stdafx.h"
#include "UnitMgr.h"
#include "ScriptMgr.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Scene.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/Layer.h"

CUnitMgr::CUnitMgr()
	: m_pButtonOwner(nullptr)
{
	SetScriptType((UINT)SCRIPT_TYPE::UNITMGR);
}


CUnitMgr::~CUnitMgr()
{
}


int CUnitMgr::update()
{	
	// 현재 누른 오브젝트
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	pCurScene->GetCurTargetObjVec();
	m_vecTargetObj = pCurScene->GetCurTargetObjVec(); //pCurScene->FindObject(pCurScene->GetCurTargetObjName());
	return 0;
}

int CUnitMgr::lateupdate()
{
	return 0;
}
