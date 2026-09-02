#pragma once
#include "UnitScript.h"

#include "YongEngine/Script.h"

#include "queue"
class CGameObject;

class CProbeScript
	: public CUnitScript
{
private:
	bool		m_bSetChapter;
	bool		m_bHoldMineral;
	bool		m_bHoldGas;
	bool		m_bAtar;
	bool		m_bBacktoResource;
	bool		m_bAtt;

	Vec3		m_vBeforePos;
	Vec3		m_vMiningPos;
	Vec3		m_vProbeDir;
	
	CGameObject*	m_pMineralObj;
	CGameObject*	m_pTargetObj;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void Key();
	void UIBtn();

public:
	void Mining();
	void BacktoNexus();
	void BacktoMineral();
	void BacktoGas();

public:
	void SetMining(bool _bool) { m_bAtt = _bool; }
	bool& GetMining() { return m_bAtt; }

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	CLONE(CProbeScript);

public:
	CProbeScript();
	virtual ~CProbeScript();
};

