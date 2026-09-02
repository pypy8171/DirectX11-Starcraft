#pragma once
#include "YongEngine/Script.h"
class CResourceScript :
	public CScript
{
public:
	virtual void awake();
	virtual int update();

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	CLONE(CResourceScript);

public:
	CResourceScript();
	virtual ~CResourceScript();
};

