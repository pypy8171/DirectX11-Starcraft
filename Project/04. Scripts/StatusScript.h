#pragma once

#include "YongEngine/Script.h"

class CGameObject;
class CMaterial;

class CStatusScript
	: public CScript
{
private:
	wstring		m_strBeforeTexName;
	CMaterial*	m_pMtrl;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void init();

public:
	void NormalStatus();
	void ProduceStatus();

public:
	CLONE(CStatusScript);


public:
	CStatusScript();
	virtual ~CStatusScript();
};

