#include "Shader.h"

#include "Device.h"
#include "PathMgr.h"

#include "BlendState.h"
#include "DepthStencilState.h"

CShader::CShader()
	: m_pVS(NULL)
	, m_pHS(NULL)
	, m_pDS(NULL)
	, m_pCS(NULL)
	, m_pPS(NULL)
	, m_pRS(NULL)
	, m_pVSBlob(NULL)
	, m_pHsBlob(NULL)
	, m_pDsBlob(NULL)
	, m_pCSBlob(NULL)
	, m_pPSBlob(NULL)
	, m_pRSBlob(NULL)
	, m_pErrBlob(NULL)
	, m_pBlendState(nullptr)
	, m_pDepthStencilState(nullptr)
	, m_eRSType(RASTERIZER_TYPE::CULL_BACK)
{
}

CShader::~CShader()
{
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pHS);
	SAFE_RELEASE(m_pDS);
	SAFE_RELEASE(m_pCS);
	SAFE_RELEASE(m_pPS);
	SAFE_RELEASE(m_pRS);
	SAFE_RELEASE(m_pVSBlob);
	SAFE_RELEASE(m_pHsBlob);
	SAFE_RELEASE(m_pDsBlob);
	SAFE_RELEASE(m_pCSBlob);
	SAFE_RELEASE(m_pPSBlob);
	SAFE_RELEASE(m_pRSBlob);
	SAFE_RELEASE(m_pErrBlob);
}

void CShader::UpdateData()
{
	CONTEXT->VSSetShader(m_pVS, NULL, NULL);
	CONTEXT->PSSetShader(m_pPS, NULL, NULL);

	// 기본 상태를 사용하도록 밀어버려야 한다. 아니면 이전 쉐이더에서 사용하던 블렌드 상태를 사용하게 된다.
	// BlendState Setting
	if (nullptr != m_pBlendState)
		m_pBlendState->SetState();
	else
		m_pBlendState->SetDefaultState(); // CBlendState::SetDefaultState();

	// 포폴 쓸땐 이 부분 주석
	// DepthStencilState
	//if (nullptr != m_pDepthStencilState)
	//	m_pDepthStencilState->SetState();
	//else
	//	m_pDepthStencilState->SetDefaultState();
	//
	//// RASTERIZER STATE Setting
	//CDevice::GetInst()->SetRSState(m_eRSType);
}

int CShader::CreateVertexShader(const wstring & _strFileName, const string & _strFuncName, const string & _strVersion)
{
	wstring strFilePath = CPathMgr::GetResPath();
	strFilePath += L"Shader\\";
	strFilePath += _strFileName;

	string strErr;

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	if (FAILED(D3DCompileFromFile(strFilePath.c_str(), NULL
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), _strVersion.c_str(), iFlag, 0, &m_pVSBlob, &m_pErrBlob)))
	{
		strErr = (char*)m_pErrBlob->GetBufferPointer();
		MessageBoxA(NULL, strErr.c_str(), "쉐이더 생성 실패", MB_OK);
		return RET_FAILED;
	}

	DEVICE->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize()
		, NULL, &m_pVS);

	return RET_SUCCESS;
}

int CShader::CreatePixelShader(const wstring & _strFileName, const string & _strFuncName, const string & _strVersion)
{
	wstring strFilePath = CPathMgr::GetResPath();
	strFilePath += L"Shader\\";
	strFilePath += _strFileName;

	string strErr;

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	if (FAILED(D3DCompileFromFile(strFilePath.c_str(), NULL
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), _strVersion.c_str(), iFlag, 0, &m_pPSBlob, &m_pErrBlob)))
	{
		strErr = (char*)m_pErrBlob->GetBufferPointer();
		MessageBoxA(NULL, strErr.c_str(), "쉐이더 생성 실패", MB_OK);
		return RET_FAILED;
	}

	DEVICE->CreatePixelShader(m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize()
		, NULL, &m_pPS);

	return RET_SUCCESS;
}