#include "Device.h"

#include "ConstBuffer.h"

CDevice::CDevice()
	: m_hWnd(NULL)
	, m_pDevice(NULL)
	, m_pContext(NULL)
	, m_iQualityLv(0)
	, m_res{}
	, m_bWindow(true)
	, m_pSwapChain(NULL)
	, m_pDepthStencilTex(NULL)
	, m_pDepthStencilView(NULL)
	, m_pSampler(nullptr)
	, m_arrRSState{}
{
	for (int i = 0; i < RENDERTARGET_NUM; ++i)
	{
		m_pTargetView[i] = NULL;
	}
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pSwapChain);
	for (int i = 0; i < RENDERTARGET_NUM; ++i)
	{
		SAFE_RELEASE(m_pTargetView[i]);
	}
	SAFE_RELEASE(m_pDepthStencilTex);
	SAFE_RELEASE(m_pDepthStencilView);

	Safe_Delete_Map(m_mapCBuff);

	SAFE_RELEASE(m_pSampler);
	for (UINT i = 0; i < (UINT)RASTERIZER_TYPE::END; ++i)
	{
		SAFE_RELEASE(m_arrRSState[i]);
	}

#if defined(DEBUG) | defined(_DEBUG)
	ID3D11Debug* pDebug = nullptr;
	m_pDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&pDebug));

	SAFE_RELEASE(m_pDevice);
	pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	SAFE_RELEASE(pDebug);
#endif
}

