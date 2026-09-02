#include "Camera.h"

#include "Device.h"
#include "Transform.h"
#include "GameObject.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Layer.h"

#include <iostream>
using namespace std;

float g_depthz = 100.f;

CCamera::CCamera()
	: m_fFar(10000.f)
	, m_fNear(1.f)
	, m_fFov(XM_PI/4.f)
	, m_fScale(1.f)
	, m_bPerspective(false)
	, m_tResolution{}
	, m_vEye(Vec3(0.f, 0.f,-30.f))
	, m_vRight(Vec3(1.f, 0.f, 0.f))
	, m_vLook(Vec3(0.f, 0.f, 0.f))
	, m_vUp(Vec3(0.f, 1.f, 0.f))
	, m_vAngle(Vec3(0.f, 0.f, 0.f))
	, m_fMoveSpeed(100.f)
	, m_fSpeed(1.f)
	, m_fRatio(0.f)
	, m_bTransforming(false)
{
	SetComponentType(COMPONENT_TYPE::CAMERA);
	m_tResolution = CDevice::GetInst()->GetResolution();
}

CCamera::~CCamera()
{
}

int CCamera::update()
{
	//CameraTransform();
	//CameraRotate();	

	return 0;
}


int CCamera::finalupdate()
{
	ChangeProjMode(); // 모드 변환도 이벤트로 묶어서 해야 하지 않을까

	// 카메라 레이어라면 
	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	CLayer* pLayer = pScene->GetLayer(L"Camera");
	CGameObject* pCamObj = pLayer->GetObjVec()[0];

	Vec3 vWolrdPos{};

	vWolrdPos = -pCamObj->Transform()->GetWolrdPos();
	m_matView = Matrix::Identity;

	m_matView.Right(Transform()->GetWorldDir(DIR_TYPE::RIGHT));
	m_matView.Up(Transform()->GetWorldDir(DIR_TYPE::UP));
	m_matView.Front(Transform()->GetWorldDir(DIR_TYPE::FRONT));
	m_matView = m_matView.Transpose();

	m_matView._41 = vWolrdPos.Dot(Transform()->GetWorldDir(DIR_TYPE::RIGHT));
	m_matView._42 = vWolrdPos.Dot(Transform()->GetWorldDir(DIR_TYPE::UP));
	m_matView._43 = vWolrdPos.Dot(Transform()->GetWorldDir(DIR_TYPE::FRONT));
	g_tTransMatrix.matView = m_matView;


	if (m_bPerspective)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fFov*m_fScale, m_tResolution.x / m_tResolution.y, m_fNear, m_fFar);
	}
	else
	{
		float fWidth = m_tResolution.x * 0.5f * m_fScale;
		float fHeight = m_tResolution.y * 0.5f * m_fScale;

		m_matProj = XMMatrixOrthographicOffCenterLH(-fWidth, fWidth, -fHeight, fHeight, m_fNear, m_fFar);
	}

	// 카메라를 현재씬에 등록
	CSceneMgr::GetInst()->RegisterCamera(this);

	// 직교 <---> 원근 서로 변화가 생겼을 경우
	if (m_bTransforming)
	{
		// m_matOldProj --> m_matProj
		if (m_bPerspective)
			m_fSpeed += (float)DT * 1.f;
		else
		{
			m_fSpeed -= (float)DT * 24.f;
			if (m_fSpeed < 0.f)
				m_fSpeed = 0.05f;
		}

		m_fRatio += (float)(DT / 2.f) * m_fSpeed;

		if (m_fRatio >= 1.f)
		{
			m_fRatio = 1.f;
			m_bTransforming = false;
		}

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				// 시간에 따라 행렬 변환						
				m_matProj.m[i][j] = Lerf(m_matPrevProj.m[i][j], m_matProj.m[i][j], m_fRatio);
			}
		}
	}

	g_tTransMatrix.matProj = m_matProj;

	return 0;
}


void CCamera::ChangeProjMode()
{
	if (KEYTAB(KEY_TYPE::KEY_F12))
	{
		if (m_bPerspective == true)
		{
			m_bPerspective = false;
		}
		else if (m_bPerspective == false)
		{
			m_bPerspective = true;
		}
	}
}

