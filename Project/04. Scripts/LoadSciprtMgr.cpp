#pragma once
#include "stdafx.h"
#include "LoadSciprtMgr.h"

#include "YongEngine/CollisionMgr.h"
#include "YongEngine/Scene.h"
#include "YongEngine/Layer.h"
#include "YongEngine/GameObject.h"
#include "YongEngine/Component.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/ResMgr.h"

#include "ScriptMgr.h"

CLoadSciprtMgr::CLoadSciprtMgr()
{
}


CLoadSciprtMgr::~CLoadSciprtMgr()
{
}


int CLoadSciprtMgr::update()
{
	return 0;
}

int CLoadSciprtMgr::lateupdate()
{
	return 0;
}

void CLoadSciprtMgr::SaveScene(const wstring & _strScenePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strScenePath.c_str(), L"wb");
	assert(pFile);

	// Resource 저장( Prefab 제외)
	SaveResource(pFile);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	assert(pCurScene);

	// Scene 정보를 저장
	UINT iLayerCount = pCurScene->GetLayerCount();
	fwrite(&iLayerCount, sizeof(UINT), 1, pFile);
	for (UINT i = 0; i < iLayerCount; ++i)
	{
		CLayer* pLayer = pCurScene->GetLayer(i);
		SaveLayer(pLayer, pFile);
	}

	CCollisionMgr::GetInst()->SaveFile(pFile);

	fclose(pFile);
}



void CLoadSciprtMgr::SaveLayer(CLayer * _pLayer, FILE * _pFile)
{
	// Layer Name
	SaveWString(_pLayer->GetName(), _pFile);

	//UINT iLayerIdx = _pLayer->GetIdx();

	//fwrite(&iLayerIdx, sizeof(UINT), 1, _pFile);

	// GameObject
	vector<CGameObject*>& vecParentObj = _pLayer->GetObjVec();
	UINT vecSize = vecParentObj.size();

	fwrite(&vecSize, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < vecSize; ++i)
	{
		SaveGameObject(vecParentObj[i], _pFile);
	}
}

// 이거 이유가 뭐엿지?
void CLoadSciprtMgr::SaveGameObject(CGameObject * _pObj, FILE * _pFile)
{
	_pObj->Save(_pFile);

	// GameObject의 Script 정보 저장
	vector<CScript*>& vecScript = _pObj->Script();
	UINT iScriptCount = vecScript.size();
	fwrite(&iScriptCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < vecScript.size(); ++i)
	{
		// 스크립트 이름 저장
		SaveWString(CScriptMgr::GetScriptName(vecScript[i]), _pFile);

		// 스크립트 데이터 저장
		vecScript[i]->::CComponent::Save(_pFile);
		vecScript[i]->Save(_pFile);
	}
	// 자식들 저장
	vector<CGameObject*>& vecChild = _pObj->GetChild();

	UINT iChildCount = vecChild.size();
	fwrite(&iChildCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iChildCount; ++i)
	{
		SaveGameObject(vecChild[i], _pFile);
	}
}


void CLoadSciprtMgr::LoadScene(const wstring & _strScenePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strScenePath.c_str(), L"rb");
	assert(pFile);

	// 리소스 로딩
	LoadResource(pFile);

	CScene* pNewScene = new CScene;
	CSceneMgr::GetInst()->ChangeScene(pNewScene);

	// Scene 정보를 로딩	
	UINT iLayerCount = 0;
	fread(&iLayerCount, sizeof(UINT), 1, pFile);
	pNewScene->SetLayerCount(0);

	for (UINT i = 0; i < iLayerCount; ++i)
	{
		CLayer* pLayer = new CLayer;
		pNewScene->AddLayer(pLayer);
		LoadLayer(pLayer, pFile);
	}

	CCollisionMgr::GetInst()->LoadFile(pFile);


	fclose(pFile);

	FILE* pPrefabFile = nullptr;

	CString strPrefabPath =	L"C:\\Users\\YongHwan\\source\\repos\\YongEngine\\Game_Release\\content\\Resource\\Prefab\\pf.text";

	_wfopen_s(&pPrefabFile, strPrefabPath.GetBuffer(), L"rb");

	LoadPrefab(NULL, pPrefabFile);
	map<wstring, CRes*> mapPrefab = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::PREFAB);

	fclose(pPrefabFile);
}

