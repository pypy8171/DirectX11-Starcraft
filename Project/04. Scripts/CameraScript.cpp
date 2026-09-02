#include "stdafx.h"
#include "CameraScript.h"

#include "YongEngine/Core.h"

#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Camera.h"
#include "YongEngine/Grid.h"

#include "YongEngine/TimeMgr.h"
#include "YongEngine/KeyMgr.h"
#include "YongEngine/SceneMgr.h"

#include "YongEngine/Layer.h"
#include "YongEngine/Camera.h"
#include "YongEngine/Texture.h"
#include "YongEngine/Scene.h"

#include "ScriptMgr.h"
#include "UIMgr.h"

CCameraScript::CCameraScript()
	: m_vCamPos(Vec3(0.f,0.f,0.f))
	, m_bWheelOn(false)
	, m_iCameraDir(0)
{
	SetScriptType((UINT)SCRIPT_TYPE::CAMERASCRIPT);

}


CCameraScript::~CCameraScript()
{
}

int CCameraScript::update()
{
	bool bPerspective = Camera()->GetPerspective();	

	//if (L"MainCamera" != Object()->GetName())
	//	return 0;

	MoveCam();
	Transform()->finalupdate();
	CUIMgr::GetInst()->update();
	if (bPerspective)
	{
		RotateCam();
	}

	if (KEYAWAY(KEY_TYPE::KEY_8))
	{
		if (m_bWheelOn)
		{
			m_bWheelOn = false;
		}
		else
			m_bWheelOn = true;
	}
	

	return 0;
}

void CCameraScript::awake()
{
}

void CCameraScript::MoveCam()
{
	float fScale = Camera()->GetScale();

	CScene* pCurScene = (CScene*)CSceneMgr::GetInst()->GetCurrentScene();

	tResolution vResolution = CCore::GetInst()->GetResoultion();

	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	Vec3 vRot = Transform()->GetLocalAngle();
	Vec3 vRightDir = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUpDIr = Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vFrontDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);


	CLayer* pGridLayer = CSceneMgr::GetInst()->GetLayer(L"Grid");
	CGameObject* pGridObject = pGridLayer->GetObjVec()[0];

	int iTileSize = pGridObject->Grid()->GetTileSize();
	Vec2 vTileNum = pGridObject->Grid()->GetTileNum();


	// 이동 // 사용자가 수치 지정할 수 있도록
	if (m_bWheelOn)
	{

		if (KEYHOLD(KEY_TYPE::KEY_LEFT) || vMousePos.x < -vResolution.x / 2 + 20)
		{
			if (vPos.x < -iTileSize * vTileNum.x / 2 + vResolution.x / 2 + 60) //
				return;
			vPos -= vRightDir * DT * 400.f;
			m_iCameraDir = (UINT)CAMERA_DIR::LEFT;
		}
		else if (KEYHOLD(KEY_TYPE::KEY_RIGHT) || vMousePos.x > vResolution.x / 2 - 20)
		{
			if (vPos.x > iTileSize* vTileNum.x / 2 - vResolution.x / 2 - 60)
				return;
			vPos += vRightDir * DT * 400.f;
			m_iCameraDir = (UINT)CAMERA_DIR::RIGHT;
		}
		else if (KEYHOLD(KEY_TYPE::KEY_UP) || vMousePos.y > vResolution.y / 2 - 20)
		{
			if (vPos.y > iTileSize * vTileNum.y / 2 - vResolution.y / 2 - 60)
				return;
			vPos += vUpDIr * DT * 400.f;
			m_iCameraDir = (UINT)CAMERA_DIR::UP;
		}
		else if (KEYHOLD(KEY_TYPE::KEY_DOWN) || vMousePos.y < -vResolution.y / 2 + 20)
		{
			if (vPos.y < -iTileSize * vTileNum.y / 2 + vResolution.y / 2 - 20)
				return;
			vPos -= vUpDIr * DT * 400.f;
			m_iCameraDir = (UINT)CAMERA_DIR::DOWN;
		}
		else
		{
			m_iCameraDir = (UINT)CAMERA_DIR::NONE;
		}
	}

	Transform()->SetLocalPos(vPos);



	////if (KEYHOLD(KEY_TYPE::KEY_W)) // project일때 사용
	////{
	////	vPos += vFrontDir * DT * 100.f;
	////}
	////if (KEYHOLD(KEY_TYPE::KEY_S))
	////{
	////	vPos -= vFrontDir * DT * 100.f;
	////}

	//if (L"Temp Scene" != pCurScene->GetName())
	//{
	//	Transform()->SetLocalPos(vPos);
	//	return;
	//}
	//
	//CLayer* pLayer = CSceneMgr::GetInst()->GetLayer(L"Mouse");
	//CGameObject* pGameObject = nullptr;
	//vector<CGameObject*>& vecGameObject = pLayer->GetObjVec();
	////Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	//for (UINT i = 0; i < vecGameObject.size(); ++i)
	//{
	//	vecGameObject[i]->Transform()->SetLocalPos(Vec3(vMousePos.x +vPos.x, vMousePos.y + vPos.y, g_depthz));
	//	CKeyMgr::GetInst()->SetMousePos(Vec3(vMousePos.x + vPos.x, vMousePos.y + vPos.y, g_depthz));
	//}

	//Transform()->SetLocalPos(vPos);
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
