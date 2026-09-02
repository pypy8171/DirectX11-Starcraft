#include "Texture.h"

#include "PathMgr.h"
#include "ResMgr.h"
#include "Device.h"

CTexture::CTexture()
	: m_pSRView(nullptr)
	, m_pTex(nullptr)
{
}

CTexture::~CTexture()
{
	SAFE_RELEASE(m_pSRView);
	SAFE_RELEASE(m_pTex);
}
	
void CTexture::Load(const wstring & _strFullPath, const wstring & _strKey)
{
	wchar_t szExt[20] = {};
	_wsplitpath_s(_strFullPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);
	
	// dds
	if (!wcscmp(szExt, L".dds"))
	{
		if (FAILED(LoadFromDDSFile(_strFullPath.c_str(), DDS_FLAGS_NONE, NULL, m_Image)))
		{
			assert(nullptr);
		}
	}
	else if (!wcscmp(szExt, L".tga"))
	{
		if (FAILED(LoadFromTGAFile(_strFullPath.c_str(), NULL, m_Image)))
			assert(nullptr);
	}
	else // png, jpg, jpeg, bmp
	{
		if (FAILED(LoadFromWICFile(_strFullPath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, NULL, m_Image)))
			assert(nullptr);
	}

	CreateShaderResourceView(DEVICE
		, m_Image.GetImages()
		, m_Image.GetImageCount()
		, m_Image.GetMetadata(), &m_pSRView);

	m_pSRView->GetResource((ID3D11Resource**)&m_pTex);

}

void CTexture::SetRegister(UINT _iShaderType, UINT _iRegister)
{
	if (_iShaderType & SHADER_TYPE::ST_VERTEX)
		CONTEXT->VSSetShaderResources(_iRegister, 1, &m_pSRView);
	if (_iShaderType & SHADER_TYPE::ST_HULL)
		CONTEXT->HSSetShaderResources(_iRegister, 1, &m_pSRView);
	if (_iShaderType & SHADER_TYPE::ST_DOMAIN)
		CONTEXT->DSSetShaderResources(_iRegister, 1, &m_pSRView);
	if (_iShaderType & SHADER_TYPE::ST_GEOMETRY)
		CONTEXT->GSSetShaderResources(_iRegister, 1, &m_pSRView);
	if (_iShaderType & SHADER_TYPE::ST_COMPUTE)
		CONTEXT->CSSetShaderResources(_iRegister, 1, &m_pSRView);
	if (_iShaderType & SHADER_TYPE::ST_PIXEL)
		CONTEXT->PSSetShaderResources(_iRegister, 1, &m_pSRView);
}

void CTexture::SetRegisterAll(UINT _iRegister)
{
	CONTEXT->VSSetShaderResources(_iRegister, 1, &m_pSRView);
	CONTEXT->HSSetShaderResources(_iRegister, 1, &m_pSRView);
	CONTEXT->DSSetShaderResources(_iRegister, 1, &m_pSRView);
	CONTEXT->GSSetShaderResources(_iRegister, 1, &m_pSRView);
	CONTEXT->CSSetShaderResources(_iRegister, 1, &m_pSRView);
	CONTEXT->PSSetShaderResources(_iRegister, 1, &m_pSRView);
}

tTexInfo CTexture::GetTextureInfo(const wstring & _strKey)
{
	map<wstring, tTexInfo>::iterator iter = mapTexture.find(_strKey);

	if (iter == mapTexture.end())
		return tTexInfo();

	return iter->second;
}

void CTexture::FileSave(FILE * _pFile)
{
	// 키값
	SaveWString(GetName(), _pFile);

	// 상대경로
	SaveWString(m_strPath, _pFile);
}

void CTexture::FileLoad(FILE * _pFile)
{
	// 키값
	wstring strKey, strPath;
	strKey = LoadWString(_pFile);

	// 상대경로
	strPath = LoadWString(_pFile);

	// 해당 키로 등록된게 없으면 로딩
	if (nullptr == CResMgr::GetInst()->Load<CTexture>(strKey))
		CResMgr::GetInst()->Load<CTexture>(strKey, strPath);
}
