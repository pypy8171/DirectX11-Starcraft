//#pragma once
//// 다중 렌더 타겟 시도
//
//#include "Device.h"
//
//
//
//CDevice::CDevice()
//	: m_hWnd(NULL)
//	, m_pDevice(NULL)
//	, m_pContext(NULL)
//	, m_iQualityLv(0)
//	, m_res{}
//	, m_bWindow(true)
//	, m_pSwapChain(NULL)
//	//, m_pTargetView(NULL)
//	, m_pDepthStencilTex(NULL)
//	, m_pDepthStencilView(NULL)
//{
//	for (int i = 0; i < 2; ++i)
//	{
//		m_pTargetView[i] = NULL;
//	}
//}
//
//CDevice::~CDevice()
//{
//	SAFE_RELEASE(m_pDevice);
//	SAFE_RELEASE(m_pContext);
//	SAFE_RELEASE(m_pSwapChain);
//	SAFE_RELEASE(m_pTargetView[0]);
//	SAFE_RELEASE(m_pTargetView[1]);
//	SAFE_RELEASE(m_pDepthStencilTex);
//	SAFE_RELEASE(m_pDepthStencilView);
//}
//
//int CDevice::init(HWND _hWnd, const tResolution & _res, bool _bWindow)
//{
//	m_bWindow = _bWindow;
//	m_res = _res;
//	m_hWnd = _hWnd;
//
//	int iFlag = 0;
//#ifdef _DEBUG
//	iFlag = D3D11_CREATE_DEVICE_DEBUG;
//#endif
//
//	D3D_FEATURE_LEVEL eLv;
//	if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, iFlag,
//		0, 0, D3D11_SDK_VERSION, &m_pDevice, &eLv, &m_pContext)))
//	{
//		return RET_FAILED;
//	}
//
//	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iQualityLv);
//
//	if (m_iQualityLv == 0)
//		return RET_FAILED;
//
//	DXGI_SWAP_CHAIN_DESC tSwapDesc = {};
//
//	tSwapDesc.BufferCount = 1; // 버퍼 한개
//	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼(텍스쳐) 가 이미지 출력 타겟임을 알림
//	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	tSwapDesc.BufferDesc.Width = _res.x;
//	tSwapDesc.BufferDesc.Height = _res.y;
//
//	// 주사율
//	tSwapDesc.BufferDesc.RefreshRate.Denominator = 1; // 기존 60
//	tSwapDesc.BufferDesc.RefreshRate.Numerator = 60; // 기존 1
//
//													 // 모니터 
//	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // UNSPECIFED -> DEFAULT 값이라 생각하면됨.// 미지정
//	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//
//	// 출력 윈도우 및 창모드 
//	tSwapDesc.Windowed = _bWindow;
//	tSwapDesc.OutputWindow = m_hWnd;
//
//	// 멀티 샘플 AA 를 위해서 셋팅
//	tSwapDesc.SampleDesc.Count = 4;
//	tSwapDesc.SampleDesc.Quality = 0;
//
//	// 이전 프레임 이미지를 저장하지 않음
//	tSwapDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; // 한 프레임 이전 프레임 버려라
//
//	IDXGIDevice* pDevice = NULL;
//	IDXGIAdapter* pAdapter = NULL;
//	IDXGIFactory* pFactory = NULL;
//
//	// 예외처리 걸어놓고 failed 처리 해야함.
//	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDevice);
//	pDevice->GetAdapter(&pAdapter);
//	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);
//
//	pFactory->CreateSwapChain(m_pDevice, &tSwapDesc, &m_pSwapChain);
//
//	pDevice->Release();
//	pAdapter->Release();
//	pFactory->Release();
//
//	//=============
//	// CREATE VIEW
//	//=============
//	// RenderTargerView 만들기
//	// 이미 생성되어 있는 Texture를 가져와야 한다.
//
//	ID3D11Texture2D* pTargetTexture = NULL;
//	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pTargetTexture); // 버퍼 꺼내기 랜더 타겟이 가져야 하는 텍스쳐가 얘다.
//																					// Getbuffer 행위자체가 레퍼런스 카운트(참조 카운트) 1늘리는 행위이다.
//																					// 따라서 바로 제거
//	pTargetTexture->Release();
//	m_pDevice->CreateRenderTargetView(pTargetTexture, NULL, &m_pTargetView[0]);
//	m_pDevice->CreateRenderTargetView(pTargetTexture, NULL, &m_pTargetView[1]);
//	// DepthStencilTexture 만들기
//
//	D3D11_TEXTURE2D_DESC tTexDesc = {};
//
//	tTexDesc.Width = _res.x;
//	tTexDesc.Height = _res.y;
//	tTexDesc.MipLevels = 1; // 1 의 의미 -> 본체만 생성
//	tTexDesc.ArraySize = 1; // 텍스처 배열의 텍스처 수입니다. 범위는 1에서 D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION (2048)까지입니다. 텍스처 큐브 맵의 경우이 값은 6의 배수 ( D3D11_TEXCUBE_ARRAY_SRV 의 NumCube 멤버의 값의 6 배)이며 범위는 6에서 2046 사이입니다. 범위는 실제로 렌더링 장치를 만듭니다. 제한에 대한 자세한 내용은주의를 참조하십시오.
//	tTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 픽셀 하나당 4바이트를 사용하겠다. 3바이트는 깊이, 1바이트는 스텐실을 위한 메모리 공간 
//													 // 깊이 체크 스텐실 체크 둘 다 함 
//													 // 스텐실이란?(미술 기법)  구멍 뚫어놓고 거기만 통과 DEPTH 통과하고 STENCIL도 통과해야 그린다. 
//													 // 지정된 영역에만 효과를 주고 싶을때 사용
//	tTexDesc.SampleDesc.Count = 4; // 동일해야 함
//	tTexDesc.SampleDesc.Quality = 0; // 멀티 샘플 동일한 카운트와 퀄리티
//
//	tTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 용도
//	tTexDesc.Usage = D3D11_USAGE_DEFAULT; // 내부적으로 건들일이 없어서 default 옵션
//
//	m_pDevice->CreateTexture2D(&tTexDesc, 0, &m_pDepthStencilTex); // 텍스쳐 나옴
//
//																   // DepthStencilView 를 DepthStencilTexture 를 이용해서 만들기
//	m_pDevice->CreateDepthStencilView(m_pDepthStencilTex, NULL, &m_pDepthStencilView);
//
//	// 출력 타겟과 깊이 스텐실 타겟을 알린다. 총 8개 가능 dxd11에서는
//	m_pContext->OMSetRenderTargets(2, &m_pTargetView[0], m_pDepthStencilView); // 여러개 넣을라면 m_pTargetView[2] 이런식으로 배열로 만들어야겠다.
//
//																			   // 생성되는 텍스쳐는 gpu에 올라간다.
//
//																			   //ID3D11Texture2D
//
//																			   //__uuidof(); // 고유 아이디
//
//																			   //========
//																			   // 뷰 포트
//																			   //========
//																			   // 윈도우로 출력 이미지가 전송될때, 출력 될 영역을 지정한다.
//																			   // 실제로는 뷰포트까지 감안해서 출력이미지가 완성되고, 윈도우로 이미지가 복사된다.
//
//	D3D11_VIEWPORT tViewPortDesc[2] = {};
//
//	tViewPortDesc[0].Width = _res.x / 2.f;
//	tViewPortDesc[0].Height = _res.y / 2.f;
//	tViewPortDesc[0].MinDepth = 0.f; // 최소거리 내 눈 바로 앞이라 보면됨. 0 이하는 내 눈 뒤.
//	tViewPortDesc[0].MaxDepth = 1.f; // 최대 가시거리
//	tViewPortDesc[0].TopLeftX = 0;
//	tViewPortDesc[0].TopLeftY = 0;
//
//	tViewPortDesc[1].Width = _res.x / 2.f;
//	tViewPortDesc[1].Height = _res.y;
//	tViewPortDesc[1].MinDepth = 0.f; // 최소거리 내 눈 바로 앞이라 보면됨. 0 이하는 내 눈 뒤.
//	tViewPortDesc[1].MaxDepth = 1.f; // 최대 가시거리
//	tViewPortDesc[1].TopLeftX = _res.x / 2.f;
//	tViewPortDesc[1].TopLeftY = 0;
//
//	m_pContext->RSSetViewports(2, &tViewPortDesc[0]);
//
//	return RET_SUCCESS;
//}
//
//void CDevice::ClearTarget(float * _pCol)
//{
//	// 출력 이미지 클리어
//	m_pContext->ClearRenderTargetView(m_pTargetView[0], _pCol);
//	// 깊이 스텐실 정보 클리어
//	m_pContext->ClearDepthStencilView(m_pDepthStencilView
//		, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL
//		, 1.f, 0.f); // Depth -> 1, stencil -> 0. Depth 1 뭐였더라.
//
//
//
//}
//
//void CDevice::ClearSecondTarget(float * _pCol)
//{
//	m_pContext->ClearRenderTargetView(m_pTargetView[1], _pCol);
//	m_pContext->ClearDepthStencilView(m_pDepthStencilView
//		, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL
//		, 1.f, 0.f); // Depth -> 1, stencil -> 0. Depth 1 뭐였더라.
//}



