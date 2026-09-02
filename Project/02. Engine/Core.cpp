#include "Core.h"
#include "Device.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "SceneMgr.h"
#include "RenderMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"


tGlobalValue     g_global = {};

CCore::CCore()
	: m_fRotateAngle(0)
	, m_vMovePos(Vec3(0.f, 0.f, 0.f))
	, m_vMoveAngle(Vec3(0.f, 0.f, 0.f))
	, m_vResolution{}
{
}

CCore::~CCore()
{
}


void CCore::init(HWND _hWnd, const tResolution & _res, bool _bWindow)
{
	m_hWnd = _hWnd;
	CDevice::GetInst()->init(m_hWnd, _res, _bWindow);

	m_vResolution = _res;

	CPathMgr::init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CRenderMgr::GetInst()->init();
	CShaderMgr::GetInst()->init();
	CResMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	// 상수 버퍼 만들기
	CDevice::GetInst()->CreateCBuffer(L"Transform", sizeof(tTransformMatrix), 0);
	CDevice::GetInst()->CreateCBuffer(L"ShaderParam", sizeof(tShaderParam), 1);
	CDevice::GetInst()->CreateCBuffer(L"Anim2DInfo", sizeof(tAnim2DInfo), 2);
	CDevice::GetInst()->CreateCBuffer(L"LightInfo", sizeof(tLightInfo) * 10, 3);
	CDevice::GetInst()->CreateCBuffer(L"Global", sizeof(tGlobalValue), 4);
}

int CCore::progress()
{
	update();
	render();
	return 0;
}


void CCore::ProgressPipeline()
{	
	//CSceneMgr::GetInst()->render();
	CRenderMgr::GetInst()->render();

	// 버텍스 버퍼내의 제일 처음 버텍스데이터, 제일 처음 인스턴스부터 렌더링

}

int CCore::update()
{
	CKeyMgr::GetInst()->update();
	CTimeMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();
	CEventMgr::GetInst()->update();

	return 0;
}



void CCore::render()
{
	float arrCol[2][4]{ {0.5f, 0.5f, 0.5f, 1.f},
						{1.f, 1.f, 0.f, 1.f}};

	for (int i = 0; i < 1; ++i)
	{
		CDevice::GetInst()->ClearTarget(arrCol[i]);
	}


	ProgressPipeline();

	CDevice::GetInst()->Present();
}

//CONTEXT->Draw(3, 0);
//CONTEXT->DrawInstanced(3, 8, 0, 0);
//CONTEXT->DrawIndexed(36, 0, 0); // 파이프라인 시작 // 인덱스 갯수 