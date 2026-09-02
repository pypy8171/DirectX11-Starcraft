#include "ShaderMgr.h"

#include "Shader.h"
#include "BlendState.h"
#include "RenderMgr.h"

CShaderMgr::CShaderMgr()
{
}


CShaderMgr::~CShaderMgr()
{
	Safe_Delete_Map(m_mapShader);
}


void CShaderMgr::init()
{
	CShader* pShader = NULL;

	//==============
	// Color Shader
	//==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"std.fx", "VS_Color", "vs_5_0");
	pShader->CreatePixelShader(L"std.fx", "PS_Color", "ps_5_0");
	AddShader(L"ColorShader", pShader);

	//================
	// Collider Shader
	//================
	pShader = new CShader;
	pShader->CreateVertexShader(L"std.fx", "VS_Collider", "vs_5_0");
	pShader->CreatePixelShader(L"std.fx", "PS_Collider", "ps_5_0");

	pShader->AddShaderParam(L"Collision", SHADER_PARAM::INT_0);

	AddShader(L"ColliderShader", pShader);

	//==============
	// Std 2D Shader
	//==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"std.fx", "VS_Std2D", "vs_5_0");
	pShader->CreatePixelShader(L"std.fx", "PS_Std2D", "ps_5_0");

	// Shader param Description
	pShader->AddShaderParam(L"Diffuse Texture", SHADER_PARAM::TEX_0);

	// Blend State Setting
	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));

	AddShader(L"Std2DShader", pShader);

	//==============
	// Unit Shader
	//==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"std.fx", "VS_Unit", "vs_5_0");
	pShader->CreatePixelShader(L"std.fx", "PS_Unit", "ps_5_0");

	// Shader param Description
	pShader->AddShaderParam(L"Diffuse Texture", SHADER_PARAM::TEX_0);

	// Blend State Setting
	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));

	AddShader(L"UnitShader", pShader);

	//==============
	// Grid 2D Shader
	//==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"std.fx", "VS_GridCollider", "vs_5_0");
	pShader->CreatePixelShader(L"std.fx", "PS_GridCollider", "ps_5_0");

	// Shader param Description
	pShader->AddShaderParam(L"Diffuse Texture", SHADER_PARAM::TEX_0);

	// Blend State Setting
	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));

	AddShader(L"StdGrid2DShader", pShader);

	//==============
	// SkyBox Shader
	//==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"skybox.fx", "VS_SkyBox", "vs_5_0");
	pShader->CreatePixelShader(L"skybox.fx", "PS_SkyBox", "ps_5_0");

	// Rasterizer 
	// 포폴땐 NONE으로 바꿔야 함
	pShader->SetRSType(RASTERIZER_TYPE::CULL_FRONT);

	// DepthStencil State
	pShader->SetDepthStencilState(CRenderMgr::GetInst()->GetDepthStencilState(DEPTH_STENCIL_TYPE::LESS_EQUAL));

	// Shader param Description
	pShader->AddShaderParam(L"SkyBox Texture", SHADER_PARAM::TEX_0);

	AddShader(L"SkyBoxShader", pShader);

	//==============
	// TEST Shader
	//==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"test.fx", "VS_TEST", "vs_5_0");
	pShader->CreatePixelShader(L"test.fx", "PS_TEST", "ps_5_0");

	// Blend State Setting
	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));

	// 포폴땐 NONE으로 바꿔야 함
	//pShader->SetRSType(RASTERIZER_TYPE::CULL_FRONT);
	// Shader param Description

	pShader->AddShaderParam(L"Diffuse Texture", SHADER_PARAM::TEX_0);

	AddShader(L"TestShader", pShader);

}

void CShaderMgr::AddShader(const wstring & _strKey, CShader * _pShader)
{
	assert(m_mapShader.end() == m_mapShader.find(_strKey) && "no key");
	_pShader->SetName(_strKey);
	m_mapShader.insert(make_pair(_strKey, _pShader));
}

CShader * CShaderMgr::FindShader(const wstring & _strKey)
{
	map<wstring, CShader*>::iterator iter = m_mapShader.find(_strKey);
	assert(m_mapShader.end() != iter && "m_mapShader.end");
	return iter->second;
}


//// 쉐이더 만들기
//pShader = new CShader;
//pShader->CreateVertexShader(L"std.fx", "VS_Color", "vs_5_0");
//pShader->CreatePixelShader(L"std.fx", "PS_Color", "ps_5_0");
//
//// Shader param Description // 모든 시점에 전달.shaderresourceview 가 포인터를 참조하므로 비용이 거의 없을 것이라 추측.
//pShader->AddShaderParam(L"Diffuse Texture", SHADER_PARAM::TEX_0);// | (비트 연산하면 시점 두개를 전달하는 것)
//pShader->AddShaderParam(L"Black and White", SHADER_PARAM::INT_0);
//
//// Blend State Setting
//pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
//
//AddShader(L"ColorShader", pShader);