//const int n = 5;
//mInstancedData.resize(n*n*n);
//
//float width = 200.f;
//float height = 200.f;
//float depth = 200.f;
//
//float x = -0.5f*width;
//float y = -0.5f*height;
//float z = -0.5f*depth;
//float dx = width / (n - 1);
//float dy = height / (n - 1);
//float dz = depth / (n - 1);
//
//for (int k = 0; k < n; ++k)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		for (int j = 0; j < n; ++j)
//		{
//			mInstancedData[k*n*n + i * n + j].World = XMFLOAT4x4(
//				1.f, 0.f, 0.f, 0.f,
//				0.f, 1.f, 0.f, 0.f,
//				0.f, 0.f, 1.f, 0.f,
//				x + j * dx, y + idy, z + k * dz, 1.f);
//
//
//		}
//	}
//}
//
//
//D3D11_BUFFER_DESC tBufferDesc = {};
//tBufferDesc.ByteWidth = sizeof(InstancedData) * mInstancedData.size();
//tBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // 두개 같이 usage spuaccessflags 바꿀 수 있게 하는 파라미터
//tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//D3D11_SUBRESOURCE_DATA tSubData = {};
//tSubData.pSysMem = arrVTX;
//
//DEVICE->CreateBuffer(&tBufferDesc, &tSubData, m_pVB);





