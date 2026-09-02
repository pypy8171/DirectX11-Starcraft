#pragma once
#include "Component.h"
class CLight :
	public CComponent
{
private:
	tLightInfo		m_info;


public:
	virtual int update();
	virtual int finalupdate();

public:
	void SetLightType(LIGHT_TYPE _eType) { m_info.iType = (UINT)_eType; }
	LIGHT_TYPE GetLightType() { return (LIGHT_TYPE)m_info.iType; }

	void SetLightColor(const tLightCol& _tCol) { m_info.tCol = _tCol; }
	tLightCol& GetLightColor() { return m_info.tCol; }

	void SetLightRange(float _fRange) { m_info.fDist = _fRange; }
	float GetLightRange() { return m_info.fDist; }

public:
	CLONE(CLight);

public:
	CLight();
	virtual ~CLight();
};
