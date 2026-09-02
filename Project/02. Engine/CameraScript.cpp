#include "CameraScript.h"

#include "Transform.h"

#include "TimeMgr.h"
#include "KeyMgr.h"

#include "Camera.h"


CCameraScript::CCameraScript()
{
}


CCameraScript::~CCameraScript()
{
}

int CCameraScript::update()
{
	bool bPerspective = Camera()->GetPerspective();

	MoveCam();
	if (bPerspective)
	{
		RotateCam();
	}


	return 0;
}

void CCameraScript::awake()
{
}

void CCameraScript::MoveCam()
{
	float fScale = Camera()->GetScale();

	if (KEYHOLD(KEY_TYPE::KEY_1))
	{
		fScale += DT * 0.1f;
	}
	if (KEYHOLD(KEY_TYPE::KEY_2))
	{
		fScale -= DT * 0.1f;
	}

	Camera()->SetScale(fScale);

	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vRot = Transform()->GetLocalAngle();
	Vec3 vRightDIr = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUpDIr = Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vFrontDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	// 이동
	if (KEYHOLD(KEY_TYPE::KEY_A))
	{
		vPos -= vRightDIr * DT * 100.f;
	}
	if (KEYHOLD(KEY_TYPE::KEY_D))
	{
		vPos += vRightDIr * DT * 100.f;
	}
	if (KEYHOLD(KEY_TYPE::KEY_W))
	{
		vPos += vFrontDir * DT * 100.f;
	}
	if (KEYHOLD(KEY_TYPE::KEY_S))
	{
		vPos -= vFrontDir * DT * 100.f;
	}
	if (KEYHOLD(KEY_TYPE::KEY_R))
	{
		vPos += vUpDIr * DT * 100.f;
	}
	if (KEYHOLD(KEY_TYPE::KEY_F))
	{
		vPos -= vUpDIr * DT * 100.f;
	}

	Transform()->SetLocalPos(vPos);
}


void CCameraScript::RotateCam()
{
	Vec3 vRot = Transform()->GetLocalAngle();
	Vec3 vRightDIr = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUpDIr = Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vFrontDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	// 회전
	//if (KEYHOLD(KEY_TYPE::KEY_RBTN))
	//{
	if (KEYHOLD(KEY_TYPE::KEY_Q))
	{
		vRot.y -= (float)(XM_PI * 0.5 * DT);
	}
	if (KEYHOLD(KEY_TYPE::KEY_E))
	{
		vRot.y += (float)(XM_PI * 0.5 * DT);
	}
	if (KEYHOLD(KEY_TYPE::KEY_Z))
	{
		vRot.x -= (float)(XM_PI * 0.5 * DT);
	}
	if (KEYHOLD(KEY_TYPE::KEY_X))
	{
		vRot.x += (float)(XM_PI * 0.5 * DT);
	}
	if (KEYHOLD(KEY_TYPE::KEY_C))
	{
		vRot.z -= (float)(XM_PI * 0.5 * DT);
	}
	if (KEYHOLD(KEY_TYPE::KEY_V))
	{
		vRot.z += (float)(XM_PI * 0.5 * DT);
	}
	//}


	Transform()->SetLocalRotate(vRot);
}
