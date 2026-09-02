#pragma once
#include "atlstr.h"
#include "YongEngine/Script.h"
#include "queue"

class CGameObject;

class CBuildingScript
	: public CScript
{
private:
	bool		m_bBuildComplete;
	bool		m_bCreated;
	bool		m_bKeyComplete;
	float		m_fAccDT;

	CString		m_strKey;

	bool		m_bSetChapter;
	Vec3		m_vInstanciatedPos;

	bool		m_bProduce;
	bool		m_bProduceOut;

	queue<CPrefab*>			m_pClickedPrefab;
	CBuildingScript*			m_pMyself;

	int			m_iBuildingCount;

	int			m_iShield;
	int			m_iMaxShield;
	int			m_iHp;
	int			m_iMaxHp;
	int			m_iMineralCost;
	int			m_iGasCost;

	bool		m_bExplosion;
	float		m_fAccExplosionDT;

	CGameObject*	m_pOwner;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void Animation();
	void ProduceUnit();

public:
	void SetProduce(bool _bProduce) { m_bProduce = _bProduce; }
	bool& GetProduce() { return m_bProduce; }

	void SetProduceOut(bool _bProduceOut) { m_bProduceOut = _bProduceOut; }
	bool& GetProduceOut() { return m_bProduceOut; }

	bool& GetBuildComplete() { return m_bBuildComplete; }

	bool& GetExplosion() { return m_bExplosion; }

	void SetOwner(CGameObject* pOwner) { m_pOwner = pOwner; }
	CGameObject* GetOwner() { return m_pOwner; }

public:
	void AddClickedPrefab(CPrefab* _pObj) { if (m_pClickedPrefab.size()<5)m_pClickedPrefab.push(_pObj); }
	void PopFirstPrefab() { m_pClickedPrefab.pop(); }

	queue<CPrefab*>& GetListPrefab() { return m_pClickedPrefab; }

public:
	void SetBuildingHp(int _i) { m_iHp = _i; }
	int& GetBuildingHp() { return m_iHp; }

	void SetBuildingShield(int _i) { m_iShield = _i; }
	int& GetBuildingShield() { return m_iShield; }

	void SetMineralCost(int _i) { m_iMineralCost = _i; }
	int& GetMineralCost() { return m_iMineralCost; }

	void SetGasCost(int _i) { m_iGasCost = _i; }
	int& GetGasCost() { return m_iGasCost; }

	void SetHp(int _i) { m_iHp -= _i; }
	void SetShield(int _i) { m_iShield -= _i; }

	void SetMaxHp(int _i) { m_iMaxHp = _i; }
	int& GetMaxHp() { return m_iMaxHp; }

	void SetMaxShield(int _i) { m_iShield = _i; }
	int& GetMaxShield() { return m_iShield; }

public:
	void SetBuildTree();

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CLONE(CBuildingScript);

public:
	CBuildingScript();
	virtual ~CBuildingScript();
};