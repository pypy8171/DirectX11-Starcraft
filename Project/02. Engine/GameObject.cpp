#include "GameObject.h"

#include "Transform.h"
#include "MeshRender.h"
#include "Grid.h"
#include "Camera.h"
#include "Collider.h"
#include "Animator2D.h"
#include "Light.h"


#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Layer.h"

#include "Script.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_pParent(NULL)
	, m_bIsDead(false)
	, m_bClicked(false)
	, m_bActive(true)
	, m_bTargetted(false)
	, m_bOccupied(false)
	, m_bColOccupied(false)
	, m_iLayerIdx(-1)
	, m_eUnitStatus(UNIT_STATUS::IDLE)
	, m_eObjType(OBJ_TYPE::NONE)
	, m_pTargetObj(nullptr)
	, m_bColRender(false)
{
	AddComponent(new CTransform);
}

CGameObject::CGameObject(const CGameObject & _other)
	: CEntity(_other)
	, m_pParent(nullptr)
	, m_arrCom{}
	, m_iLayerIdx(-1)
	, m_bActive(true) // m_vecScript // 벡터는 알아서 기본 초기화
	, m_bClicked(false)
	, m_bTargetted(false)
	, m_bOccupied(false)
	, m_eObjType(OBJ_TYPE::NONE)
	, m_pTargetObj(nullptr)
	, m_bColRender(false)
{
	this->m_eObjType = _other.m_eObjType;
	// 컴포넌트(Script 포함) 깊은복사
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != _other.m_arrCom[i])
		{
			AddComponent((CComponent*)_other.m_arrCom[i]->Clone());
		}
	}

	for (UINT i = 0; i < _other.m_vecScript.size(); ++i)
	{
		AddComponent((CComponent*)_other.m_vecScript[i]->Clone());
	}

	// 자식 오브젝트 깊은복사
	for (UINT i = 0; i < _other.m_vecChild.size(); ++i)
	{
		AddChild(_other.m_vecChild[i]->Clone());
	}


	// 자식 오브젝트 깊은 복사
}


CGameObject::~CGameObject()
{

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrCom[i]);
	}

	//for (UINT i = 0; i < m_vecChild.size(); ++i)
	//{
	//	SAFE_DELETE(m_vecChild[i]);
	//}
	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		//for (int j = 0; j < m_vecChild[i]->Script().size(); ++j)
		//{
		//	SAFE_DELETE(m_vecChild[i]->Script()[j]);
		//}
		SAFE_DELETE(m_vecChild[i]);
	}

	Safe_Delete_Vec(m_vecScript); // 같은 스크립트 써서 이전에 지워진애 또 지우려 할때 문제생김
	
	//Safe_Delete_Vec(m_vecChild);
}

void CGameObject::awake()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
		{
			m_arrCom[i]->awake();
		}
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->awake();
	}

	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->awake();
	}
}

void CGameObject::start()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
		{
			m_arrCom[i]->start();
		}
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->start();
	}

	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->start();
	}

}

int CGameObject::update()
{
	if (KEYAWAY(KEY_TYPE::KEY_0))
	{
		if (!m_bColRender)
			m_bColRender = true;
		else if (m_bColRender)
			m_bColRender = false;
	}

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
		{
			m_arrCom[i]->update();
		}
	}


	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->update();
	}

	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->update();
	}

	return 0;
}

int CGameObject::lateupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
		{
			m_arrCom[i]->lateupdate();
		}
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->lateupdate();
	}

	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->lateupdate();
	}

	return 0;
}

int CGameObject::finalupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
		{
			m_arrCom[i]->finalupdate();
		}
	}

	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finalupdate();
	}

	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finalupdate();

	}
	CLayer* pMyLayer = CSceneMgr::GetInst()->GetLayer(m_iLayerIdx);
	pMyLayer->RegisterObj(this);

	return 0;
}

void CGameObject::render()
{
	//if (MeshRender() == NULL)
	//	return;

	//MeshRender()->render();
	

	if (MeshRender() != NULL)
	{
		MeshRender()->render();
	}

	if (Grid() != NULL)
	{
		Grid()->render();
	}

	if (Collider() != NULL && MeshRender()->GetRender())
	{
		if(L"Drag" == GetName())
			Collider()->render();

		if (m_bColRender)
			Collider()->render();

		// grid 콜라이더 랜더해야됨
	}

	for (UINT i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->render();
	}
}

void CGameObject::AddChild(CGameObject * _pChild)
{
	assert(!(IsAncestor(_pChild)));

	if (NULL == _pChild->GetParent())
	{
		// 자식으로 들어온 오브젝트가 최상위 부모였다면
		// Layer 에서 최상위 오브젝트 해제
		CLayer* pLayer = CSceneMgr::GetInst()->GetLayer(_pChild->GetLayerIdx());
		if(nullptr != pLayer)
			pLayer->PopParentObj(_pChild);
	}
	else
	{
		// 이미 부모가 있었다.
		// 이전 부모와 관계를 정리한다.
		_pChild->DisconnectParent();
	}

	m_vecChild.push_back(_pChild);
	_pChild->SetParent(this);
	_pChild->SetLayerIdx(_pChild->GetParent()->GetLayerIdx());
}

