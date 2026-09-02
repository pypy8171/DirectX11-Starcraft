#include "stdafx.h"
#include "PlanetScript.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Animator2D.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Transform.h"

#include "YongEngine/ResMgr.h"
#include "YongEngine/TimeMgr.h"

#include "YongEngine/Animation2D.h"

#include "ScriptMgr.h"

CPlanetScript::CPlanetScript()
{
	SetScriptType((UINT)SCRIPT_TYPE::PLANETSCRIPT);
}


CPlanetScript::~CPlanetScript()
{
}

int CPlanetScript::update()
{
	if (Object()->GetName() == L"Sun")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.01f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

	}
	else if (Object()->GetName() == L"SunChild")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.01f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);
	}
	else if (Object()->GetName() == L"MercuryDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.15f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);


		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.y += 0.1f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);
	}
	else if (Object()->GetName() == L"VenusDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.12f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.y += 0.1f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);

	}
	else if (Object()->GetName() == L"EarthDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.1f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.y += 0.05f*DT;
		vChildAngle.x += 0.05f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);

		Vec3 vCloudAngle = Object()->GetChild()[1]->Transform()->GetLocalAngle();
		vCloudAngle.y += 0.2f*DT;
		vCloudAngle.x += 0.2f*DT;
		Object()->GetChild()[1]->Transform()->SetLocalRotate(vCloudAngle);

	}
	else if (Object()->GetName() == L"MarsDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.08f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.y += 0.05f*DT;
		vChildAngle.x += 0.05f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);

	}
	else if (Object()->GetName() == L"JupiterDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.05f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.y += 0.1f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);

	}
	else if (Object()->GetName() == L"SaturnDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.03f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.y += 0.05f*DT;
		vChildAngle.x += 0.05f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);

		Vec3 vRingAngle = Object()->GetChild()[1]->Transform()->GetLocalAngle();
		vRingAngle.x += 0.1f*DT;
		Object()->GetChild()[1]->Transform()->SetLocalRotate(vRingAngle);

	}
	else if (Object()->GetName() == L"UranusDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.025f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.x += 0.1f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);

		Vec3 vRingAngle = Object()->GetChild()[1]->Transform()->GetLocalAngle();
		vRingAngle.x += 0.1f*DT;
		Object()->GetChild()[1]->Transform()->SetLocalRotate(vRingAngle);

	}
	else if (Object()->GetName() == L"NeptuneDummy")
	{
		Vec3 vAngle = Object()->Transform()->GetLocalAngle();
		vAngle.y += 0.02f*DT;
		Object()->Transform()->SetLocalRotate(vAngle);

		Vec3 vChildAngle = Object()->GetChild()[0]->Transform()->GetLocalAngle();
		vChildAngle.y += 0.05f*DT;
		vChildAngle.x += 0.05f*DT;
		Object()->GetChild()[0]->Transform()->SetLocalRotate(vChildAngle);

	}
	return 0;
}

int CPlanetScript::lateupdate()
{
	return 0;
}