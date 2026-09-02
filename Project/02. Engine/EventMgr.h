#pragma once

#include "global.h"

class CGameObject;

class CEventMgr
{
private:
	vector<tEvent>				m_vecEvent;
	vector<CGameObject*>		m_vecDeleteObj;
	vector<tEvent>				m_vecEventCopy;

public:
	int update();

public:
	void AddEvent(const tEvent& _eEvent) { m_vecEvent.push_back(_eEvent); }
	void Execute(const tEvent& _eEvent);

public:
	vector<tEvent>& GetEventList() { return m_vecEventCopy; }

public:
	void DeleteObj();

public:
	SINGLE(CEventMgr);
};

