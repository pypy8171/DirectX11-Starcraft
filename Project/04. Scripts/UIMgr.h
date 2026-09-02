#pragma once
#include "SingleTonScript.h"

class CGameObject;

class CUIMgr :
	public CSingleTonScript<CUIMgr>
{
private:
	Vec3					m_vCamPos;
	vector<CGameObject*>	m_vecTargetObj;

	BUTTON_CHAPTER			m_eButtonChapter;
	BUTTON_CHAPTER			m_eBeforeButtonChapter;

	bool					m_bProduce;
	bool					m_bClicked;
	bool					m_bProduceOut;
	bool					m_bProduceBtnClick;

	bool					m_bBaseUI;
	bool					m_bLBuildUI;
	bool					m_bHBuildUI;

	bool					m_bMineralRequest;
	bool					m_bGasRequest;
	int						m_iMineral;
	int						m_iGas;

	static int				m_iMineralOn;
	static int				m_iGasOn;

private:
	CGameObject *			m_pTargetObj;

public:
	virtual int update();
	virtual int lateupdate();
	const Vec3& GetCamPos() { return m_vCamPos; }
	vector<CGameObject*> GetTargetObjVec() { return m_vecTargetObj; }

	CGameObject* GetTargetObj() { return m_pTargetObj; }

	bool IsTargetEmpty(){
		if (m_vecTargetObj.empty())
			return true;
		else
			return false;
	}

	const wstring& SubtractName(wstring& SubtractName);

public:
	void SetMineral(int _iMineral) { m_iMineral += _iMineral; }
	int& GetMineral() { return m_iMineral; }

	void SetGas(int _iGas) { m_iGas += _iGas; }
	int& GetGas() { return m_iGas; }

public:
	void SetButtonChapter(BUTTON_CHAPTER _ButtonChapter) {m_eButtonChapter = _ButtonChapter; }
	BUTTON_CHAPTER & GetButtonChapter() { return m_eButtonChapter; }

	void SetBeforeButtonChapter(BUTTON_CHAPTER _ButtonChapter) { m_eBeforeButtonChapter = _ButtonChapter; }
	BUTTON_CHAPTER & GetBeforeButtonChapter() { return m_eBeforeButtonChapter; }

	void SetBaseUI(bool _bBaseUI) { m_bBaseUI = _bBaseUI; }
	bool& GetBaseUI() { return m_bBaseUI; }

	void SetLBuildUI(bool _bLBuildUI) { m_bLBuildUI = _bLBuildUI; }
	bool& GetLBuildUI() { return m_bBaseUI; }

	void SetHBuildUI(bool _bHBaseUI) { m_bHBuildUI = _bHBaseUI; }
	bool& GetHBuildUI() { return m_bHBuildUI; }

public:
	void SetProduce(bool _bProduce) { m_bProduce = _bProduce; }
	bool& GetProduce() { return m_bProduce; }

	void SetProduceOut(bool _bProduce) { m_bProduceOut = _bProduce; }
	bool& GetProduceOut() { return m_bProduceOut; }

	void SetProduceBtnClick(bool _bProduce) { m_bProduceBtnClick = _bProduce; }
	bool& GetProduceBtnClick() { return m_bProduceBtnClick; }

	void SetClick(bool _bProduce) {m_bClicked = _bProduce; }
	bool& GetClick() { return m_bClicked; }
	CLONE(CUIMgr);
public:
	CUIMgr();
	virtual ~CUIMgr();
};

