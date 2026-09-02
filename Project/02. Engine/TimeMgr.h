#pragma once
#include "global.h"

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llOldCount;

	double			m_dt;	// 1프레임 시간
	UINT			m_iFPS;

	float           m_fAccTime; // 누적시간

public:
	float DeltaTime() { return (float)m_dt; }
	UINT FPS() { return m_iFPS; }

public:
	void init();
	int update();
	void render(HDC _dc);
};

