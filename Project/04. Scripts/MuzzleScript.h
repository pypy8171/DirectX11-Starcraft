#pragma once
#include "YongEngine/Script.h"
#include "YongEngine/Transform.h"

class CMuzzleScript :
	public CScript
{
private:
	CScript * m_pPlayer;

public:
	virtual int update();

public:
	void Move();

public:
	void SetPlayer(CScript* _pObject) { m_pPlayer = _pObject; }
	const CScript* GetPlayer() { return m_pPlayer; }

public:
	const Vec3& GetMuzzlePos() { return Transform()->GetLocalPos(); }
	const Vec3& GetMuzzleAngle() { return Transform()->GetLocalAngle(); }


public:
	CLONE(CMuzzleScript);

public:
	CMuzzleScript();
	virtual ~CMuzzleScript();
};

