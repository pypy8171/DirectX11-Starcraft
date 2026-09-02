#include "Scene.h"

#include "Layer.h"
#include "Camera.h"

CScene::CScene()
	: m_iLayerCount(0)
	, m_arrLayer{}
	, m_pTargetObj(nullptr)
	, m_pHeadObject(nullptr)
{
	m_vecTargetObj.clear();
	AddLayer(L"Default");
}


CScene::~CScene()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		SAFE_DELETE(m_arrLayer[i]);
	}
}

void CScene::awake()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_arrLayer[i])
			m_arrLayer[i]->awake();
	}
}

void CScene::start()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_arrLayer[i])
			m_arrLayer[i]->start();
	}
}

int CScene::update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_arrLayer[i])
			m_arrLayer[i]->update();
	}
	return 0;
}

int CScene::lateupdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_arrLayer[i])
			m_arrLayer[i]->lateupdate();
	}
	return 0;
}

int CScene::finalupdate()
{
	m_vecCam.clear();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_arrLayer[i])
			m_arrLayer[i]->finalupdate();
	}
	return 0;
}


void CScene::AddLayer(const wstring & _strLayerName)
{
	if (m_iLayerCount >= MAX_LAYER)
	{
		assert(NULL);
	}

	CLayer* pNewLayer = new CLayer;
	pNewLayer->SetName(_strLayerName);
	pNewLayer->SetIdx(m_iLayerCount);

	m_arrLayer[m_iLayerCount++] = pNewLayer;
}

void CScene::AddLayer(CLayer * _pLayer)
{
	if (m_iLayerCount >= MAX_LAYER)
	{
		assert(NULL);
	}
	_pLayer->SetIdx(m_iLayerCount);
	m_arrLayer[m_iLayerCount++] = _pLayer;
}

bool CScene::CheckLayer(const wstring & _strLayerName)
{
	for (UINT i = 0; i < (UINT)m_iLayerCount; ++i)
	{
		if (m_arrLayer[i]->GetName() == _strLayerName)
		{
			return true;
		}
	}
	return false;
}

void CScene::render()
{
	// 카메라가 기준이 되어서 layer 를 그린다.
	// 카메라는 찍고 싶은 layer만 골라서 찍는다.

	for (UINT i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->render(m_arrLayer);
	}
}


void CScene::AddGameObject(const wstring & _strLayerName, CGameObject * _pObj)
{
	for (UINT i = 0; i < m_iLayerCount; ++i)
	{
		if(m_arrLayer[i]->GetName() == _strLayerName)
		{
			m_arrLayer[i]->AddGameObject(_pObj);
			//if (0 != _pObj->GetChild().size())
			//{
			//	for(UINT i = 0;i<_pObj->GetChild().size();++i)
			//		m_arrLayer[i]->AddGameObject(_pObj->GetChild()[i]);
			//}
			return;
		}
	}
	
	assert(NULL);
}

void CScene::AddGameObject(UINT _iLayerIdx, CGameObject * _pObj)
{
	assert(_iLayerIdx < MAX_LAYER);
	m_arrLayer[_iLayerIdx]->AddGameObject(_pObj);
}

void CScene::DeleteGameObject(const wstring & _strLayerName, CGameObject * _pObj)
{
	for (UINT i = 0; i < m_iLayerCount; ++i)
	{
		if (m_arrLayer[i]->GetName() == _strLayerName)
		{
			m_arrLayer[i]->DeleteGameObject(_pObj);
			return;
		}
	}

	assert(NULL);
}

CGameObject * CScene::FindObject(const wstring & _strName)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == m_arrLayer[i])
			return nullptr;

		vector<CGameObject*>& vecObj = m_arrLayer[i]->GetObjVec();
		for (auto pObj : vecObj)
		{
			if (pObj->GetName() == _strName)
			{
				return pObj;
			}
		}
	}
	return nullptr;
}

CLayer * CScene::GetLayer(const wstring & _strLayerName)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_arrLayer[i] && m_arrLayer[i]->GetName() == _strLayerName)
			return m_arrLayer[i];

	}
	assert(NULL);
	return nullptr;
}
