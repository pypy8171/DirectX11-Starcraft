#pragma once
#include "YongEngine/Script.h"
#include "YongEngine/Transform.h"
#include "YongEngine/Prefab.h"
//#include "YongEngine/Material.h"

class CAnimation2D;
class CCollider;

class CPlayerScript :
	public CScript
{

//private:
//	Ptr<CMaterial>  m_pSharedMtrl;
//	Ptr<CMaterial>	m_pCloneMtrl;

private:
	CPrefab*	m_pBullet;

	CScript *	m_pMark;
	CScript *	m_pMonster;
	CScript*	m_pMuzzle;

	BULLET_TYPE	m_eBulletType;

	bool		m_bTarget;
	int			m_bCollide;
	
	int			m_iCurTex;
	CAnimation2D* m_pAnimation2D;

	int			m_iMaxCount;
	wstring		m_szBeforeAnimName;

	UNIT_STATUS	m_eUnitStatus;
	float		m_fAccDT;

	Vec3		m_vMarkPos;
	Vec3		m_vDir;

public:
	virtual int update();
	virtual void awake();

public:
	void MoveDir();
	void Animation();
	void Key();

public:
	void SetMark(CScript* _pMark) { m_pMark = _pMark; }
	void SetMonster(CScript* _pMonster) { m_pMonster = _pMonster; }
	void SetMuzzle(CScript* _pMuzzle) { m_pMuzzle = _pMuzzle; }

public:
	const Vec3& GetPlayerPos() { return Transform()->GetLocalPos(); }
	const Vec3& GetPlayerAngle() { return Transform()->GetLocalAngle(); }

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	CLONE(CPlayerScript);

public:
	CPlayerScript();
	virtual ~CPlayerScript();
};