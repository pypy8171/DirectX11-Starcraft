#include "stdafx.h"
#include "MineralScript.h"
#include "YongEngine/GameObject.h"

#include "YongEngine/Transform.h"
#include "YongEngine/Animation2D.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/MeshRender.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/TimeMgr.h"
#include "YongEngine/SceneMgr.h"
#include "ScriptMgr.h"

CMineralScript::CMineralScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::MINERALSCRIPT);

}

CMineralScript::~CMineralScript()
{
}

int CMineralScript::update()
{
	if (0 == Object()->GetChild().size())
	{
		CString strShadName = Object()->GetName().c_str();
		strShadName += L"0Shad00";
	
		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>((wstring)strShadName);

		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
		CGameObject* pGameObject = new CGameObject;
		pGameObject->AddComponent(new CMeshRender);

		CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

		pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pGameObject->MeshRender()->SetMaterial(pMtrl);
		pGameObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex);

		pGameObject->Transform()->SetLocalPos(Object()->Transform()->GetLocalPos());
		pGameObject->Transform()->SetLocalScale(Vec3(pTex->GetWidth(), pTex->GetHeight(), 1.f));

		Object()->AddChild(pGameObject);

	}

	return 0;
}

int CMineralScript::lateupdate()
{
	return 0;
}
