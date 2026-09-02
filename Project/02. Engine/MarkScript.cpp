#include "MarkScript.h"
#include "BulletScript.h"
#include "PlayerScript.h"
#include "Script.h"

#include "Transform.h"
#include "MeshRender.h"

#include "GameObject.h"
#include "Script.h"

#include "KeyMgr.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Animator2D.h"

CMarkScript::CMarkScript()
	: m_bMarkOn(false)
	, m_bCollide(false)
	//, m_pPlayer(NULL)
{
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
		SetMarkOn(true);
		Transform()->SetLocalPos(Vec3(vMousePos.x, vMousePos.y, g_depthz));
	}
}