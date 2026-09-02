#pragma once
#include "YongEngine/Script.h"

class CSkillScript
	: public CScript
{
private:
	bool		m_bSkillOn;
	Vec3		m_vSkillPos;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void Animation();

public:
	CLONE(CSkillScript);

public:
	CSkillScript();
	~CSkillScript();
};

