#pragma once
#include "Component.h"

class CAnimation2D;
class CTexture;

class CAnimator2D :
	public CComponent
{
private:
	map<wstring, CAnimation2D*> m_mapAnim;
	CAnimation2D*				m_pCurAnim;
	bool						m_bRepeat;

	wstring						m_szCurAnimName;

	int							m_iFrmCount;
	POINT						m_vLeftTop;
	int							m_iGap;
	POINT						m_vCropSize;
	float						m_fDuration;

	bool						m_bFileLoadOn;

public:
	virtual int update();
	virtual void UpdateData();

public:
	void PlayAnim(const wstring& _strKey, bool _bRepeat);
	void AddAnimation(CTexture* _pTexture, const POINT& _ptLT, UINT _iWGap, UINT iFrmCount,
		const POINT& _ptCropSize, const wstring & _strKey,  float _fDuration, const bool& _bRepeat);

	// 낱장으로 로딩하는 경우, 폴더경로 지정
	void AddAnimation(const wstring& _strFolderPath, const wstring& _strKey, const bool& _bRepeat, float _fDuration = 0.1f);

	void DeleteAnim(const wstring & _strKey);

	void PlayNumAnimation(const wstring & _strKey, bool _bRepeat, int _iNum);
	CTexture* SelectFrm(const wstring& _strKey, bool _bRepeat, int _iNum);


public:
	int GetFileNum(const wstring& _strFolderPath);
	int GetMaxCount() { return (m_iFrmCount / 17) -1 ; }

public:
	//void SetCurAnim(const wstring& _strKey);

	void SetCurAnimName(wstring _name) { m_szCurAnimName = _name; }
	wstring& GetCurAnimName() { return m_szCurAnimName; }

	void SetRepeat(bool _bRepeat) { m_bRepeat = _bRepeat; }
	bool& GetRepeat() {	return m_bRepeat;}

	void SetFrmCount(int _iFrmCount) { m_iFrmCount = _iFrmCount; }
	int& GetFrmCount() { return m_iFrmCount; }

	void SetGap(int _iGap) { m_iGap = _iGap; }
	int& GetGap() { return m_iGap; }

	void SetLeftTop(POINT _LeftTop) { m_vLeftTop = _LeftTop; }
	POINT& GetLeftTop() { return m_vLeftTop; }

	void SetCropSize(POINT _CropSize) { m_vCropSize = _CropSize; }
	POINT& GetCropSize() { return m_vCropSize; }

	void SetDuration(float _fDuration) { m_fDuration = _fDuration; }
	float& GetDuration() { return m_fDuration; }

	CAnimation2D* GetAnimation() { 	return m_pCurAnim; 	}
	map<wstring, CAnimation2D*>& GetAnimationMap() { return m_mapAnim; }

public:
	void SetFileLoadOn(bool _b) { m_bFileLoadOn = _b; }
	bool GetFileLoadOn() { return m_bFileLoadOn; }

public:
	static void ClearData();

public:
	CLONE(CAnimator2D);
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CAnimator2D();
	CAnimator2D(const CAnimator2D& _other);
	virtual ~CAnimator2D();
};

