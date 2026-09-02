#pragma once
#include "SingleTonScript.h"



class CSkillMgr :
	public CSingleTonScript<CSkillMgr>
{
private:
	SKILL		m_eSkill;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void SetSkill(SKILL _eSkill) { m_eSkill = _eSkill; }
	SKILL& GetSkill() { return m_eSkill; }


public:
	CLONE(CSkillMgr);

public:
	CSkillMgr();
	virtual ~CSkillMgr();
};

