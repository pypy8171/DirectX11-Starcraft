#include "BulletScript.h"

#include "Script.h"

#include "SceneMgr.h"
#include "TimeMgr.h"
#include "KeyMgr.h"

#include "Scene.h"

#include "Transform.h"


CBulletScript::CBulletScript()
	: m_vDest(Vec3(0.f, 0.f, 0.f))
	, m_vSrc(Vec3(0.f, 0.f, 0.f))
	, m_vDirVec(Vec3(0.f, 0.f, 0.f))
	, m_vPlayerAngle(Vec3(0.f, 0.f, 0.f))
	, m_eBulletType(BULLET_TYPE::NORMAL)
	, m_pGameObject(NULL)
	, m_bGuidedOn(false)
	, m_bDelete(false)
	, m_bCollide(0)
{
}

CBulletScript::~CBulletScript()
{
	
}

int CBulletScript::update()
{
	Move();
	//DeleteBulletOp();

	return 0;
}

int CBulletScript::lateupdate()
{
	return 0;
}

void CBulletScript::Move()
{
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vAngle = Transform()->GetLocalAngle();
	Vec3 vPlayerAngle = GetPlayerAngle();

	//if (GetBulletType() == BULLET_TYPE::GUIDED)
	//{
	//	Vec3 vDirvec = GetDestPos() - GetSrcPos();
	//	vDirvec.Normalize();

	//	vPos.x += 500 * DT*vDirvec.x;
	//	vPos.y += 500 * DT*vDirvec.y;
	//}
	//else if (GetBulletType() == BULLET_TYPE::NORMAL)
	//{
	//	vPos.x += 500 * DT*cos(vPlayerAngle.z);
	//	vPos.y += 500 * DT*sin(vPlayerAngle.z);
	//}

	vPos.x += 500 * DT*cos(vAngle.z);
	vPos.y += 500 * DT*sin(vAngle.z);


	//if (vPos.x > 300)
	//{
	//	m_bDelete = true;
	//}
	//if (m_bDelete == true)
	//{
	//	CScene* pCurScene = (CScene*)CSceneMgr::GetInst()->GetCurrentScene();
	//	//GetBullet()->DeleteScript();
	//	//GetBullet()->DeleteComponent();
	//	pCurScene->DeleteGameObject(L"Default", GetBullet());
	//	//m_bDelete = false;
	//	//vPos.x = 290;
	//}

	Transform()->SetLocalPos(vPos);
}


void CBulletScript::DeleteBulletOp()
{
	Vec3 vPos = Transform()->GetLocalPos();

	if (vPos.x < 0.1f || vPos.x > WINCX- 0.1f || vPos.y > WINCY- 0.1f || vPos.y < 0.1f)
	{
		DestroyObj(Object());
	}

	Transform()->SetLocalPos(vPos);
}

void CBulletScript::OnCollisionEnter(const CCollider * _pOther)
{
	DestroyObj(Object());
	//m_bCollide = 1;
	//for (UINT i = 0; i < Script().size(); ++i)
	//{
	//	CMaterial* pMtrl = Script()[i]->GetMaterial();
	//	pMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	//}
}

void CBulletScript::OnCollision(const CCollider * _pOther)
{
}

void CBulletScript::OnCollisionExit(const CCollider * _pOther)
{
	//m_bCollide = 0;
	//for (UINT i = 0; i < Script().size(); ++i)
	//{
	//	CMaterial* pMtrl = Script()[i]->GetMaterial();
	//	pMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	//}

}