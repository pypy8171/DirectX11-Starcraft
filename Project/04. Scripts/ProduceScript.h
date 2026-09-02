#pragma once
#include "atlstr.h"
#include "YongEngine/Script.h"

class CGameObject;
class CMaterial;
class CBuildingScript;

class CProduceScript
	: public CScript
{
private:
	wstring		m_strBeforeTexName;
	CMaterial*	m_pMtrl[5];

	Vec3		m_vInstanciatedPos;
	float		m_fAccDT;

	CGameObject* m_pBeforeObj;

	CBuildingScript* m_pBuildingScript;
public:
	virtual int update();
	virtual int lateupdate();

public:
	void init();
	void Produce();

public:
	CLONE(CProduceScript);
public:
	CProduceScript();
	virtual ~CProduceScript();
};