void CCamera::CheckLayer(UINT _iIdx)
{
	if (m_iLayerMask & (1 << _iIdx))
	{
		m_iLayerMask &= ~(1 << _iIdx);
	}
	else
	{
		m_iLayerMask |= (1 << _iIdx);
	}
}

void CCamera::CheckLayer(const wstring & _strLayerName)
{
	UINT iIdx = CSceneMgr::GetInst()->GetLayer(_strLayerName)->GetIdx();
	m_iLayerMask |= (1 << iIdx);
}

void CCamera::render(CLayer** _pLayer)
{
	CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
	if (pScene->GetName() != L"StudyScene")
	{
		CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"ProtossUI")->update();
		CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"ProtossUI")->lateupdate();
		CSceneMgr::GetInst()->GetCurrentScene()->GetLayer(L"ProtossUI")->finalupdate();
	}
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL == _pLayer[i] || !(m_iLayerMask & (1 << i)))
		{
			continue;
		}
		// GameObject 중에서, 화면에 보이는 Object 선별
		_pLayer[i]->render();
	}
}

void CCamera::CameraTransform()
{
	static Vec3 mat;
	mat = m_vLook - m_vEye;
	mat.Normalize();

	if (KEYHOLD(KEY_TYPE::KEY_W))
	{
		m_vEye += mat * DT * m_fMoveSpeed;
		m_vLook += mat * DT * m_fMoveSpeed;
		//m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp); //    XMVECTORF32 Result = { { {	V1.vector4_f32[0] - V2.vector4_f32[0],	V1.vector4_f32[1] - V2.vector4_f32[1],	V1.vector4_f32[2] - V2.vector4_f32[2],	V1.vector4_f32[3] - V2.vector4_f32[3]}} };
	}

	if (KEYHOLD(KEY_TYPE::KEY_S))
	{
		m_vEye -= mat * DT* m_fMoveSpeed;
		m_vLook -= mat * DT* m_fMoveSpeed;
	}

	static Vec3 vView;
	static Vec3 vCross;

	// 외적 결과 : 두 벡터의 외적 결과 값이 양수면 반시계 // 반시계 위치에 있으면 결과는 양수이다.
	vView = m_vLook - m_vEye;
	vCross = XMVector3Cross(m_vUp, vView); //XMVECTORF32 vResult = { { {(V1.vector4_f32[1] * V2.vector4_f32[2]) - (V1.vector4_f32[2] * V2.vector4_f32[1]),(V1.vector4_f32[2] * V2.vector4_f32[0]) - (V1.vector4_f32[0] * V2.vector4_f32[2]),(V1.vector4_f32[0] * V2.vector4_f32[1]) - (V1.vector4_f32[1] * V2.vector4_f32[0]),0.0f} } };
	vCross.Normalize();
	vView.Normalize();

	if (KEYHOLD(KEY_TYPE::KEY_E))
	{
		m_vEye += vCross * DT* m_fMoveSpeed;
		m_vLook += vCross * DT* m_fMoveSpeed;
	}

	if (KEYHOLD(KEY_TYPE::KEY_Q))
	{
		m_vEye -= vCross * DT * m_fMoveSpeed;
		m_vLook -= vCross * DT * m_fMoveSpeed;
	}

	static Vec3 vViewY;
	static Vec3 vCrossY;
	vViewY = m_vLook - m_vEye;
	vCrossY = XMVector3Cross(vViewY, m_vRight); // 카메라 이동에서 외적 곱하는 순서에 따라 결과가 달라지는데? 내가 좌표계를 혼동하는건가?
	vCrossY.Normalize();
	vViewY.Normalize();

	if (KEYHOLD(KEY_TYPE::KEY_R))
	{
		m_vEye += vCrossY * DT * m_fMoveSpeed;
		m_vLook += vCrossY * DT * m_fMoveSpeed;
	}

	if (KEYHOLD(KEY_TYPE::KEY_F))
	{
		m_vEye -= vCrossY * DT* m_fMoveSpeed;
		m_vLook -= vCrossY * DT* m_fMoveSpeed;
	}

	m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp);
}

