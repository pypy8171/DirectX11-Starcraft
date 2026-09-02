#pragma once
#include "Script.h"
#include "Transform.h"
#include "Prefab.h"


class CAnimation2D;
class CCollider;

class CPlayerScript :
	public CScript
{
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
	void OnCollisionEnter(const CCollider* _pOther);
	void OnCollision(const CCollider* _pOther);
	void OnCollisionExit(const CCollider* _pOther);

public:
	CLONE(CPlayerScript);

public:
	CPlayerScript();
	virtual ~CPlayerScript();
};