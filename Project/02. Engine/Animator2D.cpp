#include "Animator2D.h"
#include "Animation2D.h"
#include "Transform.h"

#include "PathMgr.h"
#include "ResMgr.h"

#include "Device.h"
#include "ConstBuffer.h"

#include "Texture.h"

#include "EventMgr.h"

CAnimator2D::CAnimator2D()
	: m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_iFrmCount(0)
	, m_vLeftTop{}
	, m_iGap(0)
	, m_vCropSize{}
	, m_fDuration(0.f)
	, m_bFileLoadOn(false)
{
	SetComponentType(COMPONENT_TYPE::ANIMATOR2D);
}

CAnimator2D::~CAnimator2D()
{
	Safe_Delete_Map(m_mapAnim);
}

CAnimator2D::CAnimator2D(const CAnimator2D& _other)
	: m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_iFrmCount(0)
	, m_vLeftTop{}
	, m_iGap(0)
	, m_vCropSize{}
	, m_fDuration(0.f)
	, m_bFileLoadOn(false)
{
	*this = _other;

	SetComponentType(COMPONENT_TYPE::ANIMATOR2D);

	map<wstring, CAnimation2D*> clonemap;
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.begin(); // const_iterator 있음
	for (; iter != m_mapAnim.end(); ++iter)
	{
		CAnimation2D* pCloneAnim = new CAnimation2D;
		wstring strKey = iter->first;
		*pCloneAnim = *iter->second;
		clonemap.insert(make_pair(strKey, pCloneAnim));
	}
	m_mapAnim = clonemap;
}

int CAnimator2D::update()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->SetRepeat(m_bRepeat); // 애니메이션 고정하기 위함
		Transform()->SetLocalScale(Vec3(m_pCurAnim->GetCurAnimSize().x, m_pCurAnim->GetCurAnimSize().y, 1));
		m_pCurAnim->update();
		if (m_pCurAnim->IsFinish() && m_bRepeat)
			m_pCurAnim->SetFrmIdx(0);
	}

	return 0;
}

void CAnimator2D::UpdateData()
{
	if (nullptr == m_pCurAnim)
	{
		static CConstBuffer* pBuffer = CDevice::GetInst()->FindCBuffer(L"Anim2DInfo");

		g_anim2d.g_bAnim2dUse = false;
		pBuffer->UpdateData(&g_anim2d, sizeof(tAnim2DInfo));
		pBuffer->UpdateRegisterAll();
		return;
	}
	m_pCurAnim->UpdateData();
}

void CAnimator2D::AddAnimation(CTexture * _pTexture, const POINT & _ptLT, UINT _iWGap, UINT iFrmCount, const POINT & _ptCropSize, const wstring & _strKey, float _fDuration, const bool& _bRepeat)
{
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter != m_mapAnim.end())
	{
		MessageBox(NULL, L"동일한 Animation Key 가 있습니다.", L"경고!!", MB_OK);
		assert(nullptr);
	}

	CAnimation2D* pNewAnim = new CAnimation2D;
	pNewAnim->Create(_pTexture, _ptLT, _iWGap, iFrmCount, _ptCropSize, _strKey, _fDuration);
	pNewAnim->SetRepeat(_bRepeat);

	pNewAnim->SetOwner(this);
	m_mapAnim.insert(make_pair(_strKey, pNewAnim));

}

// 폴더로 텍스쳐 
void CAnimator2D::AddAnimation(const wstring & _strFolderPath, const wstring & _strKey, const bool& _bRepeat, float _fDuration)
{
	CAnimation2D* pNewAnim = new CAnimation2D;

	pNewAnim->Create(_strFolderPath, _strKey, _fDuration/*, _bRepeat*/);
	pNewAnim->SetRepeat(_bRepeat);

	pNewAnim->SetOwner(this);
	m_mapAnim.insert(make_pair(_strKey, pNewAnim));
}

