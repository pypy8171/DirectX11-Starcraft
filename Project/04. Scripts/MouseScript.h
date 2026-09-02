#pragma once
#include "YongEngine/Script.h"
class CGameObject;
class CMaterial;

class CMouseScript :
	public CScript
{
private:
	CScript *		m_pMark;
	int				m_bCollide;

	CGameObject*	m_pTargetObj; // 나중ㅇ ㅔ구조 바꿔야 함.
	CGameObject*	m_pBeforeTargetObj;

	Vec3			m_vDragPos;
	bool			m_bDrag;

	CGameObject*	m_pBuildingPrefabObj;
	bool			m_bStructure;

	int				m_iSoundCount;

	CMaterial*		m_pVicMtrl;
public:
	virtual int update();
	virtual void awake();

	void init();

public:
	void SetMark(CScript* _pMark) { m_pMark = _pMark; }

	bool& GetStructure() { return m_bStructure; }

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	CGameObject * GetTargetObj() { return m_pTargetObj; }
	void SetTargetObj(CGameObject* _pGameObject) { m_pTargetObj = _pGameObject; }

	bool& GetDrag() { return m_bDrag; }

	void Drag();

public:
	CLONE(CMouseScript);

public:
	CMouseScript();
	virtual ~CMouseScript();
};

