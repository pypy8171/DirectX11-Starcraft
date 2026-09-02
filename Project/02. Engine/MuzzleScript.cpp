#include "MuzzleScript.h"
#include "PlayerScript.h"

#include "Transform.h"

#include "KeyMgr.h"


CMuzzleScript::CMuzzleScript()
	: m_pPlayer(NULL)
{
}


CMuzzleScript::~CMuzzleScript()
{
}


int CMuzzleScript::update()
{
	Move();
	return 0;
}

void CMuzzleScript::Move()
{
	Vec3 vPlayerPos = ((CPlayerScript*)m_pPlayer)->GetPlayerPos();
	Vec3 vPlayerAngle = ((CPlayerScript*)m_pPlayer)->GetPlayerAngle();

	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vAngle = Transform()->GetLocalAngle();
	
	vPos.x = vPlayerPos.x + 75 * (cos(vPlayerAngle.z));
	vPos.y = vPlayerPos.y + 75 * (sin(vPlayerAngle.z));
	vPos.z = vPlayerPos.z;

	vAngle.z = XM_PI / 2 + vPlayerAngle.z;
	vAngle.x = vPlayerAngle.x;
	vAngle.y =  vPlayerAngle.y;

	Transform()->SetLocalPos(vPos);
	Transform()->SetLocalRotate(vAngle);
}

//// 월드 행렬 계산하기
//// 크기 행렬
//Matrix matScale = XMMatrixScaling(m_vLocalScale.x, m_vLocalScale.y, m_vLocalScale.z);
//
//// 회전(자전) 행렬
//Matrix matRotate = XMMatrixRotationX(m_vLocalRotate.x);
//matRotate *= XMMatrixRotationY(m_vLocalRotate.y);
//matRotate *= XMMatrixRotationZ(m_vLocalRotate.z);
//
//// 이동 행렬
//Matrix matTrans = XMMatrixTranslation(m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);
//
//// 월드행렬
//m_matWorld = matScale * matRotate * matTrans;