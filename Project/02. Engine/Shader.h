#pragma once
#include "Entity.h"

class CBlendState;
class CDepthStencilState;

struct tParamInfo
{
	wstring			strParamName;
	SHADER_PARAM	eType;
};

class CShader :
	public CEntity
{
private:
	// Ω¶¿Ã¥ı ƒ⁄µÂ ¿˙¿Â
	ID3DBlob*				m_pVSBlob;
	ID3DBlob*				m_pHsBlob;
	ID3DBlob*				m_pDsBlob;
	ID3DBlob*				m_pGSBlob;
	ID3DBlob*				m_pCSBlob;
	ID3DBlob*				m_pPSBlob;
	ID3DBlob*				m_pRSBlob;

	ID3DBlob*				m_pErrBlob;

	// Ω¶¿Ã¥ı ∞¥√º
	ID3D11VertexShader*		m_pVS;
	ID3D11HullShader*		m_pHS;
	ID3D11DomainShader*		m_pDS;
	ID3D11GeometryShader*	m_pGS;
	ID3D11ComputeShader*	m_pCS;
	ID3D11PixelShader*		m_pPS;
	ID3D11RasterizerState*	m_pRS;

	vector<tParamInfo>		m_vecParam;
	CBlendState*			m_pBlendState;
	CDepthStencilState*		m_pDepthStencilState;

	RASTERIZER_TYPE			m_eRSType;

public:
	virtual int update() { return 0;}
	virtual void UpdateData();

public:
	ID3DBlob* GetVSBlob() { return m_pVSBlob; }
	const vector<tParamInfo>& GetParamInfo() { return m_vecParam; }

public:
	int CreateVertexShader(const wstring& _strFileName, const string& _strFuncName, const string& _strVersion);
	int CreatePixelShader(const wstring& _strFileName, const string& _strFuncName, const string& _strVersion);

public:
	//void CreateShaderParam();
	void AddShaderParam(const wstring& _strParamName, SHADER_PARAM _eType)
	{
		m_vecParam.push_back(tParamInfo{ _strParamName , _eType });
	}
	void SetBlendState(CBlendState* _pBlendState) { m_pBlendState = _pBlendState; }
	void SetDepthStencilState(CDepthStencilState* _pDSState) { m_pDepthStencilState = _pDSState; }
	void SetRSType(RASTERIZER_TYPE _eType) { m_eRSType = _eType; }

public:
	CLONE(CShader);

public:
	CShader();
	~CShader();
};