void CLoadSciprtMgr::LoadLayer(CLayer* _pLayer, FILE * _pFile)
{
	wstring strLayerName = LoadWString(_pFile);
	_pLayer->SetName(strLayerName);

	UINT iObjCount = 0;
	fread(&iObjCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iObjCount; ++i)
	{
		CGameObject* pNewObj = LoadGameObject(_pFile);
		_pLayer->AddGameObject(pNewObj);
		for (size_t i = 0; i < pNewObj->GetChild().size(); ++i)
		{
			pNewObj->GetChild()[i]->SetLayerIdx(pNewObj->GetLayerIdx());
		}

	}
}

CGameObject * CLoadSciprtMgr::LoadGameObject(FILE * _pFile)
{
	CGameObject* pObj = new CGameObject;

	// 컴포넌트 로딩
	pObj->Load(_pFile);

	// GameObject 의 Script 정보 로딩	
	UINT iScriptCount = 0;
	fread(&iScriptCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iScriptCount; ++i)
	{
		// 스크립트 이름 로딩
		wstring strScriptName = LoadWString(_pFile);
		CScript* pScript = CScriptMgr::GetScript(strScriptName);

		// 스크립트가 저장한 정보를 다시 복구
		pScript->::CComponent::Load(_pFile);
		pScript->Load(_pFile);

		pObj->AddComponent(pScript);

	}

	// ChildObject 로딩
	// Child 
	UINT iChildCount = 0;
	fread(&iChildCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iChildCount; ++i)
	{
		CGameObject* pChildObj = LoadGameObject(_pFile);
		pObj->AddChild(pChildObj);
	}

	return pObj;
}

void CLoadSciprtMgr::SaveResource(FILE * _pFile)
{
	for (UINT i = 0; i < (UINT)RESOURCE_TYPE::END; ++i)
	{
		const map<wstring, CRes*>& mapRes = CResMgr::GetInst()->GetResourceMap((RESOURCE_TYPE)i);

		// Resource 타입
		fwrite(&i, sizeof(UINT), 1, _pFile);

		// Resource 개수
		UINT iCount = mapRes.size();
		fwrite(&iCount, sizeof(UINT), 1, _pFile);

		if ((UINT)RESOURCE_TYPE::PREFAB == i)
		{
			//SavePrefab(mapRes, _pFile, nullptr);
			continue;
		}
		else
		{
			for (auto& pair : mapRes)
			{
				pair.second->FileSave(_pFile);
			}
		}
	}

	// Resource 타입
	UINT i = (UINT)RESOURCE_TYPE::END;
	fwrite(&i, sizeof(UINT), 1, _pFile);
}

void CLoadSciprtMgr::LoadResource(FILE * _pFile)
{
	while (true)
	{
		RESOURCE_TYPE eResType = RESOURCE_TYPE::END;
		fread(&eResType, sizeof(UINT), 1, _pFile);

		if (eResType == RESOURCE_TYPE::END)
			break;

		int iCount = 0;
		fread(&iCount, sizeof(int), 1, _pFile);

		switch (eResType)
		{
		case RESOURCE_TYPE::MESH:

			break;
		case RESOURCE_TYPE::TEXTURE:
			for (int i = 0; i < iCount; ++i)
			{
				CTexture::FileLoad(_pFile);
			}
			break;
		case RESOURCE_TYPE::MATERIAL:
			for (int i = 0; i < iCount; ++i)
			{
				CMaterial::FileLoad(_pFile);
			}
			break;
		case RESOURCE_TYPE::SOUND:
			for (int i = 0; i < iCount; ++i)
			{
				CSound::FileLoad(_pFile);
			}
			break;
		case RESOURCE_TYPE::PREFAB:
			//LoadPrefab(iCount, _pFile);
			break;
		default:
			break;
		}
	}
}


