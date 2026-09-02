#include "stdafx.h"
#include "NumberMgr.h"

#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Layer.h"

#include "NumberScript.h"

#include "ScriptMgr.h"

CNumberMgr::CNumberMgr()
	: m_iNum(0)
	, m_pGameObject(nullptr)
	, m_bHpRequest(false)
	, m_bShieldRequest(false)
	, m_bMpRequest(false)
	, m_bMineralRequest(false)
	, m_bGasRequest(false)
{
	SetScriptType((UINT)SCRIPT_TYPE::NUMBERMGR);
	init();
}


CNumberMgr::~CNumberMgr()
{
}

int CNumberMgr::update()
{
	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();

	if (m_bHpRequest)
	{
		CNumberScript* pNumberScript = new CNumberScript;

		CGameObject* pNumber = new CGameObject;
		pNumber->SetName(L"HpNum");
		pNumber->AddComponent(new CMeshRender);
		pNumber->AddComponent(pNumberScript);

		pNumberScript->SetNumberType(NUMBER_TYPE::HP);
		pNumberScript->SetObject(m_pGameObject);

		pNumber->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pNumber->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		pScene->AddGameObject(L"ProtossUI", pNumber);

		m_bHpRequest = false;
	}

	if (m_bShieldRequest)
	{
		CNumberScript* pNumberScript = new CNumberScript;

		CGameObject* pNumber = new CGameObject;
		pNumber->SetName(L"ShieldNum");
		pNumber->AddComponent(new CMeshRender);
		pNumber->AddComponent(pNumberScript);

		pNumberScript->SetNumberType(NUMBER_TYPE::SHIELD);
		pNumberScript->SetObject(m_pGameObject);

		pNumber->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pNumber->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		pScene->AddGameObject(L"ProtossUI", pNumber);

		m_bShieldRequest = false;
	}

	if (m_bMineralRequest)
	{
		CNumberScript* pNumberScript = new CNumberScript;

		CGameObject* pNumber = new CGameObject;
		pNumber->SetName(L"MineralNum");
		pNumber->AddComponent(new CMeshRender);
		pNumber->AddComponent(pNumberScript);

		pNumberScript->SetNumberType(NUMBER_TYPE::MINERAL);

		pNumber->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pNumber->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		pScene->AddGameObject(L"ProtossUI", pNumber);

		m_bMineralRequest = false;
	}

	if (m_bGasRequest)
	{
		CNumberScript* pNumberScript = new CNumberScript;

		CGameObject* pNumber = new CGameObject;
		pNumber->SetName(L"GasNum");
		pNumber->AddComponent(new CMeshRender);
		pNumber->AddComponent(pNumberScript);

		pNumberScript->SetNumberType(NUMBER_TYPE::GAS);

		pNumber->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pNumber->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		pScene->AddGameObject(L"ProtossUI", pNumber);

		m_bGasRequest = false;
	}

	return 0;
}

int CNumberMgr::lateupdate()
{
	return 0;
}

void CNumberMgr::init()
{
	Normal();
	Shield();
	Mp();

}

void CNumberMgr::Normal()
{
	wstring strFolderPath = CPathMgr::GetResPath();

	strFolderPath += L"Texture\\Texture\\Protoss\\UI\\Number\\Normal\\";

	wstring strPngPath = strFolderPath + L"*.png";

	wstring strRelativePath;
	WIN32_FIND_DATA data{};
	HANDLE hFind = FindFirstFile(strPngPath.c_str(), &data);

	map<wstring, CRes*> pTexture = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);
	while (true)
	{
		strRelativePath = wstring(strFolderPath + data.cFileName);

		map<wstring, CRes*>::iterator iter = pTexture.find(strRelativePath);

		wstring strMidPath = L"Texture\\Texture\\Protoss\\UI\\Number\\Normal\\";
		strMidPath += data.cFileName;

		
		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(data.cFileName);

		if(pTex == nullptr)
			pTex = CResMgr::GetInst()->Load<CTexture>(data.cFileName, strMidPath);

		if (!FindNextFile(hFind, &data)) // null ¸¸³ª¸é Åð±Ù.
			break;
	}

	FindClose(hFind);
}

void CNumberMgr::Shield()
{
	wstring strFolderPath = CPathMgr::GetResPath();

	strFolderPath += L"Texture\\Texture\\Protoss\\UI\\Number\\Shield\\";

	wstring strPngPath = strFolderPath + L"*.png";

	wstring strRelativePath;
	WIN32_FIND_DATA data{};
	HANDLE hFind = FindFirstFile(strPngPath.c_str(), &data);

	map<wstring, CRes*> pTexture = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);
	while (true)
	{
		strRelativePath = wstring(strFolderPath + data.cFileName);

		map<wstring, CRes*>::iterator iter = pTexture.find(strRelativePath);

		wstring strMidPath = L"Texture\\Texture\\Protoss\\UI\\Number\\Shield\\";
		strMidPath += data.cFileName;

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(data.cFileName);

		if (pTex == nullptr)
			pTex = CResMgr::GetInst()->Load<CTexture>(data.cFileName, strMidPath);

		if (!FindNextFile(hFind, &data)) // null ¸¸³ª¸é Åð±Ù.
			break;
	}

	FindClose(hFind);
}

void CNumberMgr::Mp()
{
	wstring strFolderPath = CPathMgr::GetResPath();

	strFolderPath += L"Texture\\Texture\\Protoss\\UI\\Number\\Mp\\";

	wstring strPngPath = strFolderPath + L"*.png";

	wstring strRelativePath;
	WIN32_FIND_DATA data{};
	HANDLE hFind = FindFirstFile(strPngPath.c_str(), &data);

	map<wstring, CRes*> pTexture = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);
	while (true)
	{
		strRelativePath = wstring(strFolderPath + data.cFileName);

		map<wstring, CRes*>::iterator iter = pTexture.find(strRelativePath);

		wstring strMidPath = L"Texture\\Texture\\Protoss\\UI\\Number\\Mp\\";
		strMidPath += data.cFileName;

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(data.cFileName);

		if (pTex == nullptr)
			pTex = CResMgr::GetInst()->Load<CTexture>(data.cFileName, strMidPath);

		if (!FindNextFile(hFind, &data)) // null ¸¸³ª¸é Åð±Ù.
			break;
	}

	FindClose(hFind);
}
