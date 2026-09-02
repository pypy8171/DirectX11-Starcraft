#pragma once
#include "YongEngine/Script.h"

class CArchonEffectScript
	: public CScript
{
private:
	wstring m_szBeforeAnimName;
	int		m_iMaxCount;

	Vec3	m_vPos;
	float	m_fDelayDT;
	float	m_fShockDT;

	float	m_fDraAttDT;
	bool	m_bAttack;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void Ball();
	void Splash();

public:
	void Animation();
	void BallAnimation();
	void AttAnim();

public:
	CLONE(CArchonEffectScript);

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	CArchonEffectScript();
	~CArchonEffectScript();
};