//const int n = 5;
//mInstancedData.resize(4);

//float width = 200.f;
//float height = 200.f;
//float depth = 200.f;

//float x = -0.5f;
//float y = -0.5f;
//float z = -0.5f;
//float dx = width / (n - 1);
//float dy = height / (n - 1);
//float dz = depth / (n - 1);

//for (int k = 0; k < n; ++k)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		for (int j = 0; j < n; ++j)
//		{
//			mInstancedData[k*n*n + i*n + j ].World = XMFLOAT4X4(
//				1.f, 0.f, 0.f, 0.f,
//				0.f, 1.f, 0.f, 0.f,
//				0.f, 0.f, 1.f, 0.f,
//				x + j * dx, y +i* dy, z + k * dz, 1.f);


//		}
//	}
//}
//mInstancedData[0].World = XMFLOAT4X4(
//	1.f, 0.f, 0.f, 0.f,
//	0.f, 1.f, 0.f, 0.f,
//	0.f, 0.f, 1.f, 0.f,
//	0, 0, 0, 1.f);

//mInstancedData[1].World = XMFLOAT4X4(
//	1.f, 0.f, 0.f, 0.f,
//	0.f, 1.f, 0.f, 0.f,
//	0.f, 0.f, 1.f, 0.f,
//	0.2, 0.2, 0.2, 1.f);

//mInstancedData[2].World = XMFLOAT4X4(
//	1.f, 0.f, 0.f, 0.f,
//	0.f, 1.f, 0.f, 0.f,
//	0.f, 0.f, 1.f, 0.f,
//	0.4, 0.4, 0.4, 1.f);

//mInstancedData[3].World = XMFLOAT4X4(
//	100.f, 0.f, 0.f, 0.f,
//	0.f, 100.f, 0.f, 0.f,
//	0.f, 0.f, 100.f, 0.f,
//	0.6, 0.6, 0.6, 1.f);

/////////////

//tLayoutDesc[0].SemanticName = "POSITION"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
//tLayoutDesc[0].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
//tLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
//tLayoutDesc[0].InputSlot = 0;
//tLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;//  D3D11_INPUT_PER_VERTEX_DATA; // D3D11_INPUT_PER_INSTANCE_DATA
//tLayoutDesc[0].InstanceDataStepRate = 0; // 인스턴싱 할때 
//tLayoutDesc[0].AlignedByteOffset = iOffset;

//iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32_FLOAT);

