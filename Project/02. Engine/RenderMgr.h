#pragma once
// 렌더링 담당 매니져
#include "global.h"

class CBlendState;
class CDepthStencilState;
class CLight;

class CRenderMgr
{
	SINGLE(CRenderMgr);
private:
	CBlendState *		m_arrBS[(UINT)BLEND_TYPE::END];
	CDepthStencilState* m_arrDS[(UINT)DEPTH_STENCIL_TYPE::END];

	vector<tLightInfo>	m_vecLight;

public:
	void init();
	void render();
	
public:
	void RegisterLight(const tLightInfo& _tInfo) { m_vecLight.push_back(_tInfo); }

public:
	CBlendState * GetBlendState(BLEND_TYPE _eType) { return m_arrBS[(UINT)_eType]; }
	CDepthStencilState* GetDepthStencilState(DEPTH_STENCIL_TYPE _eType) { return m_arrDS[(UINT)_eType]; }

public:
	void CreateBlendState();
	void CreateDepthStencilState();
};

