#pragma once
#include "SingleTonScript.h"

class CGameObject;

class CNumberMgr :
	public CSingleTonScript<CNumberMgr>
{
private:
	int				m_iNum;
	bool			m_bHpRequest;
	bool			m_bShieldRequest;
	bool			m_bMpRequest;
	bool			m_bMineralRequest;
	bool			m_bGasRequest;

	CGameObject*	m_pGameObject;

public:
	virtual int update();
	virtual int lateupdate();
	void init();

	void Normal();
	void Shield();
	void Mp();
	
public:
	void SetObject(CGameObject* pGameObject) { m_pGameObject = pGameObject; }

	void SetHpRequest(bool _bRequest) { m_bHpRequest = _bRequest; }
	void SetShieldRequest(bool _bRequest) { m_bShieldRequest = _bRequest; }
	void SetMpRequest(bool _bRequest) { m_bMpRequest = _bRequest; }
	void SetMineralRequest(bool _bRequest) { m_bMineralRequest = _bRequest; }
	void SetGasRequest(bool _bRequest) { m_bGasRequest = _bRequest; }

public:
	CLONE(CNumberMgr);

public:
	CNumberMgr();
	virtual ~CNumberMgr();
};

