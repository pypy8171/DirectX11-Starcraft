#include "stdafx.h"
#include "TileMgr.h"

#include "YongEngine/GameObject.h"

#include "ScriptMgr.h"

CTileMgr::CTileMgr()
	: m_iMinX(0)
	, m_iMaxX(0)
	, m_iMinY(0)
	, m_iMaxY(0)
{
	SetScriptType((UINT)SCRIPT_TYPE::TILEMGR);

}


CTileMgr::~CTileMgr()
{
}

void CTileMgr::SetMinX(int _iIdx)
{
	if (m_iMinX < _iIdx && m_iMinX != 0)
	{
		m_iMinX = _iIdx;
	}
}

void CTileMgr::SetMaxX(int _iIdx)
{
	if (m_iMaxX > _iIdx && m_iMaxX != 0)
	{
		m_iMaxX = _iIdx;
	}
}

void CTileMgr::SetMinY(int _iIdx)
{
	if (m_iMinY < _iIdx && m_iMinY != 0)
	{
		m_iMinY = _iIdx;
	}
}

void CTileMgr::SetMaxY(int _iIdx)
{
	if (m_iMaxY > _iIdx && m_iMaxY != 0)
	{
		m_iMaxY = _iIdx;
	}
}

int CTileMgr::update()
{
	return 0;
}

int CTileMgr::lateupdate()
{
	return 0;
}
