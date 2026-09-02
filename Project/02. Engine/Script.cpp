#include "Script.h"

#include "Transform.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"

#include "EventMgr.h"


CScript::CScript()
{
	SetComponentType(COMPONENT_TYPE::SCRIPT);
}


CScript::~CScript()
{

}

void CScript::Instantiate(CPrefab* _pPrefab, const wstring & _strLayerName, const Vec3 vLocalPos, const Vec3 vLocalAngle)
{
	CGameObject* pCopy = _pPrefab->Instantiate();
	pCopy->Transform()->SetLocalPos(vLocalPos);
	pCopy->Transform()->SetLocalRotate(vLocalAngle);

	int iIdx = CSceneMgr::GetInst()->GetLayer(_strLayerName)->GetIdx();

	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::CREATE_OBJECT, (INT_PTR)pCopy, iIdx });
}

void CScript::DestroyObj(CGameObject * _pObject)
{
	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT, (INT_PTR)_pObject, 0 });
}
void CScript::DestroyObj()
{
	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT, (INT_PTR)Object(), 0 });
}
void CScript::DisconnectParent(CGameObject * _pObject)
{
	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT, (INT_PTR)_pObject, 0 });
}
void CScript::DisconnectParent()
{
	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DISCONNECT_PARENT, (INT_PTR)Object(), 0 });
}

void CScript::AddChild(CGameObject * _pChild)
{
	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::ADD_CHILD, (INT_PTR)Object(), (INT_PTR)_pChild });
}
void CScript::AddChild(CGameObject * _pParent, CGameObject * _pChild)
{
	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::ADD_CHILD, (INT_PTR)_pParent, (INT_PTR)_pChild });
}