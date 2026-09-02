#pragma once
#include "Res.h"

#include "DirectXTex/DirectXTex.h"

#ifdef _DEBUG
#pragma comment(lib,"DirectX_DebugTex")
#else
#pragma comment(lib,"DirectXTex")
#endif

class CTexture :
	public CRes
{
private:
	ScratchImage					m_Image;
	ID3D11ShaderResourceView*		m_pSRView;
	ID3D11Texture2D*				m_pTex;

private:
	map<wstring, tTexInfo> mapTexture;

public:
	ID3D11ShaderResourceView * GetSRV() { return m_pSRView;}

public:
	virtual void Load(const wstring& _strFullPath, const wstring& _strKey);

	float GetWidth() { return (float)m_Image.GetMetadata().width; }
	float GetHeight() { return (float)m_Image.GetMetadata().height; }

	void SetRegister(UINT _iShaderType, UINT _iRegister);
	void SetRegisterAll(UINT _iRegister);

public:
	tTexInfo GetTextureInfo(const wstring& _strKey);

public:
	void AddTexData(tTexInfo _TexInfo) { mapTexture.insert(make_pair(_TexInfo.strTexName, _TexInfo)); }

public:
	virtual void FileSave(FILE* _pFile);
	static void FileLoad(FILE* _pFile);


public:
	CLONE_DISABLE(CTexture);

public:
	CTexture();
	virtual ~CTexture();
};