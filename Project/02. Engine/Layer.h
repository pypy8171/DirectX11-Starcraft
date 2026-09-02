#pragma once
#include "Entity.h" // 레이어 = 게임 오브젝트

class CGameObject;
class CCollider;

class CLayer :
	public CEntity
{

private:
	vector<CGameObject*>		m_pParentList;
	vector<CGameObject*>		m_AllObject;
	list<CGameObject*>			m_pDeleteList;
	int							m_iLayerIdx;

public:
	virtual void awake();
	virtual void start();
	virtual int update();
	virtual int lateupdate();
	virtual int finalupdate();

	void render();

public:
	void DeleteGameObject(CGameObject* _pObj);

public:
	void SetIdx(UINT _iIdx) { m_iLayerIdx = _iIdx; }
	UINT GetIdx() { return m_iLayerIdx; }
	//void AddGameObject(CGameObject* _pObj);
	void AddGameObject(CGameObject* _pObj, bool _bAll = true/*자식 오브젝트도 전부 옮겨올지 아닌지*/);

	void PopParentObj(CGameObject* _pObj);

	vector<CGameObject*>& GetObjVec() { return m_pParentList; }

	void RegisterObj(CGameObject* _pObj) { m_AllObject.push_back(_pObj); };


public:
	CLONE(CLayer);

public:
	CLayer();
	virtual ~CLayer();
};

