#pragma once

#include "global.h"

class CEntity
{
private:
	wstring			m_strName;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	virtual void start(){};
	virtual void awake(){};

	virtual int update() = 0;
	virtual int lateupdate() { return 0; }
	virtual int finalupdate() { return 0; }

	virtual void UpdateData() {}

public:
	virtual CEntity* Clone() = 0;

public:
	CEntity();
	virtual ~CEntity();
};

