#include "EventMgr.h"

#include "SceneMgr.h"

#include "Grid.h"

#include "GameObject.h"

CEventMgr::CEventMgr()
{
}


CEventMgr::~CEventMgr()
{
}

int CEventMgr::update()
{
	for (UINT i = 0; i < m_vecDeleteObj.size();++i)
	{	
		m_vecDeleteObj[i]->Isolate();
		SAFE_DELETE(m_vecDeleteObj[i]);
	}
	m_vecDeleteObj.clear();

	for (UINT i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEventCopy = m_vecEvent;
	m_vecEvent.clear();

	return 0;
}

void CEventMgr::Execute(const tEvent & _eEvent)
{
	switch (_eEvent.eType)
	{
	case EVENT_TYPE::ADD_CHILD:
		((CGameObject*)_eEvent.wParam)->AddChild(((CGameObject*)_eEvent.lParam));
		break;
	case EVENT_TYPE::DISCONNECT_PARENT:
		((CGameObject*)_eEvent.wParam)->DisconnectParent();
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		((CGameObject*)_eEvent.wParam)->Kill();
		bool bFind = false;
		for (UINT i = 0; i < m_vecDeleteObj.size(); ++i)
		{
			if ((INT_PTR)m_vecDeleteObj[i] == _eEvent.wParam)
			{
				bFind = true;
				break;
			}
		}
		if(!bFind)
			m_vecDeleteObj.push_back((CGameObject*)_eEvent.wParam);
	}
		break;
	case EVENT_TYPE::CREATE_OBJECT:
		CSceneMgr::GetInst()->AddGameObject(_eEvent.lParam, ((CGameObject*)_eEvent.wParam));
		break;
	case EVENT_TYPE::CHANGE_RESOLUTION:
		break;
	case EVENT_TYPE::RENEWAL:
		((CGrid*)_eEvent.wParam)->ChangeGrid();
		break;
	case EVENT_TYPE::END:
		break;
	default:
		break;
	}
}

void CEventMgr::DeleteObj()
{
}















//
//int CEventMgr::update()
//{
//	// 삭제예정 오브젝트 처리	
//	for (UINT i = 0; i < m_vecDelObj.size(); ++i)
//	{
//		m_vecDelObj[i]->Isolate();
//		SAFE_DELETE(m_vecDelObj[i]);
//	}
//	m_vecDelObj.clear();
//
//	// 등록된 이벤트 처리
//	for (UINT i = 0; i < m_vecEvent.size(); ++i)
//	{
//		Execute(m_vecEvent[i]);
//	}
//	m_vecEvent.clear();
//
//	return 0;
//}
//
//void CEventMgr::Execute(const tEvent & _event)
//{
//	switch (_event.eType)
//	{
//	case EVENT_TYPE::ADD_CHILD:
//		break;
//	case EVENT_TYPE::DISCONNECT_PARENT:
//		break;
//	case EVENT_TYPE::DELETE_OBJECT:
//	{
//		((CGameObject*)_event.wParam)->Kill();
//		bool bFind = false;
//		for (UINT i = 0; i < m_vecDelObj.size(); ++i)
//		{
//			if ((INT_PTR)m_vecDelObj[i] == _event.wParam)
//			{
//				bFind = true;
//				break;
//			}
//		}
//		if (!bFind)
//			m_vecDelObj.push_back(((CGameObject*)_event.wParam));
//	}
//	break;
//	case EVENT_TYPE::CREATE_OBJECT:
//		break;
//	case EVENT_TYPE::CHANGE_RESOLUTION:
//		break;
//	case EVENT_TYPE::END:
//		break;
//	default:
//		break;
//	}
//}
//
//void CEventMgr::DeleteObject()
//{
//}
