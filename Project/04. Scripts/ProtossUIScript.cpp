#include "stdafx.h"
#include "ProtossUIScript.h"

#include "YongEngine/Transform.h"
#include "YongEngine/Camera.h"

#include "YongEngine/Animator2D.h"
#include "YongEngine/Animation2D.h"

#include "YongEngine/SceneMgr.h"
#include "YongEngine/Scene.h"
#include "YongEngine/Layer.h"

#include "YongEngine/Core.h"

#include "YongEngine/ResMgr.h"

#include "UIMgr.h"

#include "ScriptMgr.h"

CProtossUIScript::CProtossUIScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::PROTOSSUISCRIPT);
}


CProtossUIScript::~CProtossUIScript()
{
}

int CProtossUIScript::update()
{
	CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"Protoss");
	if(pSound == nullptr)
	{
		pSound = CResMgr::GetInst()->Load<CSound>(L"Protoss", L"Sound\\Protoss.wav");
	}
	pSound->Play(2);

	Vec3 vScale = Object()->Transform()->GetLocalScale();
	tResolution v = CCore::GetInst()->GetResoultion();

	Object()->Transform()->SetLocalScale(Vec3(vScale.x * v.x / 640, vScale.y*v.y / 480, vScale.z));
	Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
	Object()->Transform()->SetLocalPos(Vec3(vCamPos.x, vCamPos.y, 10.f));

	if (nullptr == Object()->Animator2D())
		return false;

	if (false == Object()->Animator2D()->GetFileLoadOn())
		return false;



	Object()->Animator2D()->PlayAnim(L"MainFrame_1.png", true);



	return 0;
}

int CProtossUIScript::lateupdate()
{
	return 0;
}