int CDevice::init(HWND _hWnd, const tResolution & _res, bool _bWindow)
{
	m_bWindow = _bWindow;
	m_res = _res;
	m_hWnd = _hWnd;

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL eLv;
	if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, iFlag,
		0, 0, D3D11_SDK_VERSION, &m_pDevice, &eLv, &m_pContext)))
	{
		return RET_FAILED;
	}

	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iQualityLv);

	if (m_iQualityLv == 0)
		return RET_FAILED;

	DXGI_SWAP_CHAIN_DESC tSwapDesc = {};

	tSwapDesc.BufferCount = 1; // 버퍼 한개
	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼(텍스쳐) 가 이미지 출력 타겟임을 알림
	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapDesc.BufferDesc.Width = (UINT)_res.x;
	tSwapDesc.BufferDesc.Height = (UINT)_res.y;

	// 주사율
	tSwapDesc.BufferDesc.RefreshRate.Denominator = 1; // 기존 60
	tSwapDesc.BufferDesc.RefreshRate.Numerator = 60; // 기존 1

	// 모니터 
	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // UNSPECIFED -> DEFAULT 값이라 생각하면됨.// 미지정
	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 출력 윈도우 및 창모드 
	tSwapDesc.Windowed = _bWindow;
	tSwapDesc.OutputWindow = m_hWnd;

	// 멀티 샘플 AA 를 위해서 셋팅
	tSwapDesc.SampleDesc.Count = 4;
	tSwapDesc.SampleDesc.Quality = 0;

	// 이전 프레임 이미지를 저장하지 않음
	tSwapDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; // 한 프레임 이전 프레임 버려라

	IDXGIDevice* pDevice = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIFactory* pFactory = NULL;

	// 예외처리 걸어놓고 failed 처리 해야함.
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDevice);
	pDevice->GetAdapter(&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	pFactory->CreateSwapChain(m_pDevice, &tSwapDesc, &m_pSwapChain);

	pDevice->Release();
	pAdapter->Release();
	pFactory->Release();

	//=============
	// CREATE VIEW
	//=============
	// RenderTargerView 만들기
	// 이미 생성되어 있는 Texture를 가져와야 한다.

	ID3D11Texture2D* pTargetTexture = NULL;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pTargetTexture); // 버퍼 꺼내기 랜더 타겟이 가져야 하는 텍스쳐가 얘다.
																					// Getbuffer 행위자체가 레퍼런스 카운트(참조 카운트) 1늘리는 행위이다.
																					// 따라서 바로 제거
	pTargetTexture->Release();

	for (int i = 0; i < RENDERTARGET_NUM; ++i)
	{
		m_pDevice->CreateRenderTargetView(pTargetTexture, NULL, &m_pTargetView[i]);
	}
	// DepthStencilTexture 만들기

	D3D11_TEXTURE2D_DESC tTexDesc = {};

	tTexDesc.Width = (UINT)_res.x;
	tTexDesc.Height = (UINT)_res.y;
	tTexDesc.MipLevels = 1; // 1 의 의미 -> 본체만 생성
	tTexDesc.ArraySize = 1; // 텍스처 배열의 텍스처 수입니다. 범위는 1에서 D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION (2048)까지입니다. 텍스처 큐브 맵의 경우이 값은 6의 배수 ( D3D11_TEXCUBE_ARRAY_SRV 의 NumCube 멤버의 값의 6 배)이며 범위는 6에서 2046 사이입니다. 범위는 실제로 렌더링 장치를 만듭니다. 제한에 대한 자세한 내용은주의를 참조하십시오.
	tTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 픽셀 하나당 4바이트를 사용하겠다. 3바이트는 깊이, 1바이트는 스텐실을 위한 메모리 공간 
													 // 깊이 체크 스텐실 체크 둘 다 함 
													 // 스텐실이란?(미술 기법)  구멍 뚫어놓고 거기만 통과 DEPTH 통과하고 STENCIL도 통과해야 그린다. 
													 // 지정된 영역에만 효과를 주고 싶을때 사용
	tTexDesc.SampleDesc.Count = 4; // 동일해야 함
	tTexDesc.SampleDesc.Quality = 0; // 멀티 샘플 동일한 카운트와 퀄리티

	tTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 용도
	tTexDesc.Usage = D3D11_USAGE_DEFAULT; // 내부적으로 건들일이 없어서 default 옵션

	m_pDevice->CreateTexture2D(&tTexDesc, 0, &m_pDepthStencilTex); // 텍스쳐 나옴

	// DepthStencilView 를 DepthStencilTexture 를 이용해서 만들기
	m_pDevice->CreateDepthStencilView(m_pDepthStencilTex, NULL, &m_pDepthStencilView);

	// 출력 타겟과 깊이 스텐실 타겟을 알린다. 총 8개 가능 dxd11에서는
	//m_pContext->OMSetRenderTargets(1, &m_pTargetView[0], m_pDepthStencilView); // 여러개 넣을라면 m_pTargetView[2] 이런식으로 배열로 만들어야겠다.
	m_pContext->OMSetRenderTargets(RENDERTARGET_NUM, &m_pTargetView[0], m_pDepthStencilView);

	//========
	// 뷰 포트
	//========
	// 윈도우로 출력 이미지가 전송될때, 출력 될 영역을 지정한다.
	// 실제로는 뷰포트까지 감안해서 출력이미지가 완성되고, 윈도우로 이미지가 복사된다.

	D3D11_VIEWPORT tViewPortDesc[RENDERTARGET_NUM] = {};

	for (int i = 0; i < RENDERTARGET_NUM; ++i)
	{
		tViewPortDesc[i].Width = _res.x;
		tViewPortDesc[i].Height = _res.y;
		tViewPortDesc[i].MinDepth = 0.f; // 최소거리 내 눈 바로 앞이라 보면됨. 0 이하는 내 눈 뒤.
		tViewPortDesc[i].MaxDepth = 1.f; // 최대 가시거리
		tViewPortDesc[i].TopLeftX = 0;
		tViewPortDesc[i].TopLeftY = 0;
	}
	
	m_pContext->RSSetViewports(RENDERTARGET_NUM, &tViewPortDesc[0]);

	// 샘플러 디스크립션
	D3D11_SAMPLER_DESC tSamDesc = {};
	tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	tSamDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	DEVICE->CreateSamplerState(&tSamDesc, &m_pSampler);
	CONTEXT->PSSetSamplers(0, 1, &m_pSampler);

	//==================
	// Rasterizer State
	//==================

	m_arrRSState[(UINT)RASTERIZER_TYPE::CULL_BACK] = {};

	D3D11_RASTERIZER_DESC tRSDesc = {};
	tRSDesc.CullMode = D3D11_CULL_FRONT;
	tRSDesc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&tRSDesc, &m_arrRSState[(UINT)RASTERIZER_TYPE::CULL_FRONT]);

	tRSDesc = {};
	tRSDesc.CullMode = D3D11_CULL_NONE;
	tRSDesc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&tRSDesc, &m_arrRSState[(UINT)RASTERIZER_TYPE::CULL_NONE]);

	tRSDesc = {};
	tRSDesc.CullMode = D3D11_CULL_NONE;
	tRSDesc.FillMode = D3D11_FILL_WIREFRAME;

	DEVICE->CreateRasterizerState(&tRSDesc, &m_arrRSState[(UINT)RASTERIZER_TYPE::WIREFRAME]);

	return RET_SUCCESS;
}

void CDevice::ClearTarget(float * _pCol)
{
	// 출력 이미지 클리어
	for (int i = 0; i < RENDERTARGET_NUM; ++i)
	{
		m_pContext->ClearRenderTargetView(m_pTargetView[i], _pCol);
		// 깊이 스텐실 정보 클리어
		m_pContext->ClearDepthStencilView(m_pDepthStencilView
			, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL
			, (UINT8)1.f, (UINT8)0.f); // Depth -> 1, stencil -> 0. Depth 1 뭐였더라.
	}
}

void CDevice::ReleaseDevice()
{

}

void CDevice::CreateCBuffer(const wstring _strKey, UINT _iSize, UINT _iRegister)
{
	CConstBuffer* pBuffer = CConstBuffer::Create(_strKey, _iSize, _iRegister);

	m_mapCBuff.insert(make_pair(_strKey, pBuffer));
}

CConstBuffer * CDevice::FindCBuffer(const wstring & _strKey)
{
	map<wstring, CConstBuffer*>::iterator iter = m_mapCBuff.find(_strKey);
	if (iter == m_mapCBuff.end())
	{
		return NULL;
	}
	return iter->second;
}


// 생성되는 텍스쳐는 gpu에 올라간다.

//ID3D11Texture2D

//__uuidof(); // 고유 아이디