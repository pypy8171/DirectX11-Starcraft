#include "MouseScript.h"
#include "Script.h"

#include "Transform.h"
#include "MeshRender.h"

#include "Scene.h"

#include "SceneMgr.h"
#include "KeyMgr.h"

#include "Animator2D.h"

CMouseScript::CMouseScript()
	: m_pMark(nullptr)
{
}


CMouseScript::~CMouseScript()
{
}

#include <iostream>
using namespace std;

int CMouseScript::update()
{
	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetLocalPos();
	if (KEYHOLD(KEY_TYPE::KEY_LBTN)) // 오브젝트 위에 있을때
	{
		Object()->Animator2D()->PlayAnim(L"CursorOn", true);
	}
	else
	{
		Object()->Animator2D()->PlayAnim(L"CursorArrow", true); // 텍스쳐는 1인거 쓰고 180도 회전
	}

	if (KEYHOLD(KEY_TYPE::KEY_RBTN))
	{
		Object()->Animator2D()->PlayAnim(L"RightCursorActive", true);
	}

	Transform()->SetLocalPos(CKeyMgr::GetInst()->GetMousePos());

	return 0;
}

void CMouseScript::awake()
{
}
