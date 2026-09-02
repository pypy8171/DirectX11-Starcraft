#pragma once
#include "YongEngine/Script.h"

class CPrefab;

class CButtonScript
	: public CScript
{
private:
	Vec3			m_vButtonIdxPos;
	Vec3			m_vBeforePos;
	Vec3			m_vButtonOrgPos;

	int				m_iButtionIdx;

	BUTTON_CHAPTER	m_eButtonChapter;

	CPrefab*		m_pClickedObj;
	wstring			m_strClickedObjLayer;

	SKILL			m_eSkill;
	wstring			m_strCurSkill;

	bool			m_bCollide;
	bool			m_bPressed;
	bool			m_bScaleUp;
	CGameObject*	m_pCurTargetObj;
	Vec3			m_vScaleUp;


public:
	virtual int update();
	virtual int lateupdate();


public:
	void SetButtonIdx(int _iBtnIdx) { m_iButtionIdx = _iBtnIdx;}
	int& GetButtonIdx() { return m_iButtionIdx; }	

	void SetButtonChapter(BUTTON_CHAPTER _eButtonChapter) { m_eButtonChapter = _eButtonChapter; }
	BUTTON_CHAPTER& GetButtonChapter() { return m_eButtonChapter; }

	void SetButtonPressed(bool _bPressed) { m_bPressed = _bPressed; }
	bool& GetBtnPressed() { return m_bPressed; }
	//void CheckIdx();

public:
	void ProbeBaseUI(bool _bool);
	void ProbeLBuildUI(bool _bool);
	void ProbeHBuildUI(bool _bool);
	void PressButton(bool _bool);
	void AttUnitButtonUI(bool _bool);
	void NAttUnitButtonUI(bool _bool);
	void NexusButtonUI(bool _bool);
	void GatewayButtonUI(bool _bool);
	void StargateButtonUI(bool _bool);
	void RoboticsButtonUI(bool _bool);
	void EmptyButtonUI(bool _bool);

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	CLONE(CButtonScript);

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CButtonScript();
	~CButtonScript();
};

