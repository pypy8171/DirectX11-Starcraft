#pragma once
#include "Entity.h"

#include "GameObject.h"

#include "Ptr.h"

class CComponent :
	public CEntity
{
private:
	COMPONENT_TYPE		m_eType;
	CGameObject*		m_pGameObject;
	bool				m_bActive;


protected:
	void SetComponentType(COMPONENT_TYPE _eType) { m_eType = _eType; }
	CTransform* Transform() { return m_pGameObject->Transform(); }
	CMeshRender* MeshRender() { return m_pGameObject->MeshRender(); }
	CCamera* Camera() { return m_pGameObject->Camera(); }
	CCollider* Collider() { return m_pGameObject->Collider(); }
	vector<CScript*>& Script() { return m_pGameObject->Script(); }
	CAnimator2D* Animator2D() { return m_pGameObject->Animator2D(); }
	CGameObject* ParentObject() { return m_pGameObject->GetParent(); }
	CGrid* Grid() { return m_pGameObject->Grid(); }

public:
	CGameObject* Object() { return m_pGameObject; }

private:
	void SetGameObject(CGameObject* _pObject) { m_pGameObject = _pObject; }

public:
	COMPONENT_TYPE  GetComponentType() { return m_eType; }

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CComponent();
	CComponent(const CComponent& _other)
		: m_eType(_other.m_eType)
		, m_pGameObject(nullptr)
		, m_bActive(true)
	{}
	virtual ~CComponent();

	friend class CGameObject;
};