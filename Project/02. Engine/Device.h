#pragma once

#include "global.h"

class CConstBuffer;

class CDevice
{
	SINGLE(CDevice);

private:
	HWND						m_hWnd;		// 타겟 윈도우 핸들
	ID3D11Device*				m_pDevice;	// GPU 메모리, 할당
	ID3D11DeviceContext*		m_pContext;	// Render

	//ID3D11Device1*				m_pDevice1;
	//ID3D11DeviceContext1*		m_pContext1;

	UINT						m_iQualityLv; // 멀티샘플 품질 수준

	IDXGISwapChain*				m_pSwapChain; // swap chain // 생성과 동시에 아래 것이 생성
	ID3D11RenderTargetView*		m_pTargetView[RENDERTARGET_NUM]; // 출력 타겟 뷰 // 스왑체인이 가지고 있다. ( 직접 만드는게 아니라 스왑체인이 가지고 있으니까 그걸 꺼내서 연결지어줌 )

	ID3D11Texture2D*			m_pDepthStencilTex; // 깊이 스텐실 버퍼 뷰 // 물체가 가려지는지 아닌지 결정 // 이거를 아래로 전달 ( 깊이 스텐실 뷰로 )
	ID3D11DepthStencilView*		m_pDepthStencilView; // 깊이 스텐실 뷰 // 텍스쳐가 필요함 (내가 직접 만들어 주는것()

	ID3D11SamplerState*			m_pSampler;
	tResolution					m_res;		// 현재 해상도
	bool						m_bWindow;	// 창모드 

	map<wstring, CConstBuffer*>	m_mapCBuff;

	ID3D11RasterizerState*		m_arrRSState[(UINT)RASTERIZER_TYPE::END];


public:
	int init(HWND _hWnd, const tResolution& _res, bool _bWindow);
	void ClearTarget(float* _pCol);
	void Present() { m_pSwapChain->Present(0, 0); }
	void ReleaseDevice();
	//void SecondPresent() { m_pSwapChain->Present(0, 0); }

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetContext() { return m_pContext; }

	//ID3D11Device1* GetDevice() { return m_pDevice1; }
	//ID3D11DeviceContext1* GetContext() { return m_pContext1; }

	ID3D11RenderTargetView* GetRenderTargetView() { return m_pTargetView[0]; }
	ID3D11DepthStencilView* GetDepthStencilView() { return m_pDepthStencilView; }
	IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }
	//void Release();

public:
	void SetRSState(RASTERIZER_TYPE _eType)
	{
		CONTEXT->RSSetState(m_arrRSState[(UINT)_eType]);
	}

public:
	const tResolution& GetResolution() { return m_res; }

public:
	void CreateCBuffer(const wstring _strKey, UINT _iSize, UINT _iRegister);
	CConstBuffer* FindCBuffer(const wstring& _strKey);

public:
	const HWND& GetMainhWnd() { return m_hWnd; }
};

