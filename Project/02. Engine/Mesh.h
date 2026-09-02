#pragma once
#include "Res.h"

class CShader;

class CMesh :
	public CRes
{
private:
	ID3D11Buffer*			m_pVB[2];
	ID3D11Buffer*			m_pIB;
	ID3D11Buffer*			m_pInstanceBuff;
	ID3D11InputLayout*		m_pLayout;

	D3D_PRIMITIVE_TOPOLOGY	m_eTopology;

	D3D11_BUFFER_DESC		m_tVtxDesc;
	D3D11_BUFFER_DESC		m_tIdxDesc;
	D3D11_BUFFER_DESC		m_tInstDesc;

	UINT					m_iVtxSize;
	UINT					m_iVtxCount;
	UINT					m_iIdxSize;
	UINT					m_iIdxCount;

	void*					m_pVtxMem; // ? 
	void*					m_pIdxMem; // ? 

	vector<D3D11_INPUT_ELEMENT_DESC>	m_vecLayout; // 이거 이해 안됨
	ID3DBlob*							m_pVtxBlob;



public:
	void render();

public:
	static CMesh* Create(void* _pVtx, UINT _iVtxSize, UINT _iVtxCount, D3D11_USAGE _eVtxUsage
		, void* _pIdx, UINT _iIdxSize, UINT _iIdxCount, D3D11_USAGE _eIdxUsage
	, D3D_PRIMITIVE_TOPOLOGY _eTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	virtual void UpdateData();
	void SetShader(CShader* _pShader);

public:
	virtual void Load(const wstring& _strFullPath, const wstring& _strKey) {};

public:
	virtual void FileSave(FILE* _pFile);
	static void FileLoad(FILE* _pFile);

	CLONE_DISABLE(CMesh);
public:
	CMesh();
	virtual ~CMesh();
};

