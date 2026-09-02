#pragma once
#include "Res.h"

#include "Texture.h"
#include "Ptr.h"

#include "Shader.h"

class CMaterial :
	public CRes
{
private:
	CShader *		m_pShader;
	tShaderParam	m_tParam;
	CTexture*	m_arrTex[(UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0];

	vector<tParamInfo>  m_vecParam;

public:
	virtual void UpdateData();

	void SetShader(CShader* _pShader)
	{
		assert(_pShader); // nullÀÌ¸é assert
		m_pShader = _pShader;
		m_vecParam = m_pShader->GetParamInfo();
	}

	CShader* GetShader() { return m_pShader; }

public:
	void SetData(SHADER_PARAM _eType, void* _pData);
	CTexture* GetTexture() { return m_arrTex[0]; }
	//void SetTexture(CTexture* _Texture);

public:
	virtual void Load(const wstring& _strFullPath, const wstring& _strKey);

public:
	virtual void FileSave(FILE* _pFile);
	static void FileLoad(FILE* _pFile);

public:
	CMaterial* Clone();

public:
	CMaterial();
	virtual ~CMaterial();
};

