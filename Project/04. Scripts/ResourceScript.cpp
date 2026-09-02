#include "stdafx.h"
#include "ResourceScript.h"

#include "YongEngine/Grid.h"
#include "YongEngine/Transform.h"

#include "YongEngine/Layer.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/KeyMgr.h"

#include "MouseScript.h"
#include "ScriptMgr.h"
CResourceScript::CResourceScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::RESOURCESCRIPT);
}


CResourceScript::~CResourceScript()
{
}


void CResourceScript::awake()
{
}

int CResourceScript::update()
{
	// collideon 으로 가는게 맞다.
	CLayer* pMouseLayer = CSceneMgr::GetInst()->GetLayer(L"Mouse");
	CGameObject* pMouseObject = pMouseLayer->GetObjVec()[0];

	assert(pMouseObject);

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMouseScript* pMouseScript = (CMouseScript*)pMouseObject->Script()[0]; // 마우스 스크립트 추가시 변경
	CGameObject* pTargetObj = pMouseScript->GetTargetObj();


	if (nullptr == pTargetObj || pTargetObj->GetObjType() == OBJ_TYPE::UI || pTargetObj->GetObjType() == OBJ_TYPE::BUILDING
		|| pTargetObj->GetObjType() == OBJ_TYPE::AIRUNIT || pTargetObj->GetObjType() == OBJ_TYPE::GROUNDUNIT
		|| pTargetObj->GetObjType() == OBJ_TYPE::RESOURCE)
		return 0;

	if (KEYHOLD(KEY_TYPE::KEY_LBTN))
	{
		Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		pTargetObj->Transform()->SetLocalPos(vMousePos);
	}
	if (KEYAWAY(KEY_TYPE::KEY_LBTN))
	{
		CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
		CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

		int iTileSize = pGridObject->Grid()->GetTileSize();
		Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos() + pGridObject->Grid()->GetTransformed();;
		Vec2 vIdx = Vec2((int)((vMousePos.x + iTileSize / 2) / iTileSize), (int)((vMousePos.y + iTileSize / 2) / iTileSize));

		CGameObject* pClickedTile = pGridObject->Grid()->GetClickedTile(Vec2(vIdx.x, vIdx.y));

		Vec3 vClickedTilePos = pClickedTile->Transform()->GetLocalPos();

		pTargetObj->Transform()->SetLocalPos(Vec3(vClickedTilePos.x - iTileSize / 2,
			vClickedTilePos.y - iTileSize / 2, 100.f));
	}
	
	return 0;
}

void CResourceScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CResourceScript::OnCollision(CCollider * _pOther)
{
	
}

void CResourceScript::OnCollisionExit(CCollider * _pOther)
{
}
