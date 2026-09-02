#pragma once
#include "SingleTonScript.h"

class CGameObject;
class CPrefab;

class CBuildingMgr :
	public CSingleTonScript<CBuildingMgr>
{
private:
	wstring			m_strStructureName;
	CPrefab*		m_pClickedPrefab;

	vector<Vec3>	m_vecStartingPoint;
	int				m_arrBuildLevel[12];

	bool			m_bBuildAvailable;
	bool			m_bFinish;
	float			m_fDT;
public:
	virtual int update();
	virtual int lateupdate();
public:
	void SetStructureName(wstring _str) { m_strStructureName = _str; }
	void SetClickedPrefab(CPrefab* _pObj) { m_pClickedPrefab = _pObj; }

	wstring& GetStructureName() { return m_strStructureName; }
	CPrefab* GetClickedPrefab() { return m_pClickedPrefab; }

	void SetSTartingPoint(Vec3 _vStartingPoint) { m_vecStartingPoint.push_back(_vStartingPoint); }
	vector<Vec3>& GetStartingPoint() { return m_vecStartingPoint; }
	//CPrefab* GetTargetPrefab(const wstring& _StructureName){ return CResMgr::GetInst()->Load<CPrefab>(_StructureName); }
public:
	void SetBuildAvailable(bool _bool) { m_bBuildAvailable = _bool; }
	bool& GetBuildAvailable() { return m_bBuildAvailable; }

public:
	void SetBuildLevel(UINT _eLevel, bool _bool) { m_arrBuildLevel[_eLevel] = _bool; }
	int& GetBuildLevel(UINT _eLevel) { return m_arrBuildLevel[_eLevel]; }

	CLONE(CBuildingMgr);
public:
	CBuildingMgr();
	virtual ~CBuildingMgr();
};