void CAnimator2D::DeleteAnim(const wstring & _strKey)
{
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find((wstring)_strKey);

	//CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT, (INT_PTR)iter->second, 0 });
	if (iter != m_mapAnim.end())
	{
		delete iter->second;
	}
	m_mapAnim.erase((wstring)_strKey);

	m_pCurAnim = nullptr;
}

void CAnimator2D::PlayAnim(const wstring & _strKey, bool _bRepeat)
{
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find(_strKey);
	if (iter == m_mapAnim.end())
	{
		MessageBox(NULL, L"Animation 해당 키 없음", L"경고!!", MB_OK);
		assert(nullptr);
	}
	m_pCurAnim = iter->second;
	m_bRepeat = _bRepeat;
}

void CAnimator2D::PlayNumAnimation(const wstring & _strKey, bool _bRepeat, int _iNum)
{
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		assert(NULL);

	m_pCurAnim = iter->second;
	m_bRepeat = _bRepeat;

	m_pCurAnim->SetFrmIdx(_iNum);
}

CTexture * CAnimator2D::SelectFrm(const wstring& _strKey, bool _bRepeat, int _iNum)
{
	CTexture* pTex = NULL;
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		assert(NULL);

	m_bRepeat = _bRepeat;
	m_pCurAnim = iter->second;

	pTex = iter->second->GetFrame()[_iNum].pTex;
	return pTex;
}

//void CAnimator2D::SetCurAnim(const wstring& _strKey)
//{
//	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find(_strKey);
//
//	if (iter == m_mapAnim.end())
//		assert(NULL);
//
//	m_pCurAnim = iter->second;
//	m_bRepeat = m_pCurAnim->GetRepeat();
//
//}
//
//bool & CAnimator2D::GetRepeat()
//{
//	bool a = m_pCurAnim->GetRepeat();
//	return m_pCurAnim->GetRepeat();
//}

void CAnimator2D::ClearData()
{
	static CConstBuffer* pBuffer = CDevice::GetInst()->FindCBuffer(L"Anim2DInfo");
	pBuffer->ClearData();
}

int CAnimator2D::GetFileNum(const wstring& _strFolderPath)
{
	wstring strFilePath = CPathMgr::GetResPath() + _strFolderPath + L"*.png";

	WIN32_FIND_DATA data{};
	HANDLE hFind = FindFirstFile(strFilePath.c_str(), &data);

	int iFileNum = 0;

	while (true)
	{
		++iFileNum;
		if (!FindNextFile(hFind, &data)) // null 만나면 퇴근.
			break;
	}

	FindClose(hFind);
	return iFileNum;
}

void CAnimator2D::Save(FILE * _pFile)
{
	UINT iAnimCount = m_mapAnim.size();
	fwrite(&iAnimCount, sizeof(UINT), 1, _pFile);

	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		SaveWString(iter->first, _pFile);
		iter->second->Save(_pFile);

	}

	bool bCurAnim = false;
	if (nullptr != m_pCurAnim)
		bCurAnim = true;

	fwrite(&bCurAnim, sizeof(bool), 1, _pFile);
	fwrite(&m_bRepeat, sizeof(bool), 1, _pFile);

	SaveWString(m_szCurAnimName, _pFile);

	if (bCurAnim)
	{
		SaveWString(m_szCurAnimName, _pFile);
	}

}

void CAnimator2D::Load(FILE * _pFile)
{
	UINT iAnimCount = 0;
	fread(&iAnimCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iAnimCount; ++i)
	{
		CAnimation2D* pAnim = new CAnimation2D();
		wstring a = LoadWString(_pFile);
		pAnim->Load(_pFile);

		pAnim->SetOwner(this);
		m_mapAnim.insert(make_pair(a, pAnim)); // m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim)); 바꾼거
		SetFileLoadOn(true);
	}


	bool bCurAnim = false;
	fread(&bCurAnim, 1, 1, _pFile);
	fread(&m_bRepeat, 1, 1, _pFile);

	m_szCurAnimName = LoadWString(_pFile);


	if (bCurAnim)
	{
		wchar_t* pstrCurAnimName = LoadWString(_pFile);
		PlayAnim(pstrCurAnimName, m_bRepeat);
	}

}
