#include "Prefab.h"

#include "GameObject.h"	

#include "ResMgr.h"

//CPrefab * CPrefab::Clone()
//{
//	CPrefab* pClonePrefab = new CPrefab(*this);
//	CResMgr::GetInst()->AddClone(pClonePrefab);
//	return pClonePrefab;
//}

// 肯己等 府家胶 
CPrefab::CPrefab()
	: m_pProto(nullptr)
{
}

CPrefab::CPrefab(CGameObject* _pObj)
	: m_pProto(_pObj)
{
}


CPrefab::~CPrefab()
{
	SAFE_DELETE(m_pProto);
}

CGameObject * CPrefab::Instantiate()
{
	//m_pProto->GetChild()[0]->Clone();
	return m_pProto->Clone();
}