void CCamera::CameraRotate()
{
	static Matrix matRotY{};
	static Vec3 ViewY{};
	ViewY = m_vLook - m_vEye;
	ViewY.Normalize();
	m_vAngle.y = DT;

	if (KEYHOLD(KEY_TYPE::KEY_A))
	{
		matRotY = XMMatrixRotationAxis(m_vUp, -m_vAngle.y); // XMScalarSinCos

		ViewY = XMVector3TransformCoord(ViewY, matRotY);

		m_vLook = m_vEye + ViewY;
		m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp);

	}

	if (KEYHOLD(KEY_TYPE::KEY_D))
	{
		matRotY = XMMatrixRotationAxis(m_vUp, m_vAngle.y);

		ViewY = XMVector3TransformCoord(ViewY, matRotY);

		m_vLook = m_vEye + ViewY;
		m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp);
	}

	static Vec3  ViewX{};
	static Vec3  vCross{};
	static Matrix matRotX{};

	ViewX = m_vLook - m_vEye;
	//vCross = XMVector3Cross(m_vUp, ViewZ);
	//vCross.Normalize();
	ViewX.Normalize();
	m_vAngle.x = DT;

	if (KEYHOLD(KEY_TYPE::KEY_T))
	{
		matRotX = XMMatrixRotationAxis(m_vRight, -m_vAngle.x);
		ViewX = XMVector3TransformCoord(ViewX, matRotX);

		m_vLook = m_vEye + ViewX;
		m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp);
	}
	if (KEYHOLD(KEY_TYPE::KEY_G))
	{
		matRotX = XMMatrixRotationAxis(m_vRight, m_vAngle.x);
		ViewX = XMVector3TransformCoord(ViewX, matRotX);

		m_vLook = m_vEye + ViewX;
		m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp);
	}

	static Vec3 ViewZ(0.f, 0.f, 0.f);
	static Vec3 vFront(0.f, 0.f, 1.f);
	static Matrix matRotZ;

	vFront.Normalize();
	ViewZ = m_vLook - m_vEye;
	ViewZ.Normalize();
	m_vAngle.z = DT;


	if (KEYHOLD(KEY_TYPE::KEY_V))
	{
		matRotZ = XMMatrixRotationAxis(vFront, m_vAngle.z);
		ViewZ = XMVector3TransformCoord(ViewZ, matRotZ);

		m_vLook = m_vEye + ViewZ;
		m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp);
	}
	if (KEYHOLD(KEY_TYPE::KEY_B))
	{
		matRotZ = XMMatrixRotationAxis(vFront, -m_vAngle.x);
		ViewZ = XMVector3TransformCoord(ViewZ, matRotZ);

		m_vLook = m_vEye + ViewZ;
		m_matView = XMMatrixLookAtLH(m_vEye, m_vLook, m_vUp);
	}


	//static float fcos;
	//static float fsin;
	//static float fangle = 0.f;
	//fangle += 0.001f;
	//XMScalarSinCos(&fcos, &fsin, fangle);

	//m_matView(0, 0) = fcos;
	//m_matView(0, 1) = fsin;
	//m_matView(1, 0) = -fsin;
	//m_matView(1, 1) = fcos;
}

void CCamera::Save(FILE * _pFile)
{
	CComponent::Save(_pFile);

	fwrite(&m_fNear, sizeof(float), 1, _pFile);	// 최소거리
	fwrite(&m_fFar, sizeof(float), 1, _pFile);	// 최대거리
	fwrite(&m_fFov, sizeof(float), 1, _pFile);	// 시야각 (원근투영)
	fwrite(&m_fScale, sizeof(float), 1, _pFile);	// 투영 크기(직교투영)

	fwrite(&m_iLayerMask, sizeof(UINT), 1, _pFile);	// 투영 크기(직교투영)
	fwrite(&m_bPerspective, 1, 1, _pFile);
}

