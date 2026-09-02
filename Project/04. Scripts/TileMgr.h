#pragma once
#include "SingleTonScript.h"
class CTileMgr :
	public CSingleTonScript<CTileMgr>
{
private:
	vector<Vec2>		m_vecTileIdx;

	int					m_iMinX;
	int					m_iMaxX;
	int					m_iMinY;
	int					m_iMaxY;

public:
	void SetTileIdx(Vec2 _vIdx) { m_vecTileIdx.push_back(_vIdx); }
	vector<Vec2>& GetTileIdx() { return m_vecTileIdx; };

	void SetMinX(int _iIdx);
	void SetMaxX(int _iIdx);
	void SetMinY(int _iIdx);
	void SetMaxY(int _iIdx);

	int GetMinX() { return m_iMinX; }
	int GetMaxX() { return m_iMaxX; }
	int GetMinY() { return m_iMinY; }
	int GetMaxY() { return m_iMaxY; }

public:
	virtual int update();
	virtual int lateupdate();


public:
	CLONE(CTileMgr);

public:
	CTileMgr();
	virtual ~CTileMgr();
};