//tLayoutDesc[1].SemanticName = "COLOR"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
//tLayoutDesc[1].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
//tLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//tLayoutDesc[1].InputSlot = 0;
//tLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // D3D11_INPUT_PER_VERTEX_DATA; // D3D11_INPUT_PER_INSTANCE_DATA
//tLayoutDesc[1].InstanceDataStepRate = 0; // 인스턴싱 할때 
//tLayoutDesc[1].AlignedByteOffset = iOffset;

//iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

//iOffset = 0;

//tLayoutDesc[2].SemanticName = "WORLD"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
//tLayoutDesc[2].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
//tLayoutDesc[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//tLayoutDesc[2].InputSlot = 1;
//tLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA; // D3D11_INPUT_PER_VERTEX_DATA; // D3D11_INPUT_PER_INSTANCE_DATA
//tLayoutDesc[2].InstanceDataStepRate = 1; // 인스턴싱 할때 
//tLayoutDesc[2].AlignedByteOffset = iOffset;

//iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

//tLayoutDesc[3].SemanticName = "WORLD"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
//tLayoutDesc[3].SemanticIndex = 1;			// 같은 시멘틱에 대한 offset 인덱스
//tLayoutDesc[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//tLayoutDesc[3].InputSlot = 1;
//tLayoutDesc[3].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA; // D3D11_INPUT_PER_VERTEX_DATA; // D3D11_INPUT_PER_INSTANCE_DATA
//tLayoutDesc[3].InstanceDataStepRate = 1; // 인스턴싱 할때 
//tLayoutDesc[3].AlignedByteOffset = iOffset;

//iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

//tLayoutDesc[4].SemanticName = "WORLD"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
//tLayoutDesc[4].SemanticIndex = 2;			// 같은 시멘틱에 대한 offset 인덱스
//tLayoutDesc[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//tLayoutDesc[4].InputSlot = 1;
//tLayoutDesc[4].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA; // D3D11_INPUT_PER_VERTEX_DATA; // D3D11_INPUT_PER_INSTANCE_DATA
//tLayoutDesc[4].InstanceDataStepRate = 1; // 인스턴싱 할때 
//tLayoutDesc[4].AlignedByteOffset = iOffset;

//iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

//tLayoutDesc[5].SemanticName = "WORLD"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
//tLayoutDesc[5].SemanticIndex = 3;			// 같은 시멘틱에 대한 offset 인덱스
//tLayoutDesc[5].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//tLayoutDesc[5].InputSlot = 1;
//tLayoutDesc[5].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA; // D3D11_INPUT_PER_VERTEX_DATA; // D3D11_INPUT_PER_INSTANCE_DATA
//tLayoutDesc[5].InstanceDataStepRate = 1; // 인스턴싱 할때 
//tLayoutDesc[5].AlignedByteOffset = iOffset;

//iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);


//// 월드 행렬 계산하기
////m_vRot = Transform()->GetLocalAngle();
//
//// 크기 행렬
//Matrix matScale = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
//
//// 회전(자전) 행렬
////Matrix matRotate = XMMatrixRotationX(m_vRot.x);
////matRotate *= XMMatrixRotationY(m_vRot.y);
////matRotate *= XMMatrixRotationZ(m_vRot.z);
//
//// 이동 행렬
////Vec3 vPos = Transform()->GetLocalPos();
//Matrix matTrans = XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);
//
//// 월드행렬
//m_matCol = matScale * matTrans;
//m_matCol *= Transform()->GetWolrdMat();
//break;

//m_fTimer += DT;
//CWell512 randompos, randomsize;
//float fSize = randomsize.GetFloatValue(10, 50);
//float fPos = randompos.GetFloatValue(-300, 300);

//int iTimer = 100.f * m_fTimer;
//if (iTimer %200 == 0)
//{
//	CScript* pMonsterScript = new CMonsterScript;
//	// 몬스터 
//	CGameObject* pObject = new CGameObject;	
//	pObject->AddComponent(new CMeshRender);

//	pObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"hexahedron"));
//	pObject->MeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));

//	pObject->Transform()->SetLocalScale(Vec3(fSize, fSize, fSize));
//	pObject->Transform()->SetLocalPos(Vec3(-fPos, 100.f, 500.f));


//	pObject->AddComponent<CScript>(pMonsterScript);

//	m_pCurScene->AddGameObject(L"Default", pObject);
//}