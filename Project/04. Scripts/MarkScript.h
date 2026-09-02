#pragma once
#include "YongEngine/Script.h"
#include "YongEngine/Transform.h"

class CMarkScript :
	public CScript
{
private:
	bool				m_bMarkOn;
	int					m_bCollide;
public:
	virtual int update();

public:
	void Key();

public:

public:
	void SetMarkOn(bool _bMarkOn) { m_bMarkOn = _bMarkOn; }
	const bool& GetMarkOn() { return m_bMarkOn; }

public:
	void SetMarkPos(Vec3 _vMarkPos) { Transform()->SetLocalPos(_vMarkPos);}
	const Vec3& GetMarkPos() { return  Transform()->GetLocalPos(); }


public:
	CLONE(CMarkScript);

public:
	CMarkScript();
	virtual ~CMarkScript();
};

