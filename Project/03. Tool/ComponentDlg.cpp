#include "stdafx.h"
#include "ComponentDlg.h"

#include "MainFrm.h"

#include "resource.h"

CComponentDlg::CComponentDlg(UINT _id, CWnd * pParent)
	: CDialogEx(_id, pParent)
	, m_pTargetObj(nullptr)
	, m_bClicked(false)
	, m_bEditFocus(false)
{
}

CComponentDlg::~CComponentDlg()
{
}


void CComponentDlg::FocusGameView()
{
	::SetFocus(((CMainFrame*)AfxGetMainWnd())->GetGameViewHwnd());
}

void CComponentDlg::OnOK(){}
void CComponentDlg::OnCancel(){}


void CComponentDlg::PostNcDestroy()
{
	delete this;
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.1
	CDialogEx::PostNcDestroy();
}


BOOL CComponentDlg::OnInitDialog()
{
	//m_iScrollVal = 0;

	//CScrollBar *pScroll;
	//pScroll = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR1);
	//pScroll->SetScrollRange(0, 100);
	//pScroll->SetScrollPos(0);

	CDialogEx::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
BEGIN_MESSAGE_MAP(CComponentDlg, CDialogEx)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


void CComponentDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);

	switch (nSBCode)
	{
	case SB_LINEUP:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 1);
		break;
	case SB_LINEDOWN:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 1);
		break;
	case SB_PAGEUP:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 30);
		break;
	case SB_PAGEDOWN:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 30);
		break;
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos(nPos);
		break;
	}

	m_iScrollVal = pScrollBar->GetScrollPos();
}
