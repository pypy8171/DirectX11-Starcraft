#pragma once
#include "Entity.h"
#include "Ptr.h"
#include "Texture.h"

class CAnimator2D;

struct tAnimFrm
{
	CTexture*		pTex;		// 참조 이미지
	Vec2			vLT;		// 참조하는 이미지 내에서, 사용할 부위의 좌 상단 위치(UV 좌표 기준)
	Vec2			vOffset;	// ptLT 좌표에 더해질 상대위치					  (UV 좌표 기준)
	Vec2			vSize;		// 사용할 부위의 크기								  (UV 좌표 기준)
	Vec2			vCropSize;  /////// 나중에 추가한거
	float			fDuration;	// 지속 시간
	//bool			bRepeat;
};

class CAnimation2D :
	public CEntity
{
private:
	CAnimator2D *		m_pOwner;
	vector<tAnimFrm>	m_vecFrm;

	int					m_iCurFrm;
	int					m_iCurFrmIdx;
	float				m_fAccTime;
	bool				m_bFinish;
	bool				m_bRepeat;

public:
	virtual int update();

public:
	virtual void UpdateData();

public:
	void SetOwner(CAnimator2D* _pAnimator) { m_pOwner = _pAnimator; }
	void SetFrmIdx(int _iIdx);
	void Create(CTexture * _pTex, const POINT & _ptLT, UINT _iWGap, UINT iFrmCount, const POINT & _ptCropSize, const wstring& _strKey, float _fDuration);
	void Create(const wstring& _strFolderPath, const wstring& _strKey, float _fDuration );

public:
	void SetRepeat(const bool& _Repeat) { m_bRepeat = _Repeat; }

public:
	bool IsFinish() { return m_bFinish; }
	int& GetCurFrm() { return m_iCurFrm; }
	int& GetCurFrmIdx(){return 	m_iCurFrmIdx;}

public:
	void SetFrm(int _iFrmIdx)
	{
		m_bFinish = false;
		m_iCurFrmIdx = _iFrmIdx;
		m_fAccTime = 0.f;
	}

	void SetFinishFrm(int _iFrmIdx)
	{
		m_bFinish = true;
		m_iCurFrmIdx = _iFrmIdx;
		m_fAccTime = 0.f;
	}

	bool& GetRepeat() { return m_bRepeat; }
	vector<tAnimFrm> GetFrame() { return m_vecFrm; }

public:
	Vec2 & GetCurAnimSize() { return m_vecFrm[m_iCurFrm].vCropSize; }

public:
	CLONE(CAnimation2D);
	void Save(FILE* _pFile);
	void Load(FILE* _pFile);

public:
	CAnimation2D();
	virtual ~CAnimation2D();
};

