#pragma once
#include "YongEngine/Script.h"

class CGameObject;

class CWireFrameScript
	: public CScript
{
private:
	int			m_iWireFrameIdx;
	bool		m_bMulti;

	static int	m_iWireIdx;

public:
	virtual int update();
	virtual int lateupdate();

public:
	void Multi(bool _bMulti) { m_bMulti = _bMulti; }
	void SetWireFrameIdx(int _iIdx) { m_iWireFrameIdx = _iIdx; }
	int& GetWireFrameIdx() { return m_iWireFrameIdx; }

public:
	CLONE(CWireFrameScript);


public:
	CWireFrameScript();
	//CWireFrameScript(const CWireFrameScript& _other);

	~CWireFrameScript();
};

