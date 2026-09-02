#include "stdafx.h"
#include "MarkScript.h"
#include "BulletScript.h"
#include "PlayerScript.h"
#include "YongEngine/Script.h"

#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"

#include "YongEngine/Animation2D.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Script.h"

#include "YongEngine/KeyMgr.h"
#include "YongEngine/ResMgr.h"
#include "YongEngine/ShaderMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Scene.h"
#include "YongEngine/Animator2D.h"

#include "UnitScript.h"

#include "ScriptMgr.h"

CMarkScript::CMarkScript()
	: m_bMarkOn(false)
	, m_bCollide(false)
	//, m_pPlayer(NULL)
{
	SetScriptType((UINT)SCRIPT_TYPE::MARKSCRIPT);
}


CMarkScript::~CMarkScript()
{
}

int CMarkScript::update()
{
	Key();
	return 0;
}

void CMarkScript::Key()
{
	if (nullptr == Object()->Animator2D())
		return;

	if (false == Object()->Animator2D()->GetFileLoadOn())
		return;

	CScene* pCurScene = (CScene*)CSceneMgr::GetInst()->GetCurrentScene();
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	
	//if (KEYTAB(KEY_TYPE::KEY_LBTN))
	//{
	//	SetMarkOn(true);
	//	Transform()->SetLocalPos(Vec3(vMousePos.x, vMousePos.y, g_depthz));
	//}
	//else if (KEYTAB(KEY_TYPE::KEY_RBTN))
	//{
	//	SetMarkOn(false);
	//	Transform()->SetLocalPos(Vec3(0.f,	0.f, g_depthz)); // 시야 밖으로
	//}

	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		//Object()->MeshRender()->SetRender(true);
		Object()->Animator2D()->PlayAnim(L"ClickCursor", true);
		Transform()->SetLocalPos(Vec3(vMousePos.x, vMousePos.y, g_depthz));
		//CAnimation2D* pCurAnim = Object()->Animator2D()->GetAnimation();
		//if (pCurAnim->GetCurFrm() == pCurAnim->GetFrame().size() - 1)
			//Object()->MeshRender()->SetRender(false);
	}

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		vector<CGameObject*> vecObj = CSceneMgr::GetInst()->GetCurrentScene()->GetCurTargetObjVec();

		if (vecObj.size() == 0)
			return;

		CUnitScript* pUnitScript = nullptr;
		for (size_t i = 0; i < vecObj[0]->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == vecObj[0]->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)vecObj[0]->Script()[i];
			}
		}
		if (pUnitScript == nullptr)
			return;

		if (pUnitScript->GetReadyToAtt()) {
			Object()->Animator2D()->PlayAnim(L"ClickCursor", true);
			Transform()->SetLocalPos(Vec3(vMousePos.x, vMousePos.y, g_depthz));
		}

	}

	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		SetMarkOn(true);
	}
}