#pragma once
#include "YongEngine/Script.h"

class CGameObject;
class CTexture;

class CSeclectScript
	: public CScript
{
private:
	CGameObject * m_pCurSelObject;
	CTexture* m_pTex[10];

public:
	virtual int update();
	void init();

	CLONE(CSeclectScript);

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	CSeclectScript();
	virtual ~CSeclectScript();
};

