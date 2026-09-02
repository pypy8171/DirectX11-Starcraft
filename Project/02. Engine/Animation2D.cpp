#include "Animation2D.h"

#include "TimeMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"

#include "Device.h"
#include "ConstBuffer.h"

tAnim2DInfo		 g_anim2d = {};


CAnimation2D::CAnimation2D()
	: m_pOwner(nullptr)
	, m_iCurFrm(0)
	, m_iCurFrmIdx(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
	, m_bRepeat(false)
{
}


CAnimation2D::~CAnimation2D()
{
}


int CAnimation2D::update()
{
	m_fAccTime += DT;

	if (m_vecFrm[m_iCurFrm].fDuration <= m_fAccTime)
	{
		while (true)
		{
			m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;

			if(m_bRepeat == true) // 애니메이션 반복이면 프레임 증가 아니면 프레임 고정
				++m_iCurFrm;

			if (m_vecFrm.size() <= m_iCurFrm)
			{
				m_iCurFrm = m_vecFrm.size() - 1;
				m_bFinish = true;
				break;
			}
			else if (m_vecFrm[m_iCurFrm].fDuration > m_fAccTime)
				break;
		}
	}

	return 0;
}

void CAnimation2D::UpdateData()
{
	static CConstBuffer* pBuffer = CDevice::GetInst()->FindCBuffer(L"Anim2DInfo");

	g_anim2d.g_bAnim2dUse = true;
	g_anim2d.vLT = m_vecFrm[m_iCurFrm].vLT + m_vecFrm[m_iCurFrm].vOffset;
	g_anim2d.vSize = m_vecFrm[m_iCurFrm].vSize;

	pBuffer->UpdateData(&g_anim2d, sizeof(tAnim2DInfo));
	pBuffer->UpdateRegisterAll();

	m_vecFrm[m_iCurFrm].pTex->SetRegisterAll(16);
}

void CAnimation2D::SetFrmIdx(int _iIdx)
{
	if (m_vecFrm.size() <= _iIdx)
		assert(NULL);

	m_bFinish = false;
	m_iCurFrm = _iIdx;
	m_fAccTime = 0.f;
}


void CAnimation2D::Create(CTexture * _pTex, const POINT & _ptLT, UINT _iWGap, UINT iFrmCount, const POINT & _ptCropSize, const wstring & _strKey, float _fDuration)
{
	tAnimFrm frm = {};
	for (UINT i = 0; i < iFrmCount; ++i)
	{
		frm.pTex = _pTex;
		frm.vLT = Vec2(((float)_ptLT.x) / (_pTex->GetWidth()) + (i * (float)_iWGap / _pTex->GetWidth()), ((float)_ptLT.y) / _pTex->GetHeight());
		frm.vSize = Vec2(((float)_ptCropSize.x) / (_pTex->GetWidth()), ((float)_ptCropSize.y) / _pTex->GetHeight());
		frm.vCropSize = Vec2((float)_ptCropSize.x, (float)_ptCropSize.y);
		frm.fDuration = _fDuration; // _fDuration;
		/*frm.bRepeat = _bRepeat;*/
		m_vecFrm.push_back(frm);
	}

	SetName(_strKey);
}

void CAnimation2D::Create(const wstring & _strFolderPath, const wstring & _strKey, float _fDuration)
{
	wstring strFilePath = CPathMgr::GetResPath() + _strFolderPath + L"\\*.png";
	wstring strRelativePath;
	tAnimFrm frm = {};

	WIN32_FIND_DATA data{};
	HANDLE hFind = FindFirstFile(strFilePath.c_str(),&data);

	map<wstring, CRes*> pTexture = CResMgr::GetInst()->GetResourceMap(RESOURCE_TYPE::TEXTURE);


	while (true)
	{
		frm.fDuration = _fDuration; // _fDuration;
		frm.vLT = Vec2(0.f, 0.f);
		frm.vSize = Vec2(1.f, 1.f);		

		strRelativePath = wstring(_strFolderPath + data.cFileName);

		map<wstring, CRes*>::iterator iter = pTexture.find(strRelativePath);
		if (iter != pTexture.end())
			frm.pTex = CResMgr::GetInst()->Load<CTexture>(strRelativePath);
		else
			frm.pTex = CResMgr::GetInst()->Load<CTexture>(strRelativePath, strRelativePath);

		frm.vCropSize = Vec2(frm.pTex->GetWidth(), frm.pTex->GetHeight());
		/*frm.bRepeat = _bRepeat;*/

		m_vecFrm.push_back(frm);

		if (!FindNextFile(hFind, &data)) // null 만나면 퇴근.
			break;
	}
	//SetName(_strKey);
	FindClose(hFind);
}

void CAnimation2D::Save(FILE * _pFile)
{
	SaveWString(GetName(), _pFile);

	UINT iAnimCount = m_vecFrm.size();
	fwrite(&iAnimCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iAnimCount; ++i)
	{
		fwrite(&m_vecFrm[i].fDuration, sizeof(float), 1, _pFile);
		fwrite(&m_vecFrm[i].vLT, sizeof(Vec2), 1, _pFile);
		fwrite(&m_vecFrm[i].vOffset, sizeof(Vec2), 1, _pFile);
		fwrite(&m_vecFrm[i].vSize, sizeof(Vec2), 1, _pFile);
		fwrite(&m_vecFrm[i].vCropSize, sizeof(Vec2), 1, _pFile);

		SaveWString(m_vecFrm[i].pTex->GetName(), _pFile);
	}
}

void CAnimation2D::Load(FILE * _pFile)
{
	wstring as = LoadWString(_pFile);
	SetName(as);
	UINT iAnimCount = 0;
	fread(&iAnimCount, sizeof(UINT), 1, _pFile);

	tAnimFrm tFrm = {};

	for (UINT i = 0; i < iAnimCount; ++i)
	{
		fread(&tFrm.fDuration, sizeof(float), 1, _pFile);
		fread(&tFrm.vLT, sizeof(Vec2), 1, _pFile);
		fread(&tFrm.vOffset, sizeof(Vec2), 1, _pFile);
		fread(&tFrm.vSize, sizeof(Vec2), 1, _pFile);
		fread(&tFrm.vCropSize, sizeof(Vec2), 1, _pFile);

		wstring strKey = LoadWString(_pFile);
		tFrm.pTex = CResMgr::GetInst()->Load<CTexture>(strKey);
		m_vecFrm.push_back(tFrm);
	}
}