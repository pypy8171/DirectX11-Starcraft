#pragma once
#include "Entity.h"

class CComponent;
class CTransform;
class CMeshRender;
class CScript;
class CCamera;
class CCollider;
class CAnimator2D;
class CGrid;
class CLight;

template<typename T>
struct ID
{
	typedef T Type;
};

class CGameObject :
	public CEntity
{
private:
	CGameObject *				m_pParent;
	CComponent *				m_arrCom[(UINT)COMPONENT_TYPE::END];
	vector<CScript*>			m_vecScript;
	vector<CGameObject*>		m_vecChild;

	int							m_iLayerIdx;
	bool						m_bActive;
	bool						m_bIsDead;
	bool						m_bClicked;
	bool						m_bTargetted;
	bool						m_bOccupied;
	bool						m_bColOccupied;
	bool						m_bColRender;
	UNIT_STATUS					m_eUnitStatus;
	OBJ_TYPE					m_eObjType;

	CGameObject*				m_pTargetObj;

public:
	virtual void awake();
	virtual void start();
	virtual int update();
	virtual int lateupdate();
	virtual int finalupdate();

	void render();

public:
	void DeleteScript() { m_vecScript.clear(); }
	void DeleteComponent() {
		for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
		{
			m_arrCom[i] = NULL;
		}
	}

public:
	void AddChild(CGameObject* _pChild);
	int AddComponent(CComponent* _pComponent);
	int AddComponent(COMPONENT_TYPE _eType, CComponent* _pComponent);


public:
	CComponent * GetComponent(COMPONENT_TYPE _eType) {return m_arrCom[(UINT)_eType];}
	CTransform* Transform() { return (CTransform*)GetComponent(COMPONENT_TYPE::TRANSFORM); }
	CMeshRender* MeshRender() { return (CMeshRender*)GetComponent(COMPONENT_TYPE::MESHRENDER); }
	CCamera* Camera() { return (CCamera*)GetComponent(COMPONENT_TYPE::CAMERA); }
	CCollider* Collider() { return (CCollider*)GetComponent(COMPONENT_TYPE::COLLIDER); }
	CAnimator2D* Animator2D() { return (CAnimator2D*)GetComponent(COMPONENT_TYPE::ANIMATOR2D); }
	CGrid* Grid() { return (CGrid*)GetComponent(COMPONENT_TYPE::GRID); }
	vector<CScript*>& Script() { return m_vecScript; }
	//CLight* Light() { return (CLight*)GetComponent(COMPONENT_TYPE::LIGHT); } // 포폴때꺼야함

	int& GetLayerIdx() { return m_iLayerIdx; }
	void SetLayerIdx(int _iIdx) { m_iLayerIdx = _iIdx; }

	CGameObject* GetParent() { return m_pParent; }
	vector<CGameObject*>& GetChild() { return m_vecChild; }
	bool IsAncestor(CGameObject* _pObject);

	//CScript* GetScriptElement(const wstring& _strname)
	//{
	//	for (size_t i = 0; i < m_vecScript.size(); ++i)
	//	{
	//		if (_strname == m_vecScript[i]->GetName())
	//		{
	//			return m_vecScript[i];
	//		}
	//	}
	//	return nullptr;
	//}

public:
	void SetActive(bool _bool) { m_bActive = _bool; }
	bool& GetActive() { return m_bActive; }

	void SetOccupied(bool _bool) { m_bOccupied = _bool; }
	bool& GetOccupied() { return m_bOccupied; }

	void SetColOccupied(bool _bool) { m_bColOccupied = _bool; }
	bool& GetColOccupied() { return m_bColOccupied; }

private:
	void SetParent(CGameObject* _pParent){m_pParent = _pParent;}

	void DisconnectParent();
	void Isolate();
	void Kill() {m_bIsDead = true;}

public: // 게임오브잭트로 받는게 좋을듯한데
	void SetClicked(bool _bTarget) { m_bClicked = _bTarget; }
	bool GetClicked() { return m_bClicked; }

	void SetTargetted(bool _bTarget) { m_bTargetted = _bTarget; }
	bool GetTargetted() { return m_bTargetted; }

	void SetUnitStatus(UNIT_STATUS _eUnitStatus) { m_eUnitStatus = _eUnitStatus; }
	const UNIT_STATUS& GetUnitStatus() { return m_eUnitStatus; }

	void SetObjType(OBJ_TYPE _eObjType) { m_eObjType = _eObjType; }
	const OBJ_TYPE& GetObjType() { return m_eObjType; }

	void SetTarget(CGameObject* _pTargetObject) { m_pTargetObj = _pTargetObject; }
	CGameObject* GetTargetObj() { return m_pTargetObj; }

public:
	void Save(FILE* _pFile);
	void Load(FILE* _pFile);

public:
	CLONE(CGameObject);

public:
	CGameObject();
	CGameObject(const CGameObject& _other);
	virtual ~CGameObject();

	friend class CLayer;
	friend class CEventMgr;
};


//	template<typename T>
//	int AddComponent(T* _pComponent)
//	{ C
//		AddComponent(_pComponent, ID<T>());
//		return 0;
//	}
//
//private:
//	template<typename T>
//	int AddComponent(T* _pComponent, ID<T> _type);
//	int AddComponent(CScript* _pScript, ID<CScript> _type);

//
//template<typename T>
//inline int CGameObject::AddComponent(T * _pComponent, ID<T> _type)
//{
//
//	static const type_info& info = typeid(T);
//
//	static const type_info& transform = typeid(CTransform);
//	static const type_info& meshrender = typeid(CMeshRender);
//	static const type_info& camera = typeid(CCamera);
//
// 	COMPONENT_TYPE eType = COMPONENT_TYPE::END;
//	if (&transform == &info)
//	{
//		eType = COMPONENT_TYPE::TRANSFORM;
//	}
//	else if (&meshrender == &info)
//	{
//		eType = COMPONENT_TYPE::MESHRENDER;
//	}
//	else if (&camera == &info)
//	{
//		eType = COMPONENT_TYPE::CAMERA;
//	}
//
//	if (NULL != m_arrCom[(UINT)eType])
//		return RET_FAILED;
//
//	m_arrCom[(UINT)eType] = _pComponent;
//	_pComponent->SetGameObject(this);
//	return RET_SUCCESS;
//}
