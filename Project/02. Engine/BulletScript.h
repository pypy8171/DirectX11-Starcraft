#pragma once
#include "Script.h"

class CGameObject;

class CBulletScript :
	public CScript
{
private:
	Vec3		m_vDest;
	Vec3		m_vDirVec;
	Vec3		m_vSrc;

	Vec3		m_vPlayerAngle;
	BULLET_TYPE	m_eBulletType;
		
	CGameObject*	m_pGameObject;

	bool		m_bGuidedOn;
	bool		m_bDelete;
	int			m_bCollide;
public:
	virtual int update();
	virtual int lateupdate();

public:
	void Move();

public:
	void SetPlayerAngle(Vec3 _vAngle) { m_vPlayerAngle = _vAngle; }
	const Vec3& GetPlayerAngle() { return m_vPlayerAngle; }

	void SetDestPos(Vec3 _vDest) { m_vDest = _vDest; }
	const Vec3& GetDestPos() { return m_vDest; }

	void SetSrcPos(Vec3 _vSrc) { m_vSrc = _vSrc; }
	const Vec3& GetSrcPos() { return m_vSrc; }

	void SetDirVec(Vec3 _vDirVec) { m_vDirVec = _vDirVec; }
	const Vec3& GetDirVec() { return m_vDirVec; }

public:
	void SetDelete(bool _bDelete) { m_bDelete = _bDelete; }
	const bool& GetDelete() { return m_bDelete; }

	void SetGuided(bool _bGuidedOn) { m_bGuidedOn = _bGuidedOn; }
	const bool& GetGuided() { return m_bGuidedOn; }

	void SetBulletType(BULLET_TYPE _eType) { m_eBulletType = _eType; }
	const BULLET_TYPE& GetBulletType() { return m_eBulletType; }

public:
	void SetBullet(CGameObject* _pObject) { m_pGameObject = _pObject; }
	CGameObject* GetBullet() { return m_pGameObject; }

public:
	void DeleteBulletOp();


public:
	void OnCollisionEnter(const CCollider* _pOther);
	void OnCollision(const CCollider* _pOther);
	void OnCollisionExit(const CCollider* _pOther);

public:
	CLONE(CBulletScript);

public:
	CBulletScript();
	virtual ~CBulletScript();
};

