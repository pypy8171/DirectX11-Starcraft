#include "stdafx.h"
#include "SeclectScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"

#include "YongEngine/Texture.h"
#include "YongEngine/Material.h"

#include "YongEngine/Layer.h"
#include "YongEngine/Scene.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/KeyMgr.h"

#include "ScriptMgr.h"
#include "UnitMgr.h"

CSeclectScript::CSeclectScript()
	: m_pCurSelObject(nullptr)
	
{
	memset(m_pTex, 0, 10);

	SetScriptType((UINT)SCRIPT_TYPE::SECLECTSCRIPT);

	// 

	static CTexture* pTex[10]{};
	pTex[0] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly0", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_0.png");
	pTex[1] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly1", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_1.png");;
	pTex[2] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly2", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_2.png");;
	pTex[3] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly3", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_3.png");;
	pTex[4] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly4", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_4.png");;
	pTex[5] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly5", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_5.png");;
	pTex[6] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly6", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_6.png");;
	pTex[7] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly7", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_7.png");;
	pTex[8] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly8", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_8.png");;
	pTex[9] = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly9", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_9.png");;

	for (int i = 0; i < 10; ++i)
	{
		m_pTex[i] = pTex[i];
	}

}


CSeclectScript::~CSeclectScript()
{
}

void CSeclectScript::init()
{
}


int CSeclectScript::update()
{
	// 크기는 19구분으로	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();

	vector<CGameObject*> vecTargetObj = pCurScene->GetCurTargetObjVec(); // 벡터로 넣어놓자.

	for (size_t i = 0; i < vecTargetObj.size(); ++i)
	{
		Vec3 vTargetObjScale = vecTargetObj[i]->Transform()->GetLocalScale();
		Vec3 vTargetObjPos = vecTargetObj[i]->Transform()->GetLocalPos();
		int iIdx = (int)((vTargetObjScale.x - 32) / 19);
		if (iIdx > 9)
		{
			iIdx = 9;
		}

		Object()->Transform()->SetLocalPos(Vec3(vTargetObjPos.x, vTargetObjPos.y - 15, vTargetObjPos.z));
		Object()->Transform()->SetLocalScale(Vec3(m_pTex[iIdx]->GetWidth(), m_pTex[iIdx]->GetHeight(), 1.f));
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, m_pTex[iIdx]);
	}
	

	Transform()->SetLocalPos(CKeyMgr::GetInst()->GetMousePos());

	return 0;
}


void CSeclectScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CSeclectScript::OnCollision(CCollider * _pOther)
{
	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectNeutral");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);

	}
}

void CSeclectScript::OnCollisionExit(CCollider * _pOther)
{
}
