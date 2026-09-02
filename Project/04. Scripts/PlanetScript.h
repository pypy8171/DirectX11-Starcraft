#pragma once
#include "YongEngine/Script.h"

class CPlanetScript
	: public CScript
{
private:
	float	m_fRotatingSpeed; // 자전 // 자기가 도는거
	float	m_fRevolutionSpeed; // 공전 // 다른행성 기준으로 도는거

public:
	virtual int update();
	virtual int lateupdate();

public:
	CLONE(CPlanetScript);

public:
	CPlanetScript();
	virtual ~CPlanetScript();
};

