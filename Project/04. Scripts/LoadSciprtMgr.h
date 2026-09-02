#pragma once

#include "Script.h"
using namespace std;


class CLayer;
class CGameObject;
class CRes;

class CLoadSciprtMgr
	: public CScript
{
public:
	virtual int update();
	virtual int lateupdate();
public:
	static void SaveScene(const wstring& _strScenePath);
	static void LoadScene(const wstring& _strScenePath);

	static void SavePrefab(const map<wstring, CRes*>& _mapPrefab, FILE* _pFile, FILE* _pPrefabFile);
	static void LoadPrefab(int _iCount, FILE* _pFile);

private:
	static void SaveLayer(CLayer* _pLayer, FILE* _pFile);
	static void SaveGameObject(CGameObject* _pObj, FILE* _pFile);
	static void SavePrefabObject(CGameObject* _pPrefabObj, FILE* _pFile);

	static void LoadLayer(CLayer* _pLayer, FILE* _pFile);
	static CGameObject* LoadGameObject(FILE* _pFile);

	static void SaveResource(FILE* _pFile);
	static void LoadResource(FILE* _pFile);


	CLONE(CLoadSciprtMgr);
public:
	CLoadSciprtMgr();
	virtual ~CLoadSciprtMgr();
};

