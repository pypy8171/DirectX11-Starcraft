#pragma once
#include "Script.h"
#include "Transform.h"

class CMonsterScript :
	public CScript
{
private:
	MONSTER_DIR		m_eMonsterDir;

	float			m_fSpeed;
	int				m_bCollide;

public:
	virtual int update();

public:
	void Move();

public:
	void SetMonsterDir(MONSTER_DIR _eMonsterDir) { m_eMonsterDir = _eMonsterDir; }
	const MONSTER_DIR& GetMonsterDir() { return m_eMonsterDir; }

public:
	void SetMonsterPos(Vec3 _vMarkPos) { Transform()->SetLocalPos(_vMarkPos); }
	const Vec3& GetMonsterPos() { return  Transform()->GetLocalPos(); }

public:
	void OnCollisionEnter(const CCollider* _pOther);
	void OnCollision(const CCollider* _pOther);
	void OnCollisionExit(const CCollider* _pOther);

public:
	CLONE(CMonsterScript);

public:
	CMonsterScript();
	virtual ~CMonsterScript();
};

