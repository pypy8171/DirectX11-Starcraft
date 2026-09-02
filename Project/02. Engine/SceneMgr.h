#pragma once
#include "global.h"


class CScene;
class CLayer;
class CCamera;
class CGameObject;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	CScene * m_pCurScene;
	float	m_fTimer;

public:

	CScene* GetCurrentScene() { return m_pCurScene; }

public:
	void AddGameObject(const wstring& _strLayerName, CGameObject* _pObj);
	void AddGameObject(UINT _iLayerIdx, CGameObject* _pObj);

	CGameObject* FindObject(const wstring& _strName); // { assert(m_pCurScene); return m_pCurScene->FindObject(_strName); }
public:
	CLayer * GetLayer(int _iIdx);
	CLayer * GetLayer(const wstring& _strLayerName);
	void RegisterCamera(CCamera* _pCam);

public:
	void ChangeScene(CScene* _pScene);

public:
	void init();
	int update();
	void render();
};

