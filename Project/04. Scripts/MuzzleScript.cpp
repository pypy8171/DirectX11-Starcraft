#include "stdafx.h"
#include "MuzzleScript.h"
#include "PlayerScript.h"

#include "YongEngine/Transform.h"

#include "YongEngine/KeyMgr.h"

#include "ScriptMgr.h"

CMuzzleScript::CMuzzleScript()
	: m_pPlayer(NULL)
{
	SetScriptType((UINT)SCRIPT_TYPE::MUZZLESCRIPT);
}


CMuzzleScript::~CMuzzleScript()
{
}


int CMuzzleScript::update()
{
	//Move();
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
