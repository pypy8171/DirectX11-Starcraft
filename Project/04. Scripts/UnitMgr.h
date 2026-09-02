#pragma once
#include "SingleTonScript.h"
#include "queue"

class CUnitMgr
	: public CSingleTonScript<CUnitMgr>
{
private:
	vector<Vec2>			m_vecIdx;

	wstring					m_strUnitName;
	CPrefab*				m_pClickedPrefab;
	vector<CGameObject*>	m_vecTargetObj;

	CGameObject*			m_pButtonOwner;
public:
	void SetUnitName(wstring _str) { m_strUnitName = _str; }
	void SetClickedPrefab(CPrefab* _pObj) {m_pClickedPrefab = _pObj;}

	CPrefab* GetClickedPrefab() { return m_pClickedPrefab; }
	wstring& GetUnitName() { return m_strUnitName; }

	void SetButtonOwner(CGameObject* pGameObject) { m_pButtonOwner = pGameObject; }
	CGameObject* GetButtonOwner() { return m_pButtonOwner; }

	void AddIdx(Vec2 _vec) { m_vecIdx.push_back(_vec); }
	vector<Vec2>& GetIdxVec() { return m_vecIdx; }

	void IdxVecClear() { m_vecIdx.clear(); }

public:
	virtual int update();
	virtual int lateupdate();
	vector<CGameObject*> GetTargetObjVec() { return m_vecTargetObj; }


	CLONE(CUnitMgr);

public:
	CUnitMgr();
	virtual ~CUnitMgr();
};

