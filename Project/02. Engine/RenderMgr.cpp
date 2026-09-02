#include "RenderMgr.h"

#include "BlendState.h"
#include "DepthStencilState.h"

#include "SceneMgr.h"
#include "Device.h"
#include "ConstBuffer.h"

CRenderMgr::CRenderMgr()
	: m_arrBS{}
	, m_arrDS{}
{
}


CRenderMgr::~CRenderMgr()
{
	Safe_Delete_Array(m_arrBS);
	Safe_Delete_Array(m_arrDS);
}

void CRenderMgr::init()
{
	// Blend State »ý¼º
	CreateBlendState();

	// Depth Stencil State »ý¼º
	CreateDepthStencilState();
}

void CRenderMgr::render()
{

	// LightCount
	//int iLightCount = m_vecLight.size();
	//if (iLightCount > 10)
	//	iLightCount = 10;

	//g_global.iLightCount = iLightCount;

	// Global Value
	static CConstBuffer* pBuff = CDevice::GetInst()->FindCBuffer(L"Global");
	pBuff->UpdateData(&g_global, sizeof(tGlobalValue));
	pBuff->UpdateRegisterAll();

	//// LightInfo
	//static CConstBuffer* pLightBuff = CDevice::GetInst()->FindCBuffer(L"LightInfo");

	//pLightBuff->UpdateData(&m_vecLight[0], sizeof(tLightInfo) * iLightCount);
	//pLightBuff->UpdateRegisterAll();

	CSceneMgr::GetInst()->render();


	// ±¤¿øÁ¤º¸ ÇØÁ¦
	//m_vecLight.clear();
}

void CRenderMgr::CreateBlendState()
{
	D3D11_BLEND_DESC tDesc = {};

	tDesc.AlphaToCoverageEnable = false; // ³ª¹µ°¡Áö, ³ª¹µÀÙ
	tDesc.IndependentBlendEnable = false; // µ¶¸³(·»´õ Å¸°Ù °¹¼ö ¸¸Å­ ¼³Á¤ °¡´É)

	tDesc.RenderTarget[0].BlendEnable = true;
	tDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; // È¥ÇÕ ¹æ½Ä
	tDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA; // source °è¼ö
	tDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA; // dest °è¼ö

	tDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	tDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	tDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
	tDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

	m_arrBS[(UINT)BLEND_TYPE::ALPHABLEND] = new CBlendState;
	m_arrBS[(UINT)BLEND_TYPE::ALPHABLEND]->Create(&tDesc);
}

void CRenderMgr::CreateDepthStencilState()
{
	CDepthStencilState* pState = nullptr;

	// LESS_EQUAL 
	D3D11_DEPTH_STENCIL_DESC tDesc = {};

	tDesc.DepthEnable = true;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
	tDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	tDesc.StencilEnable = false;

	pState = new CDepthStencilState;
	pState->Create(&tDesc);

	m_arrDS[(UINT)DEPTH_STENCIL_TYPE::LESS_EQUAL] = pState;
}