void CLoadSciprtMgr::SavePrefabObject(CGameObject * _pPrefabObj, FILE * _pFile)
{
	_pPrefabObj->Save(_pFile);

	// GameObject의 Script 정보 저장
	vector<CScript*>& vecScript = _pPrefabObj->Script();
	UINT iScriptCount = vecScript.size();
	fwrite(&iScriptCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < vecScript.size(); ++i)
	{
		// 스크립트 이름 저장
		SaveWString(CScriptMgr::GetScriptName(vecScript[i]), _pFile);

		// 스크립트 데이터 저장
		vecScript[i]->::CComponent::Save(_pFile);
		vecScript[i]->Save(_pFile);
	}
	// 자식들 저장
	vector<CGameObject*>& vecChild = _pPrefabObj->GetChild();

	UINT iChildCount = vecChild.size();
	fwrite(&iChildCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iChildCount; ++i)
	{
		SaveGameObject(vecChild[i], _pFile);
	}
}

void CLoadSciprtMgr::SavePrefab(const map<wstring, CRes*>& _mapPrefab, FILE * _pSceneFile, FILE* _pPrefabFile)
{
	if (nullptr == _pSceneFile && nullptr == _pPrefabFile)
		assert(&_pSceneFile);

	UINT iSize = _mapPrefab.size();

	if (nullptr != _pSceneFile)
	{
		fwrite(&iSize, sizeof(UINT), 1, _pSceneFile);
		for (auto& pair : _mapPrefab)
		{
			SaveWString(pair.second->GetName(), _pSceneFile);
			SaveGameObject(((CPrefab*)pair.second)->GetOriginObj(), _pSceneFile);
		}
	}

	if (nullptr != _pPrefabFile)
	{
		for (UINT i = 0; i < (UINT)RESOURCE_TYPE::END; ++i)
		{
			const map<wstring, CRes*>& mapRes = CResMgr::GetInst()->GetResourceMap((RESOURCE_TYPE)i);

			// Resource 타입
			fwrite(&i, sizeof(UINT), 1, _pPrefabFile);

			// Resource 개수
			UINT iCount = mapRes.size();
			fwrite(&iCount, sizeof(UINT), 1, _pPrefabFile);

			if ((UINT)RESOURCE_TYPE::PREFAB == i)
			{
				continue;
			}
			else
			{
				for (auto& pair : mapRes)
				{
					pair.second->FileSave(_pPrefabFile);
				}
			}
		}
		// Resource 타입
		UINT i = (UINT)RESOURCE_TYPE::END;
		fwrite(&i, sizeof(UINT), 1, _pPrefabFile);

		fwrite(&iSize, sizeof(UINT), 1, _pPrefabFile);

		for (auto& pair : _mapPrefab)
		{
			SaveWString(pair.second->GetName(), _pPrefabFile);
			SavePrefabObject(((CPrefab*)pair.second)->GetOriginObj(), _pPrefabFile);
		}
	}
}

void CLoadSciprtMgr::LoadPrefab(int _iCount, FILE * _pFile)
{
	if (nullptr == _pFile)
		return;

	while (true)
	{
		RESOURCE_TYPE eResType = RESOURCE_TYPE::END;
		fread(&eResType, sizeof(UINT), 1, _pFile);

		if (eResType == RESOURCE_TYPE::END)
			break;

		int iCount = 0;
		fread(&iCount, sizeof(int), 1, _pFile);

		switch (eResType)
		{
		case RESOURCE_TYPE::MESH:

			break;
		case RESOURCE_TYPE::TEXTURE:
			for (int i = 0; i < iCount; ++i)
			{
				CTexture::FileLoad(_pFile);
			}
			break;
		case RESOURCE_TYPE::MATERIAL:
			for (int i = 0; i < iCount; ++i)
			{
				CMaterial::FileLoad(_pFile);
			}
			break;
		case RESOURCE_TYPE::SOUND:
			for (int i = 0; i < iCount; ++i)
			{
				CSound::FileLoad(_pFile);
			}
			break;
		case RESOURCE_TYPE::PREFAB:
			break;
		default:
			break;
		}
	}

	UINT iSize = 0;
	fread(&iSize, sizeof(UINT), 1, _pFile);

	for (size_t i = 0; i < iSize; ++i)
	{
		wstring strKey = LoadWString(_pFile);
		CGameObject* pObj = LoadGameObject(_pFile);

		CPrefab* pPrefab = CResMgr::GetInst()->Load<CPrefab>(strKey);
		if (nullptr == pPrefab)
		{
			CResMgr::GetInst()->AddResource<CPrefab>(strKey, new CPrefab(pObj));
		}
		else
			delete pObj;
	}
}


