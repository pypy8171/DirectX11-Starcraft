#include "DepthStencilState.h"

#include "Device.h"

CDepthStencilState::CDepthStencilState()
{
}


CDepthStencilState::~CDepthStencilState()
{
	SAFE_RELEASE(m_pState);
}

void CDepthStencilState::Create(D3D11_DEPTH_STENCIL_DESC * _pDesc)
{
	DEVICE->CreateDepthStencilState(_pDesc, &m_pState);

	if (nullptr == m_pState)
		assert(nullptr);

}

void CDepthStencilState::SetState(UINT _iStencilRef)
{
	CONTEXT->OMSetDepthStencilState(m_pState, _iStencilRef);
}

void CDepthStencilState::SetDefaultState()
{
	CONTEXT->OMSetDepthStencilState(nullptr, 0);
}

