#pragma once
#include "Entity.h"
class CDepthStencilState :
	public CEntity
{
private:
	ID3D11DepthStencilState * m_pState;

public:
	int update() { return 0; }
	void Create(D3D11_DEPTH_STENCIL_DESC* _pDesc);
	void SetState(UINT _iStencilRef = 0);
	static void SetDefaultState();

public:
	CLONE_DISABLE(CDepthStencilState);

public:
	CDepthStencilState();
	virtual ~CDepthStencilState();
};

