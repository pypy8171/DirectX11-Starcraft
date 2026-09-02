#pragma once
#include "SceneMgr.h"

#include "Device.h"

#include "Scene.h"

#include "GameObject.h"
#include "Animator2D.h"
#include "MeshRender.h"
#include "Transform.h"

#include "Camera.h"
#include "Collider.h"

#include "Prefab.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

#include "CollisionMgr.h"
#include "Script.h"



CSceneMgr::CSceneMgr()
	: m_pCurScene(NULL)
{
}


CSceneMgr::~CSceneMgr()
{
	SAFE_DELETE(m_pCurScene);
}


void CSceneMgr::init()
{
	m_pCurScene = new CScene;
	CDevice::GetInst()->SetRSState(RASTERIZER_TYPE::CULL_NONE);
	//CDevice::GetInst()->SetRSState(RASTERIZER_TYPE::CULL_NONE);
}

int CSceneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->lateupdate();
	m_pCurScene->finalupdate();

	CCollisionMgr::GetInst()->update();
	return 0;
}


CLayer * CSceneMgr::GetLayer(int _iIdx)
{
	assert(m_pCurScene);
	return m_pCurScene->GetLayer(_iIdx);
}

CLayer * CSceneMgr::GetLayer(const wstring & _strLayerName)
{
	assert(m_pCurScene);
	return m_pCurScene->GetLayer(_strLayerName);
}

void CSceneMgr::RegisterCamera(CCamera * _pCam)
{
	assert(m_pCurScene);
	m_pCurScene->RegisterCamera(_pCam);
}

void CSceneMgr::render()
{
	m_pCurScene->render();
}

void CSceneMgr::AddGameObject(const wstring & _strLayerName, CGameObject * _pObj)
{
	assert(m_pCurScene);
	m_pCurScene->AddGameObject(_strLayerName, _pObj);
}

void CSceneMgr::AddGameObject(UINT _iLayerIdx, CGameObject * _pObj)
{
	assert(m_pCurScene);
	m_pCurScene->AddGameObject(_iLayerIdx, _pObj);
}

CGameObject * CSceneMgr::FindObject(const wstring & _strName)
{
	assert(m_pCurScene); 
	return m_pCurScene->FindObject(_strName);
}

void CSceneMgr::ChangeScene(CScene * _pScene)
{ 
	assert(m_pCurScene);
	SAFE_DELETE(m_pCurScene);
	m_pCurScene = _pScene;
}
