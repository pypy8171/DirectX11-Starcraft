#pragma once
#include "YongEngine/Script.h"
#include "queue"


class CGameObject;
class CMaterial;
struct tNode
{
	int iCurIdxX = 0;
	int iCurIdxY = 0;

	int iParentIdxX = 0;
	int iParentIdxY = 0;

	int fFrom = 0;
	int fDest = 0;
	int fFinal = 0;

	bool bClosed = false;
	bool bOpened = false;
	bool bObstacle = false;
};

struct cmp {
	bool operator()(tNode* t, tNode* u) {
		return t->fFinal > u->fFinal;
	}
};


class CUnitScript
	: public CScript
{
private:
	CMaterial * m_pMtrl;

protected:
	int			m_iShield;
	int			m_iMaxShield;
	int			m_iHp;
	int			m_iMaxHp;
	int			m_iGroundAtt;
	int			m_iAirAtt;
	int			m_iAttSpeed;
	int			m_iRange;
	float		m_fSpeed;
	float		m_fStopSpeed;
	float		m_fAccelator;
	float		m_fAccelatorDT;

	int			m_iMineralCost;
	int			m_iGasCost;
	bool		m_bCycle;

	float		m_fAnimDT;

	float		m_fAttDT;
	bool		m_bAttackOn;
	float		m_fFloatPos;
	bool		m_bFloatUp;

	float		m_fRecallDT;

protected:
	Vec3		m_vDir;
	Vec3		m_vMarkPos;
	int			m_iMaxCount;
	int			m_iBeforeMaxCount;
	int			m_iCurTex;
	float		m_fAccDT;

	wstring		m_szBeforeAnimName;
	UNIT_TYPE	m_eUnitType;

	bool		m_bAlly;
	bool		m_bWait;

	bool		m_bReadyToAtt;
	bool		m_bStartToFind;

private:
	priority_queue<tNode*, vector<tNode*>, cmp>	m_openlist;
	list<tNode*>								m_listPath;
	tNode										m_arrNode[100][100];

public:
	// 출발 도착 지점
	int		m_iStartX;
	int		m_iStartY;

	int		m_iEndX;
	int		m_iEndY;

	list<Vec3>	m_vecNodePos;

	Vec3		m_vBeforeNodePos;

	Vec3		m_vLaterPos;
	Vec3		m_vBeforePos;
	Vec3		m_vArmyBeforePos;
	Vec3		m_vAccPos;
	Vec3		m_vStructurePos;

	Vec3		m_vDestPos;

	bool		m_bStart;

private:
	bool		m_bSetChapter;

	float		m_fAccFlozenDT;
	Vec3		m_vRecallCastingPos;

	bool		m_bFrozen;
	bool		m_bDead;
	bool		m_bFinish;
	bool		m_bHold;
	bool		m_bFix;
	bool		m_bBallOn;
	bool		m_bFrozenReset;

	bool		m_bRequestHpUI;

	int			m_iSoundCount;

public:
	virtual int update();
	virtual int lateupdate();

public:
	virtual void GroundUnitAnimation();
	virtual void AirUnitAnimation();
	virtual void Key() {};

	void SetBtnUI();
	void Move();
	void MoveByAstar();
	void InputKey();

public:
	void SetUnitType(UNIT_TYPE _eUnitType) { m_eUnitType = _eUnitType; }
	const UNIT_TYPE& GetUnitType() { return m_eUnitType; }

	void SetUnitSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float& GetUnitSpeed() { return m_fSpeed; }

	void SetUnitHp(int _iHp) { m_iHp = _iHp; }
	int& GetUnitHp() { return m_iHp; }

	void SetUnitShield(int _iHp) { m_iShield = _iHp; }
	int& GetUnitShield() { return m_iShield; }

	void SetMineralCost(int _i) { m_iMineralCost = _i; }
	int& GetMineralCost() { return m_iMineralCost; }

	void SetGasCost(int _i) { m_iGasCost = _i; }
	int& GetGasCost() { return m_iGasCost; }

	void SetDir(Vec3 _vDir) {m_vDir = _vDir;}

	Vec3& GetAnimDir() { return m_vDir; }

	void BuildStructure();
	void MakeAlly();

public:
	void Frozen();
	void Recall();
	void Storm();
	void Die();

	void ArbiterRad();

	void SetDie(bool _bool) { m_bDead = _bool; }
	bool& GetDie() { return m_bDead; }

	void SetCycle(bool _bool) { m_bCycle = _bool; }
	bool& GetCycle() { return m_bCycle; }

	void SetStartToFind(bool _bool) { m_bStartToFind = _bool; }
	bool& GetStartToFind() {return m_bStartToFind;}

	void SetReadyToAtt(bool _bool) { m_bReadyToAtt = _bool; }
	bool& GetReadyToAtt() { return m_bReadyToAtt; }

	bool& AttackOn() { return m_bAttackOn; }

	bool& BallOn() {return m_bBallOn;}
public:
	void Wait(bool _bwait) { m_bWait = _bwait; }
	bool& GetWait() { return m_bWait; }

public:
	void AstarKey();
	void Astar();
	void InitNode();
	void FindPath();
	void CalCost(int _iX, int _iY, int _iOrgX, int _iOrgY);
	void AddOpenlist(int _iX, int _iY, int _iOrgX, int _iOrgY);
	void MoveToDest();
	void Reset();


public:
	void FindOpponent();
	void Attack();


public:
	void SetHp(int _iDamage) { m_iHp -= _iDamage; }
	void SetDamage(int _iDamage) { m_iHp -= _iDamage; }
	int& GetHp() { return m_iHp; }

	void SetMaxHp(int _iMaxHp) { m_iMaxHp = _iMaxHp; }
	int& GetMaxHp() { return m_iMaxHp; }

	void SetShield(int _iDamage) { m_iShield -= _iDamage; }
	int& GetShield() { return m_iShield; }


	void SetMaxShield(int _iMaxHp) { m_iMaxShield = _iMaxHp; }
	int& GetMaxShield() { return m_iMaxShield; }

	void SetUnitGroundAtt(int _iGroundAtt) { m_iGroundAtt = _iGroundAtt; }
	void SetUnitAirAtt(int _iAirAtt) { m_iAirAtt = _iAirAtt; }

	int& GetGroundAttDamage() { return m_iGroundAtt; }
	int& GetAirAttDamage() { return m_iAirAtt; }

	void SetUnitRange(int _iRange) { m_iRange = _iRange; }
	int& GetRange() { return m_iRange; }

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CLONE(CUnitScript);


public:
	CUnitScript();
	virtual ~CUnitScript();
};

