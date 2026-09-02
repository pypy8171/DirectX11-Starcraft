#pragma once
#include "Component.h"
#include "Prefab.h"
#include "Material.h"
//class CMaterial;

class CScript :
	public CComponent
{
private:
	UINT	m_iScriptType;

private:
	CMaterial*	m_pMtrl;

public:
	void Instantiate(CPrefab* _pPrefab, const wstring& _strLayerName, const Vec3 vLocalPos,const Vec3 vLocalAngle);
protected:
	void DestroyObj(CGameObject* _pObject);
	void DestroyObj();
	void DisconnectParent(CGameObject* _pObject);
	void DisconnectParent();

	void AddChild(CGameObject* _pChild);
	void AddChild(CGameObject* _pParent, CGameObject* _pChild);

public:
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};	

public:
	void SetScriptType(UINT _iType) { m_iScriptType = _iType; }
	UINT GetScriptType() { return m_iScriptType; }

public:
	void SetMaterial(CMaterial* _pMtrl) { m_pMtrl = _pMtrl;}
	CMaterial* GetMaterial() { return m_pMtrl; }

public:
	virtual void Save(FILE* _pFile) {};
	virtual void Load(FILE* _pFile) {};

public:
	CScript();
	virtual ~CScript();
};