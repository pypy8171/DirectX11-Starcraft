#include "stdafx.h"
#include "MonsterScript.h"

#include "YongEngine/MeshRender.h"

#include "YongEngine/TimeMgr.h"

#include "YongEngine/Transform.h"

#include "Animator2D.h"
#include "Animation2D.h"

#include "ScriptMgr.h"

CMonsterScript::CMonsterScript()
	: m_bCollide(0)
{
	CWell512 randomdir, randomspeed;

	m_eMonsterDir = (MONSTER_DIR)randomdir.GetValue(0,2);
	m_fSpeed = randomspeed.GetFloatValue(100, 300);

	SetScriptType((UINT)SCRIPT_TYPE::MONSTERSCRIPT);
}


CMonsterScript::~CMonsterScript()
{
}


int CMonsterScript::update()
{
	if (nullptr == Object()->Animator2D())
		return false;

	if (false == Object()->Animator2D()->GetFileLoadOn())
		return false;

	Vec3 vScale = Object()->Transform()->GetLocalScale();
	wstring CurAnim = Object()->Animator2D()->GetCurAnimName();

	Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), true);

	Transform()->SetLocalScale(Vec3(vScale.x, vScale.y, vScale.z));


	Move();

	return 0;
}

void CMonsterScript::Move()
{
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vAngle = Transform()->GetLocalAngle();

	//vAngle.x += XM_PI * DT;
	//vAngle.y += XM_PI * DT;
	//vAngle.z += XM_PI * DT;

	if (GetMonsterDir() == MONSTER_DIR::RIGHT)
	{
		vPos.x += m_fSpeed *DT;
		if (vPos.x > WINCX / 4.f)
		{
			SetMonsterDir(MONSTER_DIR::LEFT);
		}
	}	
	else if (GetMonsterDir() == MONSTER_DIR::LEFT)
	{
		vPos.x -= m_fSpeed *DT;
		if (vPos.x < -WINCX/4.f)
		{
			SetMonsterDir(MONSTER_DIR::RIGHT);
		}
	}

	//Transform()->SetLocalPos(vPos);
	//Transform()->SetLocalRotate(vAngle);
}

void CMonsterScript::OnCollisionEnter(CCollider * _pOther)
{
	m_bCollide = 1;
	for (UINT i = 0; i < Script().size(); ++i)
	{
		// 이미 클론 따놧는데 왜 그냥은 안바뀌지
		CMaterial* pCloneMtrl = Object()->MeshRender()->GetMaterial();
		CMaterial* pMtrl = Script()[i]->GetMaterial();
		if (pCloneMtrl != nullptr)
			pCloneMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}
}

void CMonsterScript::OnCollision(CCollider * _pOther)
{
}

void CMonsterScript::OnCollisionExit(CCollider * _pOther)
{
	m_bCollide = 0;
	for (UINT i = 0; i < Script().size(); ++i)
	{
		CMaterial* pCloneMtrl = Object()->MeshRender()->GetMaterial();
		CMaterial* pMtrl = Script()[i]->GetMaterial();
		if (pCloneMtrl != nullptr)
			pCloneMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}
}