int CGameObject::AddComponent(CComponent * _pComponent)
{
	COMPONENT_TYPE eType = _pComponent->GetComponentType();

	if (COMPONENT_TYPE::SCRIPT == eType)
	{
		m_vecScript.push_back((CScript*)_pComponent);
	}
	else
	{
		// 이미 해당 컴포넌트가 있다.
		if (NULL != m_arrCom[(UINT)eType])
			assert(NULL);

		m_arrCom[(UINT)eType] = _pComponent;
	}

	_pComponent->SetGameObject(this);

	return RET_SUCCESS;
}

int CGameObject::AddComponent(COMPONENT_TYPE _eType, CComponent * _pComponent)
{
	if (COMPONENT_TYPE::SCRIPT == _eType)
	{
		m_vecScript.push_back((CScript*)_pComponent);
	}
	else
	{
		// 이미 해당 컴포넌트가 있다.
		if (NULL != m_arrCom[(UINT)_eType])
			assert(NULL);

		m_arrCom[(UINT)_eType] = _pComponent;
	}

	_pComponent->SetGameObject(this);

	return RET_SUCCESS;
}

//int CGameObject::AddComponent(CScript * _pScript, ID<CScript> _type)
//{
//	m_vecScript.push_back(_pScript);
//	
//	_pScript->SetGameObject(this);
//	return 0;
//}

bool CGameObject::IsAncestor(CGameObject* _pObject)
{
	assert(_pObject);

	CGameObject* pParent = m_pParent;
	while (pParent) // NULL 이라면 어차피 안돌아감 assert는 그냥 잘못된거 체크용
	{
		if (_pObject == pParent)
			return true;

		pParent = pParent->m_pParent;
	}

	return false;
}

void CGameObject::DisconnectParent()
{
	if (nullptr == m_pParent) // hierachydlg 때문에 만듬. 드래그 앤 드랍할때 최상위 드랍하면 터져서 
		return;

	assert(m_pParent); // NULL 이라면 어설트

	// 레이어는 최상위 오브젝트만 등록되어 있으니 최상위가 된 애들은 레이어에 등록

	CSceneMgr::GetInst()->GetLayer(m_iLayerIdx)->AddGameObject(this);

	for (UINT i = 0; i < m_pParent->m_vecChild.size(); ++i)
	{
		if (this == m_pParent->m_vecChild[i])
		{
			m_pParent->m_vecChild.erase(m_pParent->m_vecChild.begin() + i);
			m_pParent = nullptr;
			return;
		}
	}

	assert(nullptr);
}

void CGameObject::Isolate()
{
	if (!m_pParent)
	{
		CSceneMgr::GetInst()->GetLayer(m_iLayerIdx)->PopParentObj(this);
	}
	else
	{
		DisconnectParent();
	}
}

void CGameObject::Save(FILE* _pFile)
{
	SaveWString(GetName(), _pFile);
	fwrite(&m_bActive, sizeof(bool), 1, _pFile);
	//fwrite(&&m_bOccupied, sizeof(bool),1,_pFile);
	fwrite(&m_eObjType, sizeof(UINT), 1, _pFile);
	//Component 저장
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			fwrite(&i, sizeof(UINT), 1, _pFile);
			m_arrCom[i]->Save(_pFile);
		}
	}

	int End = (UINT)COMPONENT_TYPE::END;
	fwrite(&End, sizeof(UINT), 1, _pFile);


}

void CGameObject::Load(FILE* _pFile)
{
	SetName(LoadWString(_pFile));
	fread(&m_bActive, sizeof(bool), 1, _pFile);
	//fread(&&m_bOccupied, sizeof(bool),1,_pFile);
	fread(&m_eObjType, sizeof(UINT), 1, _pFile);
	// Component 불러오기
	int iComType = -1;
	CComponent* pCom = nullptr;
	bool bEnd = false;


	while (!bEnd)
	{
		fread(&iComType, sizeof(UINT), 1, _pFile);

		switch ((COMPONENT_TYPE)iComType)
		{
		case COMPONENT_TYPE::TRANSFORM:
			m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]->Load(_pFile);
			break;
		case COMPONENT_TYPE::MESHRENDER:
			pCom = new CMeshRender();
			pCom->Load(_pFile);
			AddComponent(pCom);
			break;
		case COMPONENT_TYPE::COLLIDER:
			pCom = new CCollider();
			pCom->Load(_pFile);
			AddComponent(pCom);
			break;
		case COMPONENT_TYPE::CAMERA:
			pCom = new CCamera();
			pCom->Load(_pFile);
			AddComponent(pCom);
			break;
		case COMPONENT_TYPE::ANIMATOR2D:
			pCom = new CAnimator2D();
			pCom->Load(_pFile);
			AddComponent(pCom);
			break;
		case COMPONENT_TYPE::ANIMATOR3D:
			break;
		case COMPONENT_TYPE::GRID:
			pCom = new CGrid();
			pCom->Load(_pFile);
			AddComponent(pCom);
			break;
		//case COMPONENT_TYPE::LIGHT:
		//	pCom = new CLight();
		//	pCom->Load(_pFile);
		//	AddComponent(pCom);
		//	break;
		case COMPONENT_TYPE::END:
			bEnd = true;
			continue;
			break;
		default:
			assert(nullptr);
			break;
		}

	}
}
