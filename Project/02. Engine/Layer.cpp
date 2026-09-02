#include "Layer.h"

#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"
#include "SceneMgr.h"

#include "Scene.h"

CLayer::CLayer()
	: m_iLayerIdx(-1)
{
}


CLayer::~CLayer()
{
	Safe_Delete_Vec(m_pParentList);
}

void CLayer::awake()
{
	for (auto& pObj : m_pParentList)
	{
		pObj->awake();
		//for(UINT i = 0;i<pObj->GetChild().size();++i)
		//	pObj->GetChild()[i]->awake();
	}

}

void CLayer::start()
{
	for (auto& pObj : m_pParentList)
	{
		pObj->start();
		//for (UINT i = 0; i<pObj->GetChild().size(); ++i)
		//	pObj->GetChild()[i]->start();
	}
}

int CLayer::update()
{
	for (auto& pObj : m_pParentList)
	{
		pObj->update();
		//for (UINT i = 0; i<pObj->GetChild().size(); ++i)
		//	pObj->GetChild()[i]->update();
	}
	return 0;
}

int CLayer::lateupdate()
{
	for (auto& pObj : m_pParentList)
	{
		pObj->lateupdate();
		//for (UINT i = 0; i<pObj->GetChild().size(); ++i)
		//	pObj->GetChild()[i]->lateupdate();
	}
	return 0;
}

int CLayer::finalupdate()
{
	for (auto& pObj : m_pParentList)
	{
		pObj->finalupdate();
		//for (UINT i = 0; i<pObj->GetChild().size(); ++i)
		//	pObj->GetChild()[i]->finalupdate();
	}
	return 0;
}

void CLayer::render()
{
	for (auto& pObj : m_AllObject)
	{
		pObj->render();
	
		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
		if (pScene->GetName() != L"StudyScene")
		{
			if (pObj->GetLayerIdx() == pScene->GetLayer(L"Ally")->GetIdx())
			{
				vector<CGameObject*> vec = pScene->GetLayer(L"Ally")->GetObjVec();
				sort(m_pParentList.begin(), m_pParentList.end(), [](CGameObject* pObj1, CGameObject* pObj2)
				{
					return pObj1->Transform()->GetLocalPos().y < pObj2->Transform()->GetLocalPos().y;
				});
			}
		}
	}

	m_AllObject.clear();

	for (auto& pObj : m_pParentList)
	{
		CScene* pScene = CSceneMgr::GetInst()->GetCurrentScene();
		if (pObj->GetLayerIdx() == pScene->GetLayer(L"Ally")->GetIdx())
		{
			vector<CGameObject*> vec = pScene->GetLayer(L"Ally")->GetObjVec();
			sort(m_pParentList.begin(), m_pParentList.end(), [](CGameObject* pObj1, CGameObject* pObj2)
			{
				return pObj1->Transform()->GetLocalPos().y < pObj2->Transform()->GetLocalPos().y;
			});
		}


		pObj->render();
		for (UINT i = 0; i<pObj->GetChild().size(); ++i)
			pObj->GetChild()[i]->render();
	}
}

#include <iostream>
using namespace std;

void CLayer::AddGameObject(CGameObject * _pObj,bool _bAll) // mfc 로 이걸 전부 옮김 or no 구현하기
{
	//// Object 가 다른 Layer 소속인 경우
	if (-1 != _pObj->GetLayerIdx() && nullptr != _pObj->GetParent())
	{
		CSceneMgr::GetInst()->GetLayer(_pObj->GetLayerIdx())->PopParentObj(_pObj);
	}

	m_pParentList.push_back(_pObj);

	list<CGameObject*> childObj;
	childObj.push_back(_pObj);

	// 전부 옮긴다.
	if (_bAll)
	{
		while (!childObj.empty())
		{
			CGameObject* pObj = childObj.front();
			childObj.pop_front();

			pObj->SetLayerIdx(m_iLayerIdx);

			vector<CGameObject*>& vecChild = pObj->GetChild();
			for (UINT i = 0; i < vecChild.size(); ++i)
			{
				childObj.push_back(vecChild[i]);
			}
		}
	}

	//m_pParentList.push_back(_pObj);
	//_pObj->SetLayerIdx(m_iLayerIdx);
}

void CLayer::PopParentObj(CGameObject * _pObj)
{
	vector<CGameObject*>::iterator iter = m_pParentList.begin();
	for (; iter != m_pParentList.end(); ++iter)
	{
		if (*iter == _pObj)
		{
			m_pParentList.erase(iter);
			return;
		}
	}
	assert(NULL);
}

// 예약 삭제해야 한다.
void CLayer::DeleteGameObject(CGameObject * _pObj)
{

}