void CCamera::Load(FILE * _pFile)
{
	CComponent::Load(_pFile);

	fread(&m_fNear, sizeof(float), 1, _pFile);	// 최소거리
	fread(&m_fFar, sizeof(float), 1, _pFile);	// 최대거리
	fread(&m_fFov, sizeof(float), 1, _pFile);	// 시야각 (원근투영)
	fread(&m_fScale, sizeof(float), 1, _pFile);	// 투영 크기(직교투영)

	fread(&m_iLayerMask, sizeof(UINT), 1, _pFile);	// 투영 크기(직교투영)
	fread(&m_bPerspective, 1, 1, _pFile);
}


//
//if (KEYTAB(KEY_TYPE::KEY_F10))
//{
//	ID3D11DepthStencilView* pDepthStencilView = CDevice::GetInst()->GetDepthStencilView();
//	ID3D11RenderTargetView* pRenderTargetView = CDevice::GetInst()->GetRenderTargetView();
//	//// 1. Clear the existing references to the backbuffer
//	ID3D11RenderTargetView* nullViews[] = { nullptr };
//	CONTEXT->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
//	CDevice::GetInst()->GetRenderTargetView()->Release();// Microsoft::WRL::ComPtr here does a Release();
//														 //m_depthStencilView.Reset();
//	CONTEXT->Flush();
//
//	//// 2. Resize the existing swapchain
//	CDevice::GetInst()->GetSwapChain()->ResizeBuffers(1, WINCX*0.5, WINCY*0.5, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
//	//if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
//	//	// You have to destroy the device, swapchain, and all resources and
//	//	// recreate them to recover from this case. The device was hardware reset,
//	//	// physically removed, or the driver was updated and/or restarted
//
//	//	// 3. Get the new backbuffer texture to use as a render target
//	ID3D11Texture2D* pTargetTexture = NULL;
//	CDevice::GetInst()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pTargetTexture); // 버퍼 꺼내기 랜더 타겟이 가져야 하는 텍스쳐가 얘다.
//																										  // Getbuffer 행위자체가 레퍼런스 카운트(참조 카운트) 1늘리는 행위이다.
//																										  // 따라서 바로 제거
//	pTargetTexture->Release();
//
//	//hr = m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_renderTargetView);
//	DEVICE->CreateRenderTargetView(pTargetTexture, nullptr, &pRenderTargetView);
//	//// 4. Create a depth/stencil buffer and create the depth stencil view
//	//CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);
//	//hr = m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil);
//
//	//CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
//	//hr = m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_depthStencilView));
//
//	ID3D11Texture2D*		pDepthStencilTex;
//	D3D11_TEXTURE2D_DESC tTexDesc = {};
//
//	tTexDesc.Width = (UINT)WINCX*0.5;
//	tTexDesc.Height = (UINT)WINCY*0.5;
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
//	DEVICE->CreateTexture2D(&tTexDesc, 0, &pDepthStencilTex); // 텍스쳐 나옴
//															  // DepthStencilView 를 DepthStencilTexture 를 이용해서 만들기
//	DEVICE->CreateDepthStencilView(pDepthStencilTex, NULL, &pDepthStencilView);
//
//	//// 5. Reset the rendering viewport to the new size
//	D3D11_VIEWPORT viewPort{};
//	viewPort.Width = WINCX * 0.5;
//	viewPort.Height = WINCY * 0.5;
//	viewPort.MinDepth = 0.f; // 최소거리 내 눈 바로 앞이라 보면됨. 0 이하는 내 눈 뒤.
//	viewPort.MaxDepth = 1.f; // 최대 가시거리
//	viewPort.TopLeftX = 0;
//	viewPort.TopLeftY = 0;
//	CONTEXT->RSSetViewports(1, &viewPort);
//
//	//// 6. Reset your camera's aspect ratio based on backBufferWidth/backBufferHeight
//
//	//// 7. Set your render target view/depth stencil view for rendering
//
//	CONTEXT->OMSetRenderTargets(1, &pRenderTargetView, CDevice::GetInst()->GetDepthStencilView());
//}
//// dxgiFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);