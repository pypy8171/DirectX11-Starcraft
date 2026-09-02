#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class CMeshRender :
	public CComponent
{
private:
	// 둘다 자료구조로 사용해야할 듯.

	CMesh*		m_pMesh; // Ptr<CMesh>
	CMaterial*	m_pMaterial;

	CTexture*		m_pTex;

	bool			m_bClone;
	bool			m_bRender;
	bool			m_bColRender;
public:
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
	void SetMaterial(CMaterial* _pMaterial) { m_pMaterial = _pMaterial; }
	void SetTexture(CTexture* _pTex) { 
		m_pTex = _pTex;
		m_pMaterial->SetData(SHADER_PARAM::TEX_0, _pTex);
	}

	CMesh* GetMesh() { return m_pMesh; }
	CMaterial* GetMaterial() { return m_pMaterial; }
	CMaterial* GetSharedMaterial() { return m_pMaterial; }
	CMaterial* GetCloneMaterial();
	CTexture* GetTexture() { return m_pTex;}

public:
	virtual int update();
	void render();

public:
	void SetRender(bool _bool) { m_bRender = _bool; }
	bool& GetRender() { return m_bRender; }

public:
	CLONE(CMeshRender);
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CMeshRender();
	virtual ~CMeshRender();
};