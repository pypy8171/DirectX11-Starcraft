#pragma once
#include "Entity.h"


class CLayer;
class CCamera;
class CGameObject;

class CScene :
	public CEntity
{
private:
	CLayer*					m_arrLayer[MAX_LAYER];
	UINT					m_iLayerCount;

	CGameObject*			m_pTargetObj;
	vector<CGameObject*>	m_vecTargetObj;
	vector<CCamera*>		m_vecCam;
	CGameObject*			m_pHeadObject;

public:
	virtual void awake();
	virtual void start();
	virtual int update();
	virtual int lateupdate();
	virtual int finalupdate();

public:
	void AddGameObject(const wstring& _strLayerName, CGameObject* _pObj);
	void AddGameObject(UINT _iLayerIdx, CGameObject* _pObj);
	void DeleteGameObject(const wstring& _strLayerName, CGameObject* _pObj);

	CGameObject* FindObject(const wstring& _strName);


public:
	CLayer * GetLayer(int _iIdx) { if (_iIdx == -1) return nullptr;  return m_arrLayer[_iIdx]; } // UINT -> int 로 바꿈 layer에없으면 -1로 등록해놨으므로.
	CLayer* GetLayer(const wstring& _strLayerName);

	void RegisterCamera(CCamera* _pCam) { m_vecCam.push_back(_pCam); }

public:
	void AddLayer(const wstring& _strLayerName);
	void AddLayer(CLayer * _pLayer);

	bool CheckLayer(const wstring& _strLayerName);

	UINT GetLayerCount() { return m_iLayerCount; }
	void SetLayerCount(UINT _iIdx) {m_iLayerCount = _iIdx;	}

	void AddTargetObj(CGameObject* _pTargetObj) { m_vecTargetObj.push_back(_pTargetObj); }
	const vector<CGameObject*>& GetCurTargetObjVec() { return m_vecTargetObj; }

	void SetTargetObj(CGameObject* _pTargetObj) { m_pTargetObj = _pTargetObj; }
	CGameObject* GetTargetObj() { return m_pTargetObj; }


	void SetCurTargetObjVecClear() {
		m_vecTargetObj.clear();
		m_vecTargetObj.shrink_to_fit();
	}

	void EmptyTargetObjList() { m_vecTargetObj.clear(); }

public:
	void SetHeadObj(CGameObject* _pGameObject) { m_pHeadObject = _pGameObject; }
	CGameObject* GetHeadObj() { return m_pHeadObject; }

public:
	void render();

public:
	CLONE(CScene);

public:
	CScene();
	virtual ~CScene();
};