#include "MonsterScript.h"

#include "TimeMgr.h"

#include "Transform.h"


CMonsterScript::CMonsterScript()
	: m_bCollide(0)
{
	CWell512 randomdir, randomspeed;

	m_eMonsterDir = (MONSTER_DIR)randomdir.GetValue(0,2);
	m_fSpeed = randomspeed.GetFloatValue(100, 300);
}


CMonsterScript::~CMonsterScript()
{
}


int CMonsterScript::update()
{
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

void CMonsterScript::OnCollisionEnter(const CCollider * _pOther)
{
	m_bCollide = 1;

	for (UINT i = 0; i < Script().size(); ++i)
	{
		CMaterial* pMtrl = Script()[i]->GetMaterial();
		pMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}
}

void CMonsterScript::OnCollision(const CCollider * _pOther)
{
}

void CMonsterScript::OnCollisionExit(const CCollider * _pOther)
{
	m_bCollide = 0;
	for (UINT i = 0; i < Script().size(); ++i)
	{
		CMaterial* pMtrl = Script()[i]->GetMaterial();
		pMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}
}