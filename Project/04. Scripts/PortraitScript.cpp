#include "stdafx.h"
#include "PortraitScript.h"

#include "YongEngine/GameObject.h"
#include "Transform.h"

#include "Animator2D.h"
#include "Animation2D.h"

#include "YongEngine/Core.h"

#include "UIMgr.h"
#include "ScriptMgr.h"

CPortraitScript::CPortraitScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::PORTRAITSCRIPT);
}


CPortraitScript::~CPortraitScript()
{
}

int CPortraitScript::update()
{
	if (nullptr == Object()->Animator2D())
		return false;

	if (false == Object()->Animator2D()->GetFileLoadOn())
		return false;

	Vec3 vScale = Object()->Transform()->GetLocalScale();

	tResolution tResolution = CCore::GetInst()->GetResoultion();

	Transform()->SetLocalScale(Vec3(vScale.x * tResolution.x/640, vScale.y *tResolution.y/480, vScale.z));
	Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
	Object()->Transform()->SetLocalPos(Vec3(125 * tResolution.x / 640 + vCamPos.x, -198* tResolution.y / 480 + vCamPos.y, 1.f));

	if (CUIMgr::GetInst()->IsTargetEmpty())
		return 0;

	size_t iIdx = CUIMgr::GetInst()->GetTargetObjVec().size() - 1;

	if (iIdx < 0)
		return 0 ;

	CGameObject* pTargetObj = CUIMgr::GetInst()->GetTargetObjVec()[iIdx]; // 단일타겟을 경우 BWF, 다중 SWF-> 아직 등록 안함
	if (pTargetObj == nullptr || pTargetObj->GetObjType()==OBJ_TYPE::RESOURCE
		|| pTargetObj->GetObjType() == OBJ_TYPE::UI || pTargetObj->GetName() == L"")
		return 0;
	wstring PortraitAnimName{};

	if (L"PylonRadius" != pTargetObj->GetName())
	{
		wstring CurAnimName = pTargetObj->Animator2D()->GetCurAnimName();
		PortraitAnimName = CurAnimName;
		PortraitAnimName = CUIMgr::GetInst()->SubtractName(PortraitAnimName);

		if (PortraitAnimName == L"DarkTemplar")
			PortraitAnimName = L"Dark Templar";
		else if (PortraitAnimName == L"HighTemplar")
			PortraitAnimName = L"High Templar";
		else if (PortraitAnimName == L"DarkArchon")
			PortraitAnimName = L"Dark Archon";

		if (L"Warp" == PortraitAnimName)
			return 0;
		if(OBJ_TYPE::BUILDING == pTargetObj->GetObjType())
			PortraitAnimName = L"Aldaris";
	}
	else
		PortraitAnimName = L"Aldaris";

	Object()->Animator2D()->PlayAnim(PortraitAnimName, true);
	//	
	//Transform()->SetLocalScale(Vec3(vScale.x * 1.5f, vScale.y *1.5f, vScale.z));
	//Object()->Transform()->SetLocalPos(Vec3(195.f + vCamPos.x, -315.f + vCamPos.y, 1.f));
	
	return 0;
}

int CPortraitScript::lateupdate()
{
	return 0;
}
