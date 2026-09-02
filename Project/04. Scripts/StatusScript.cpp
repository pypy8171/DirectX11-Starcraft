#include "stdafx.h"
#include "StatusScript.h"

#include "YongEngine/Core.h"

#include "YongEngine/MeshRender.h"
#include "Transform.h"

#include "Animator2D.h"
#include "Animation2D.h"

#include "YongEngine/ResMgr.h"
#include "YongEngine/PathMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"

#include "MouseScript.h"
#include "ProduceScript.h"

#include "UIMgr.h"
#include "ScriptMgr.h"
#include "UnitMgr.h"

CStatusScript::CStatusScript()
	: m_strBeforeTexName{}
	, m_pMtrl(nullptr)
{
	SetScriptType((UINT)SCRIPT_TYPE::STATUSSCRIPT);
	init();
}


CStatusScript::~CStatusScript()
{
}

void CStatusScript::init()
{
	wstring strFolderPath = CPathMgr::GetResPath();

	strFolderPath += L"Texture\\Texture\\Protoss\\UI\\Status\\Normal\\";

	wstring strPngPath = strFolderPath + L"*.png";

	wstring strRelativePath;
	WIN32_FIND_DATA data{};
	HANDLE hFind = FindFirstFile(strPngPath.c_str(), &data);


	map<wstring, CRes*> pTexture = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);
	while (FindNextFile(hFind, &data))
	{
		strRelativePath = wstring(strFolderPath + data.cFileName);

		map<wstring, CRes*>::iterator iter = pTexture.find(strRelativePath);

		wstring strMidPath = L"Texture\\Texture\\Protoss\\UI\\Status\\Normal\\";
		strMidPath += data.cFileName;

		map<wstring, CRes*>::iterator iter2 = pTexture.find(data.cFileName);
		if (iter2 != pTexture.end())
			continue;

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(data.cFileName, strMidPath);

		//if (!) // null 만나면 퇴근.
		//	break;
	}

	FindClose(hFind);

}

int CStatusScript::update()
{
	if (nullptr == Object()->MeshRender())
		return false;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();

	tResolution tResolution = CCore::GetInst()->GetResoultion();


	Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
	Object()->Transform()->SetLocalPos(Vec3(vCamPos.x, -198 * tResolution.y / 480 + vCamPos.y, 5.f));

	CTexture* pTex = nullptr;

	CLayer* pMouseLayer = CSceneMgr::GetInst()->GetLayer(L"Mouse");

	if (0 == pMouseLayer->GetObjVec().size())
	{
		Object()->MeshRender()->SetRender(false);
		return 0;
	}

	CGameObject* pMouseObject = pMouseLayer->GetObjVec()[0];


	if (pCurScene->GetCurTargetObjVec().size() > 1 || nullptr == pMouseObject)
	{
		Object()->MeshRender()->SetRender(false);
		return 0;
	}

	CMouseScript* pMouseScript = nullptr;


	for (size_t i = 0; i < pMouseObject->Script().size(); ++i)
	{
		if ((UINT)SCRIPT_TYPE::MOUSESCRIPT == pMouseObject->Script()[i]->GetScriptType())
		{
			pMouseScript = (CMouseScript*)pMouseObject->Script()[i];
		}
	}

	if (nullptr == pMouseScript)
	{
		Object()->MeshRender()->SetRender(false);
		return 0;
	}

	CGameObject* pTargetObj = pMouseScript->GetTargetObj();


	if (nullptr == pTargetObj)
	{
		Object()->MeshRender()->SetRender(false);
		return 0;
	}

	if (pTargetObj->GetName() == L"PylonRadius")
		return 0;

	Object()->MeshRender()->SetRender(true);

	if (pTargetObj->GetObjType() == OBJ_TYPE::AIRUNIT || pTargetObj->GetObjType() == OBJ_TYPE::GROUNDUNIT)
	{
		wstring strTargetName = pTargetObj->GetName(); // 이름이 status

		if (strTargetName == L"DarkTemplar")
			strTargetName = L"Dark Templar";
		else if (strTargetName == L"HighTemplar")
			strTargetName = L"High Templar";
		else if (strTargetName == L"DarkArchon")
			strTargetName = L"Dark Archon";

		strTargetName += L"Status.png";

		m_strBeforeTexName = strTargetName;
	
		pTex = CResMgr::GetInst()->Load<CTexture>(strTargetName);
	}
	else if (false == (CUIMgr::GetInst()->GetProduce())&& pTargetObj->GetObjType() == OBJ_TYPE::BUILDING)
	{
		wstring strTargetName = pTargetObj->GetName(); // 이름이 status

		strTargetName += L"Status.png";

		m_strBeforeTexName = strTargetName;

		pTex = CResMgr::GetInst()->Load<CTexture>(strTargetName);
	}
	else if (!CUIMgr::GetInst()->GetProduce())
	{
		wstring strTargetName = pTargetObj->GetName(); // 이름이 status

		if (strTargetName == L"DarkTemplar")
			strTargetName = L"Dark Templar";
		else if (strTargetName == L"HighTemplar")
			strTargetName = L"High Templar";
		else if (strTargetName == L"DarkArchon")
			strTargetName = L"Dark Archon";

		strTargetName += L"Status.png";

		m_strBeforeTexName = strTargetName;

		pTex = CResMgr::GetInst()->Load<CTexture>(strTargetName);
	}
	else if(true == CUIMgr::GetInst()->GetProduce() && pTargetObj->GetObjType() == OBJ_TYPE::BUILDING)
	{
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Frame.png");
	}

	// 수정
	//if(pTex == nullptr)
	//	pTex = CResMgr::GetInst()->Load<CTexture>(L"Universe");

	if (nullptr == m_pMtrl)
		m_pMtrl = Object()->MeshRender()->GetCloneMaterial();

	if (pTex == nullptr)
		return 0;

	m_pMtrl->SetData(SHADER_PARAM::TEX_0, pTex);



	Transform()->SetLocalScale(Vec3(pTex->GetWidth()* tResolution.x/760, pTex->GetHeight() *tResolution.y / 480 *0.9, 5.f));
	Object()->Transform()->SetLocalPos(Vec3(vCamPos.x, -198 * tResolution.y / 480 + vCamPos.y, 5.f));

	return 0;
}

int CStatusScript::lateupdate()
{
	return 0;
}

void CStatusScript::NormalStatus()
{
}

void CStatusScript::ProduceStatus()
{
}
