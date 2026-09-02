#pragma once

#include "YongEngine/Script.h"

class CGameObject;
class CMaterial;

class CNumberScript
	: public CScript
{
private:
	NUMBER_TYPE		m_eNumberType;
	int				m_iNum;

	bool			m_bHpUI;
	bool			m_bShieldUI;
	bool			m_bMineralUI;
	bool			m_bGasUI;

	CMaterial*		m_pHpMtrl[3];
	CMaterial*		m_pMaxHpMtrl[3];

	CMaterial*		m_pShieldMtrl[3];
	CMaterial*		m_pMaxShieldMtrl[3];

	CMaterial*		m_pMineralMtrl[5];
	CMaterial*		m_pGasMtrl[5];

	CGameObject*	m_pGameObject;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void Hp();
	void Shield();
	void Mineral();
	void Gas();

	void ShowHp();
	void ShowShield();
	void ShowMineral();
	void ShowGas();

public:
	void SetNum(int _iNum) {m_iNum = _iNum;	}
	void SetNumberType(NUMBER_TYPE _eNumberType) { m_eNumberType = _eNumberType; }
	void SetObject(CGameObject* pGameObject) { m_pGameObject = pGameObject; }

public:
	CLONE(CNumberScript);
public:
	CNumberScript();
	~CNumberScript();
};

