#pragma once
//1

class CGameObject;

class CComponentDlg
	: public CDialogEx
{
private:
	int				m_iScrollVal;

protected:
	bool			m_bClicked;
	bool			m_bEditFocus;
	CGameObject*	m_pTargetObj;

public:
	virtual void init() {}
	virtual void update(CGameObject* _pTargetObj) = 0;


protected:
	void FocusGameView();

public:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();


	afx_msg void OnEditSetfocus(UINT _id) { m_bEditFocus = true; }
	afx_msg void OnEditKillFocused(UINT _id) { m_bEditFocus = false; }
public:
	CComponentDlg(UINT _id, CWnd* pParent);
	virtual ~CComponentDlg();

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

