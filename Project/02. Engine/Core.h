#pragma once

#include "global.h"

class CCore
{
	SINGLE(CCore);

private:
	VTX arrVTX[8];
	IDX32 arrIdx[12];

	HWND		m_hWnd;

private:
	// Matrix	m_Matrix;
	float		m_fRotateAngle;
	Vec3		m_vMovePos;
	Vec3		m_vMoveAngle;

	tResolution		m_vResolution;


public:
	void init(HWND _hWnd, const tResolution& _res, bool _bWindow = true);
	int progress();

	const tResolution& GetResoultion() { return m_vResolution; }

public:
	void ProgressPipeline();

private:
	int update();
	void render();
};

