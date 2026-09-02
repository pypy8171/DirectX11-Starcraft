#pragma once
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
#include "Layer.h"

class CCollider :
	public CComponent
{
private:
	static DWORD	g_iID;

private:
	map<wstring, UINT>				m_mapColliderType; // 툴에서 사용하기 위한 용도
	//wstring							m_arrColliderType[(int)COLLIDER_TYPE::END];
	COLLIDER_TYPE					m_eType;
	Vec3							m_vOffsetPos;
	Vec3							m_vOffsetScale;
	Vec3							m_vRot;

	Matrix							m_matCol;
	CMaterial*					m_pMtrl;
	CMaterial*					m_pCloneMtrl;
	CMesh*						m_pMesh;

	// COLLIDE ID  // ID 만드는 알고리즘 있으면 좋을듯 비면 넣어주고
	DWORD							m_dwID;

	bool							m_bCollide;
	float							m_fRadius;
	float							m_fFinalRadius;

public:
	void SetOffsetPos(const Vec3& _vOffset) { m_vOffsetPos = _vOffset; }
	void SetOffsetScale(const Vec3& _vScale) { m_vOffsetScale = _vScale; }
	void SetRot(const Vec3& _vRot) { m_vRot = _vRot; }

	const Vec3& GetOffsetPos() { return m_vOffsetPos; }
	const Vec3& GetOffsetScale() { return m_vOffsetScale; }	
	const Matrix& GetCollideMat() { return m_matCol; }

	const DWORD& GetID() { return m_dwID; }

	const float GetFinalRadius() { return m_fFinalRadius; }

public:
	void SetMaterial(CMaterial* _pMaterial) { m_pMtrl = _pMaterial; }

public:
	void CalColliderMat();

public:
	virtual int update();
	virtual int finalupdate();
	void render();

public:
	CMaterial * GetMtrl() { return m_pMtrl; }
	CMaterial* GetCloneMtrl() { m_pCloneMtrl = m_pMtrl->Clone(); return m_pCloneMtrl; }

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	void SetColliderType(COLLIDER_TYPE _eType);
	const COLLIDER_TYPE& GetColliderType() { return m_eType; }

	const map<wstring,UINT>& GetColliderMap() { return m_mapColliderType; }
	//const wstring& GetColliderArr() { return m_arrColliderType[0]; }

	CMesh* GetColliderMesh() { return m_pMesh; }

public:
	CLONE(CCollider);
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CCollider();
	CCollider(const CCollider& _other);
	virtual ~CCollider();
};

