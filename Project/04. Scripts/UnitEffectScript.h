#pragma once
#include "YongEngine/Script.h"

class CUnitEffectScript
	: public CScript
{
private:
	Vec3		m_vDir;
	Vec3		m_vMarkPos;
	int			m_iMaxCount;
	int			m_iCurTex;
	float		m_fAccDT;

	wstring		m_szBeforeAnimName;
public:
	virtual int update();
	virtual int lateupdate();

public:
	void Animation();

public:
	CLONE(CUnitEffectScript);
public:
	CUnitEffectScript();
	virtual ~CUnitEffectScript();
};

