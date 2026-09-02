#include "stdafx.h"
#include "TestSceneMaker.h"

#include "YongEngine/Device.h"

#include "YongEngine/Animator2D.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"
#include "YongEngine/Collider.h"
#include "YongEngine/Camera.h"
#include "YongEngine/Grid.h"
#include "YongEngine/Script.h"
#include "YongEngine/Light.h"

#include "YongEngine/CollisionMgr.h"
#include "YongEngine/SceneMgr.h"
#include "YongEngine/KeyMgr.h"
#include "YongEngine/ResMgr.h"

#include "YongEngine/Prefab.h"
#include "YongEngine/Texture.h"
#include "YongEngine/Scene.h"

#include "Scripts/CameraScript.h"
#include "Scripts/PlayerScript.h"
#include "Scripts/MuzzleScript.h"
#include "Scripts/BulletScript.h"
#include "Scripts/MouseScript.h"
#include "Scripts/MarkScript.h"
#include "Scripts/MonsterScript.h"
#include "Scripts/ProtossUIScript.h"
#include "Scripts/PortraitScript.h"
#include "Scripts/StatusScript.h"
#include "Scripts/WireFrameScript.h"
#include "Scripts/ResourceScript.h"
#include "Scripts/MineralScript.h"
#include "Scripts/GasScript.h"
#include "Scripts/NexusScript.h"
#include "Scripts/UnitScript.h"
#include "Scripts/ProbeScript.h"
#include "Scripts/SeclectScript.h"
#include "Scripts/BuildingScript.h"
#include "Scripts/UnitShadScript.h"
#include "Scripts/UnitEffectScript.h"
#include "Scripts/ArchonEffectScript.h"
#include "Scripts/IconScript.h"
#include "Scripts/ButtonScript.h"
#include "Scripts/ProduceScript.h"

#include "Scripts/PlanetScript.h"

#include "YongEngine/Sound.h"

#include "SaveLoadMgr.h"

CTestSceneMaker::CTestSceneMaker()
{
}

CTestSceneMaker::~CTestSceneMaker()
{
}

void CTestSceneMaker::init()
{
	CDevice::GetInst()->SetRSState(RASTERIZER_TYPE::CULL_NONE);

	// Sound 파일 로딩
	//InitSound();
	//StudyScene();


	////bool Push(T Obj) 
 //   //    {
	//LPCRITICAL_SECTION m_CriticalSection;
 //               EnterCriticalSection(&m_CriticalSection);
 //               m_Queue.push(Obj);
 //               
 //               // semaphore count 증가
 //               bool bResult = (ReleaseSemaphore(m_Handle[SGTHREAD_SEMAPHORE],1,NULL) != 0);
 //               if(!bResult) 
 //               {
 //                       m_Queue.pop();                
 //                       CLogMgr::_LogError("CThreadQueue::Push() : Queue is Full~!");
 //               }
 //               
 //               LeaveCriticalSection(&m_CriticalSection);
 //               return bResult;
 //    //   }

	//bool Pop(T &Obj) 
 //       {
 //               bool bResult = false;
 //               
 //               SGTHREADEVENT_ID ReturnID = 
 //                       (SGTHREADEVENT_ID)WaitForMultipleObjects(2,m_Handle,FALSE,INFINITE);
 //               
 //               if(ReturnID == SGTHREAD_SEMAPHORE) 
 //               {
 //                       bResult = true;
 //                       EnterCriticalSection(&m_CriticalSection);
 //                       if(m_Queue.size()) 
 //                       {
 //                               Obj = m_Queue.front();
 //                               m_Queue.pop();                        
 //                       }
 //                       else 
 //                       {
 //                               CLogMgr::_LogError("CThreadQueue::Pop() : Queue is Empty~!");
 //                               bResult = false;
 //                       }
 //                       LeaveCriticalSection(&m_CriticalSection);
 //                       return bResult;
 //               }
 //               return bResult;
 //       }


	EditorScene();
	//CSaveLoadMgr::LoadScene(L"C:\\Users\\YongHwan\\source\\repos\\YongEngine\\Game_Release\\content\\Scene\\empty.scene");
	

	return;
}


void CTestSceneMaker::StudyScene()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	pCurScene->SetName(L"StudyScene");

	//return;

	// Layer 추가하기
	pCurScene->AddLayer(L"Camera");
	pCurScene->AddLayer(L"Planet");

	CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe", L"Texture\\universe.jpg");
	CTexture* pMercuryTex = CResMgr::GetInst()->Load<CTexture>(L"Mercury", L"Texture\\Universe\\Mercury_2.jpg");
	CTexture* pVenusTex = CResMgr::GetInst()->Load<CTexture>(L"Venus", L"Texture\\Universe\\Venus_2.jpg");
	CTexture* pMarsTex = CResMgr::GetInst()->Load<CTexture>(L"Mars", L"Texture\\Universe\\Mars_2.jpg");
	CTexture* pEarthTex = CResMgr::GetInst()->Load<CTexture>(L"Earth", L"Texture\\Universe\\Earth.jpg");
	CTexture* pEarthCloudTex = CResMgr::GetInst()->Load<CTexture>(L"EarthCloud", L"Texture\\Universe\\Earth_Cloud.jpg");
	CTexture* pSunTex = CResMgr::GetInst()->Load<CTexture>(L"Sun", L"Texture\\Universe\\Sun.jpg");
	//CTexture* pEarthNormalTex = CResMgr::GetInst()->Load<CTexture>(L"Earth", L"Texture\\Universe\\Earth_N.tif");
	CTexture* pJupiterTex = CResMgr::GetInst()->Load<CTexture>(L"Jupiter", L"Texture\\Universe\\Jupiter_2.jpg");
	CTexture* pSaturnTex = CResMgr::GetInst()->Load<CTexture>(L"Saturn", L"Texture\\Universe\\Saturn.jpg");
	CTexture* pSaturnRingTex = CResMgr::GetInst()->Load<CTexture>(L"SaturnRing", L"Texture\\Universe\\SaturnRing.png");
	CTexture* pUranusTex = CResMgr::GetInst()->Load<CTexture>(L"Uranus", L"Texture\\Universe\\Uranus.jpg");
	CTexture* pNeptuneTex = CResMgr::GetInst()->Load<CTexture>(L"Neptune", L"Texture\\Universe\\Neptune.jpg");

	CTexture* pMercuryBumpTex = CResMgr::GetInst()->Load<CTexture>(L"Mercury_Bump", L"Texture\\Universe\\Mercury_Bump.jpg");
	CTexture* pMarsBumpTex = CResMgr::GetInst()->Load<CTexture>(L"Mars_Bump", L"Texture\\Universe\\Mars_Bump.jpg");
	CTexture* pVenusBumpTex = CResMgr::GetInst()->Load<CTexture>(L"Venus_Bump", L"Texture\\Universe\\Venus_Bump.jpg");
	CTexture* pEarthBumpTex = CResMgr::GetInst()->Load<CTexture>(L"Earth_Bump", L"Texture\\Universe\\Earth_Bump.jpg");
	CTexture* pUranusRingTex = CResMgr::GetInst()->Load<CTexture>(L"UranusRing", L"Texture\\Universe\\UranusRing.jpg");
	CTexture* pMarsNTex = CResMgr::GetInst()->Load<CTexture>(L"Mars_N", L"Texture\\Universe\\Mars_N.jpg");

	//CTexture* pMooneTex = CResMgr::GetInst()->Load<CTexture>(L"Moon", L"Texture\\Universe\\Moon.jpg");
	//CTexture* pStarsTex = CResMgr::GetInst()->Load<CTexture>(L"Stars", L"Texture\\Universe\\Stars.jpg");
	//CTexture* pMilkiWayTex = CResMgr::GetInst()->Load<CTexture>(L"MilkyWay", L"Texture\\Universe\\MilkyWay.jpg");

	// Camera Object 만들기
	CGameObject* pCamObject = new CGameObject;
	pCamObject->SetName(L"MainCamera");

	pCamObject->AddComponent(new CCamera);
	pCamObject->AddComponent(new CCameraScript);
	pCamObject->Camera()->SetPerspective(true);
	pCamObject->Camera()->CheckLayerAll();


	if (pCurScene->GetName() == (L"StudyScene"))
	{
		pCamObject->Transform()->SetLocalPos(Vec3(1160, 735.f, 6300.f));
		pCamObject->Transform()->SetLocalRotate(Vec3(0.337f, -2.38f,0.f));
	}
	else
		pCamObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 4000.f));

	pCurScene->AddGameObject(L"Camera", pCamObject);

	//LTInfo.iType = 1;
	//LTInfo.tCol.vDiff = float4(1.f, 1.f, 1.f, 0.f);
	//LTInfo.tCol.vSpec = float4(0.0f, 0.0f, 0.0f, 0.f);
	//LTInfo.vPos = float4(0.f, 0.f, 5000.f, 1.f);
	//LTInfo.fDist = 5000.f;

	// Light Object
	//CGameObject* pLightObject = new CGameObject;
	//pLightObject->AddComponent(new CLight);

	//pLightObject->Light()->SetLightType(LIGHT_TYPE::POINT);
	//tLightCol tCol = {};
	//tCol.vDiff = Vec4(1.f, 1.f, 1.f, 0.f);
	//pLightObject->Light()->SetLightColor(tCol);
	//pLightObject->Light()->SetLightRange(5000.f);

	//pLightObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	//pCurScene->AddGameObject(L"Default", pLightObject);

	// SkyBox Object
	CGameObject* pSkyBox = new CGameObject;

	pSkyBox->SetName(L"SkyBox");
	pSkyBox->AddComponent(new CMeshRender);
	pSkyBox->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pSkyBox->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"SkyBoxMtrl"));

	pSkyBox->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUniverseTex);

	
	pSkyBox->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pSkyBox->Transform()->SetLocalScale(Vec3(2.f, 2.f, 2.f));

	pCurScene->AddGameObject(L"Default", pSkyBox);


	// 태양 Object 만들기
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Sun");

	pObject->AddComponent(new CPlanetScript);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CAnimator2D);

	pObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	CMaterial* pSunMtrl = pObject->MeshRender()->GetCloneMaterial();
	int iSun = 1;
	pSunMtrl->SetData(SHADER_PARAM::TEX_0, pSunTex);
	//pSunMtrl->SetData(SHADER_PARAM::INT_2, &iSun);

	pObject->Transform()->SetLocalScale(Vec3(109.f, 109.f, 109.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pCurScene->AddGameObject(L"Planet", pObject);

	CGameObject* pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"SunChild");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));

	CMaterial* pSunChildMtrl = pChildPlanet->MeshRender()->GetCloneMaterial();
	pSunChildMtrl->SetData(SHADER_PARAM::TEX_0, pSunTex);
	pSunChildMtrl->SetData(SHADER_PARAM::INT_2, &iSun);

	pChildPlanet->Transform()->SetLocalScale(Vec3(110.f, 110.f, 110.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pCurScene->AddGameObject(L"Planet", pChildPlanet);

	// 수성
	pObject = new CGameObject;
	pObject->SetName(L"MercuryDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Mercury");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));

	int iBump = 1;
	CMaterial* pMercuryMtrl = pChildPlanet->MeshRender()->GetCloneMaterial();
	pMercuryMtrl->SetData(SHADER_PARAM::TEX_0, pMercuryTex);
	pMercuryMtrl->SetData(SHADER_PARAM::TEX_1, pMercuryBumpTex);
	pMercuryMtrl->SetData(SHADER_PARAM::INT_1, &iBump);
	
	pChildPlanet->Transform()->SetLocalScale(Vec3(8.f, 8.f, 8.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(150.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);
	pCurScene->AddGameObject(L"Planet", pObject);
	for (int i = 0; i < 36; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(150.f*cos(i * 10 * 3.14 / 180), 0.f, 5000.f + 150.f*sin(i * 10 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}
	// 금성
	pObject = new CGameObject;
	pObject->SetName(L"VenusDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Venus");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	CMaterial* pVenusMtrl = pChildPlanet->MeshRender()->GetCloneMaterial();
	pVenusMtrl->SetData(SHADER_PARAM::TEX_0, pVenusTex);
	pVenusMtrl->SetData(SHADER_PARAM::TEX_1, pVenusBumpTex);
	pVenusMtrl->SetData(SHADER_PARAM::INT_1, &iBump);

	pChildPlanet->Transform()->SetLocalScale(Vec3(18.f, 18.f, 18.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(220.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);

	pCurScene->AddGameObject(L"Planet", pObject);
	for (int i = 0; i < 36; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(220.f*cos(i*10 * 3.14/180), 0.f, 5000.f + 220.f*sin(i * 10 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}

	// 지구
	pObject = new CGameObject;
	pObject->SetName(L"EarthDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));
	
	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Earth");
	
	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);
	
	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	CMaterial* pEarthMtrl = pChildPlanet->MeshRender()->GetCloneMaterial();

	int iAlpha = 1;
	pEarthMtrl->SetData(SHADER_PARAM::TEX_0, pEarthTex);
	pEarthMtrl->SetData(SHADER_PARAM::TEX_1, pEarthBumpTex);
	pEarthMtrl->SetData(SHADER_PARAM::INT_1, &iBump);
	//pMtrl->SetData(SHADER_PARAM::INT_0, &iAlpha);
	//pChildPlanet->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, pEarthNormalTex);
	
	pChildPlanet->Transform()->SetLocalScale(Vec3(20.f, 20.f, 20.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(330.f, 0.f, 0.f));
	
	pObject->AddChild(pChildPlanet);

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"EarthCloud");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	CMaterial* pEarthCloudMtrl = pChildPlanet->MeshRender()->GetCloneMaterial();

	pEarthCloudMtrl->SetData(SHADER_PARAM::TEX_0, pEarthCloudTex);
	pEarthCloudMtrl->SetData(SHADER_PARAM::INT_0, &iAlpha);

	pChildPlanet->Transform()->SetLocalScale(Vec3(22.f, 22.f, 22.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(330.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);
	pCurScene->AddGameObject(L"Planet", pObject);

	for (int i = 0; i < 36; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(330.f*cos(i * 10 * 3.14 / 180), 0.f, 5000.f + 330.f*sin(i * 10 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}
	// 화성
	pObject = new CGameObject;
	pObject->SetName(L"MarsDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Mars");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	CMaterial* pMarsMtrl = pChildPlanet->MeshRender()->GetCloneMaterial();

	iAlpha = 1;
	pMarsMtrl->SetData(SHADER_PARAM::TEX_0, pMarsTex);
	pMarsMtrl->SetData(SHADER_PARAM::TEX_1, pMarsBumpTex);
	pMarsMtrl->SetData(SHADER_PARAM::INT_1, &iBump);

	pChildPlanet->Transform()->SetLocalScale(Vec3(10.f, 10.f, 10.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(400.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);
	pCurScene->AddGameObject(L"Planet", pObject);
	for (int i = 0; i < 36; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(400.f*cos(i * 10 * 3.14 / 180), 0.f, 5000.f + 400.f*sin(i * 10 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}
	// 목성
	pObject = new CGameObject;
	pObject->SetName(L"JupiterDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Jupiter");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	pChildPlanet->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pJupiterTex);

	pChildPlanet->Transform()->SetLocalScale(Vec3(112.f, 112.f, 112.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(600.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);
	pCurScene->AddGameObject(L"Planet", pObject);
	for (int i = 0; i < 72; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(600.f*cos(i * 5 * 3.14 / 180), 0.f, 5000.f + 600.f*sin(i * 5 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}
	// 토성
	pObject = new CGameObject;
	pObject->SetName(L"SaturnDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Saturn");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	pChildPlanet->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pSaturnTex);

	pChildPlanet->Transform()->SetLocalScale(Vec3(94.f, 94.f, 94.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(800.f, 0.f, 0.f));
	pObject->AddChild(pChildPlanet);

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"SaturnRing");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	pChildPlanet->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pSaturnRingTex);

	pChildPlanet->Transform()->SetLocalScale(Vec3(150.f, 3.f, 150.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(800.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);
	pCurScene->AddGameObject(L"Planet", pObject);
	for (int i = 0; i < 108; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(800.f*cos(i * 3.3 * 3.14 / 180), 0.f, 5000.f + 800.f*sin(i * 3.3 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}
	// 천왕성
	pObject = new CGameObject;
	pObject->SetName(L"UranusDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Uranus");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	pChildPlanet->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUranusTex);

	pChildPlanet->Transform()->SetLocalScale(Vec3(40.f, 40.f, 40.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(1200.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"UranusRing");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	pChildPlanet->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pUranusRingTex);

	pChildPlanet->Transform()->SetLocalScale(Vec3(70.f, 3.f, 70.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(1200.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);

	pCurScene->AddGameObject(L"Planet", pObject);
	for (int i = 0; i < 108; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(1200.f*cos(i * 3.3 * 3.14 / 180), 0.f, 5000.f + 1200.f*sin(i * 3.3 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}
	// 해왕성
	pObject = new CGameObject;
	pObject->SetName(L"NeptuneDummy");

	pObject->AddComponent(new CPlanetScript);

	pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	pChildPlanet = new CGameObject;
	pChildPlanet->SetName(L"Neptune");

	pChildPlanet->AddComponent(new CMeshRender);
	pChildPlanet->AddComponent(new CPlanetScript);

	pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	pChildPlanet->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));
	pChildPlanet->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pNeptuneTex);

	pChildPlanet->Transform()->SetLocalScale(Vec3(39.f, 39.f, 39.f));
	pChildPlanet->Transform()->SetLocalPos(Vec3(1600.f, 0.f, 0.f));

	pObject->AddChild(pChildPlanet);
	pCurScene->AddGameObject(L"Planet", pObject);
	for (int i = 0; i < 144; ++i)
	{
		CGameObject* pOrb = new CGameObject;
		pOrb->SetName(L"Orb");
		pOrb->AddComponent(new CMeshRender);
		pOrb->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
		pOrb->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"ColorMtrl"));
		pOrb->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, nullptr);

		pOrb->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pOrb->Transform()->SetLocalPos(Vec3(1600.f*cos(i * 2.5 * 3.14 / 180), 0.f, 5000.f + 1600.f*sin(i * 2.5 * 3.14 / 180)));

		pCurScene->AddGameObject(L"Planet", pOrb);
	}

	//// 명왕성
	//pObject = new CGameObject;
	//pObject->SetName(L"PlutoDummy");

	////CPlanetScript* pPlanetScript = new CPlanetScript;
	//pObject->AddComponent(new CPlanetScript);

	//pObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	//pObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 5000.f));

	//pChildPlanet = new CGameObject;
	//pChildPlanet->SetName(L"Pluto");

	//pChildPlanet->AddComponent(new CMeshRender);
	//pChildPlanet->AddComponent(new CPlanetScript);

	//pChildPlanet->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"SphereMesh"));
	//pChildPlanet->MeshRender()->SetMaterial( CResMgr::GetInst()->Load<CMaterial>(L"TestMtrl"));

	//pChildPlanet->Transform()->SetLocalScale(Vec3(2.f, 2.f, 2.f));
	//pChildPlanet->Transform()->SetLocalPos(Vec3(1500.f, 0.f, 0.f));

	//pObject->AddChild(pChildPlanet);
	//pCurScene->AddGameObject(L"Planet", pObject);


}

// 마우스는 애니메이션 있을때만 좌표 받음
void CTestSceneMaker::EditorScene()
{
	CScene* pCurScene = (CScene*)CSceneMgr::GetInst()->GetCurrentScene();
	pCurScene->SetName(L"Edit Scene");

	pCurScene->AddLayer(L"Camera");
	pCurScene->AddLayer(L"Mouse");
	pCurScene->AddLayer(L"ProtossUI");
	pCurScene->AddLayer(L"Skill");
	pCurScene->AddLayer(L"Mark");
	pCurScene->AddLayer(L"Prefab");
	pCurScene->AddLayer(L"Opponent");
	pCurScene->AddLayer(L"Ally");
	pCurScene->AddLayer(L"Button");
	pCurScene->AddLayer(L"Resource");
	pCurScene->AddLayer(L"ColTile");
	pCurScene->AddLayer(L"RouteTile");
	pCurScene->AddLayer(L"Map");
	pCurScene->AddLayer(L"Grid");
	//pCurScene->AddLayer(L"Selection");

	// 충돌 Layer 지정하기
	//CCollisionMgr::GetInst()->CollisionCheck(L"ColTile", L"Mouse");
	CCollisionMgr::GetInst()->CollisionCheck(L"Prefab", L"Prefab");
	CCollisionMgr::GetInst()->CollisionCheck(L"Grid", L"Mouse");
	CCollisionMgr::GetInst()->CollisionCheck(L"Prefab", L"Mouse");
	CCollisionMgr::GetInst()->CollisionCheck(L"Ally", L"Mouse");
	CCollisionMgr::GetInst()->CollisionCheck(L"Opponent", L"Mouse");
	CCollisionMgr::GetInst()->CollisionCheck(L"Button", L"Mouse");
	CCollisionMgr::GetInst()->CollisionCheck(L"Ally", L"Ally");
	CCollisionMgr::GetInst()->CollisionCheck(L"Opponent", L"Opponent");
	CCollisionMgr::GetInst()->CollisionCheck(L"Ally", L"Opponent");
	CCollisionMgr::GetInst()->CollisionCheck(L"Ally", L"Prefab");
	CCollisionMgr::GetInst()->CollisionCheck(L"Prefab", L"Opponent");
	CCollisionMgr::GetInst()->CollisionCheck(L"Skill", L"Ally");
	CCollisionMgr::GetInst()->CollisionCheck(L"Skill", L"Opponent");


	CTexture* pUniverseTex = CResMgr::GetInst()->Load<CTexture>(L"Universe", L"Texture\\universe.jpg");
	// material 세팅
	CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

	int i = 1;
	//pMtrl->SetData(SHADER_PARAM::TEX_0, pUniverseTex);
	pMtrl->SetData(SHADER_PARAM::INT_0, &i);


	CScript* pMouseScript = new CMouseScript;


	// Camera 만들기
	CGameObject* pCameraObject = new CGameObject;
	pCameraObject->SetName(L"MainCamera");

	pCameraObject->AddComponent(new CCamera);
	pCameraObject->AddComponent(new CCameraScript);
	pCameraObject->Camera()->SetPerspective(false);
	pCameraObject->Camera()->CheckLayerAll();

	pCurScene->AddGameObject(L"Camera", pCameraObject);

	// Grid Object 만들기
	CGameObject* pGridObject = new CGameObject;
	pGridObject->SetName(L"Grid");

	pGridObject->AddComponent(new CGrid);

	pGridObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pGridObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 100.f));

	pCurScene->AddGameObject(L"Grid", pGridObject);


	// 마우스
	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	CGameObject* pMouseObject = new CGameObject;
	pMouseObject->SetName(L"Mouse");

	pMouseObject->AddComponent(new CMeshRender);
	pMouseObject->AddComponent(new CCollider);

	pMouseObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pMouseObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

	pMouseObject->Transform()->SetLocalScale(Vec3(3.f, 3.f, 1.f));
	pMouseObject->Transform()->SetLocalPos(Vec3(vMousePos.x, vMousePos.y, vMousePos.z));

	pMouseObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
	pMouseObject->Collider()->SetOffsetScale(Vec3(0.25f, 0.25f, 1.f));

	pMouseObject->AddComponent(pMouseScript);

	pCurScene->AddGameObject(L"Mouse", pMouseObject);

	// 마크
	CGameObject* pMarkObject = new CGameObject;
	pMarkObject->SetName(L"Mark");

	pMarkObject->AddComponent(new CMeshRender);

	pMarkObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pMarkObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

	pMarkObject->Transform()->SetLocalScale(Vec3(10.f, 10.f, 1.f));
	pMarkObject->Transform()->SetLocalPos(Vec3(vMousePos.x, vMousePos.y, vMousePos.z));

	pMarkObject->AddComponent(new CMarkScript);

	pCurScene->AddGameObject(L"Mark", pMarkObject);

	// prefab
	///////////////////
	
	// Mineral Prefab
	CTexture* pMineralTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral_0", L"Texture\\Texture\\Protoss\\UI\\Resource\\Mineral\\Mineral_0.png");
	AddPrefab(L"Mineral", pMineralTex);
	
	// Gas Prefab
	CTexture* pGasTex = CResMgr::GetInst()->Load<CTexture>(L"Gas_0", L"Texture\\Texture\\Protoss\\UI\\Resource\\Gas\\Gas_0.png");
	AddPrefab(L"Gas", pGasTex);
	
	// Nexus Prefab // 반짝거리는 애니메이션 추가해야함
	CTexture* pNexus = CResMgr::GetInst()->Load<CTexture>(L"Nexus", L"Texture\\Texture\\Protoss\\Building\\Nexus\\Nexus_0.png");
	AddPrefab(L"Nexus", pNexus);
	
	// ArbiterTribunal Prefab
	CTexture* pArbiterTribunal = CResMgr::GetInst()->Load<CTexture>(L"Arbiter Tribunal", L"Texture\\Texture\\Protoss\\Building\\Arbiter Tribunal\\Arbiter Tribunal_0.png");
	AddPrefab(L"Arbiter Tribunal", pArbiterTribunal);
	
	// Assimilator
	CTexture* pAssimilator = CResMgr::GetInst()->Load<CTexture>(L"Assimilator", L"Texture\\Texture\\Protoss\\Building\\Assimilator\\Assimilator_0.png");
	AddPrefab(L"Assimilator", pAssimilator);
	
	// CitadelofAdun
	CTexture* pCitadel = CResMgr::GetInst()->Load<CTexture>(L"Citadel of Adun", L"Texture\\Texture\\Protoss\\Building\\Citadel of Adun\\Citadel of Adun_0.png");
	AddPrefab(L"Citadel of Adun", pCitadel);
	
	// Cybernetics Core // 업그레이드 시 돌아가는 애니메이션 추가해야함
	CTexture* pCore = CResMgr::GetInst()->Load<CTexture>(L"CyberneticsCore", L"Texture\\Texture\\Protoss\\Building\\Cybernetics Core\\Cybernetics Core_0.png");
	AddPrefab(L"Cybernetics Core", pCore);
	
	// FleetBeacon
	CTexture* pFleetBeacon = CResMgr::GetInst()->Load<CTexture>(L"Fleet Beacon", L"Texture\\Texture\\Protoss\\Building\\Fleet Beacon\\Fleet Beacon_0.png");
	AddPrefab(L"Fleet Beacon", pFleetBeacon);
	
	// Forge // 업그레이드 시 돌아가는 애니메이션 추가해야함
	CTexture* pForge = CResMgr::GetInst()->Load<CTexture>(L"Forge", L"Texture\\Texture\\Protoss\\Building\\Forge\\Forge_0.png");
	AddPrefab(L"Forge", pForge);
	
	// Gateway
	CTexture* pGateway = CResMgr::GetInst()->Load<CTexture>(L"Gateway", L"Texture\\Texture\\Protoss\\Building\\Gateway\\Gateway_0.png");
	AddPrefab(L"Gateway", pGateway);
	
	// Observatory
	CTexture* pObservatory = CResMgr::GetInst()->Load<CTexture>(L"Observatory", L"Texture\\Texture\\Protoss\\Building\\Observatory\\Observatory_0.png");
	AddPrefab(L"Observatory", pObservatory);
	
	// Cannon // 일어나는 애니메이션 추가해야함
	CTexture* pCannon = CResMgr::GetInst()->Load<CTexture>(L"Photon Cannon", L"Texture\\Texture\\Protoss\\Building\\Photon Cannon\\Photon Cannon_0.png");
	AddPrefab(L"Photon Cannon", pCannon);
	
	// Pylon // 반경 추가해야함
	CTexture* pPylon = CResMgr::GetInst()->Load<CTexture>(L"Pylon", L"Texture\\Texture\\Protoss\\Building\\Pylon\\Pylon_0.png");
	AddPrefab(L"Pylon", pPylon);
	
	// RoboticsFacility
	CTexture* pRoboticsFacility = CResMgr::GetInst()->Load<CTexture>(L"Robotics Facility", L"Texture\\Texture\\Protoss\\Building\\Robotics Facility\\Robotics Facility_0.png");
	AddPrefab(L"Robotics Facility", pRoboticsFacility);
	
	// RoboticsSupportBay
	CTexture* pRoboticsSupportBay = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support Bay", L"Texture\\Texture\\Protoss\\Building\\Robotics Support Bay\\Robotics Support Bay_0.png");
	AddPrefab(L"Robotics Support Bay", pRoboticsSupportBay);
	
	// ShieldBattery // 반짝거리는 애니메이션 추가해야함
	CTexture* pShieldBattery = CResMgr::GetInst()->Load<CTexture>(L"Shield Battery", L"Texture\\Texture\\Protoss\\Building\\Shield Battery\\Shield Battery_0.png");
	AddPrefab(L"Shield Battery", pShieldBattery);
	
	// Stargate // 생산시 깜빡이는 애니메이션 추가
	CTexture* pStargate = CResMgr::GetInst()->Load<CTexture>(L"Stargate", L"Texture\\Texture\\Protoss\\Building\\Stargate\\Stargate_0.png");
	AddPrefab(L"Stargate", pStargate);
	
	// TemplarArchieve
	CTexture* pTemplarArchives = CResMgr::GetInst()->Load<CTexture>(L"Templar Archives", L"Texture\\Texture\\Protoss\\Building\\Templar Archives\\Templar Archives_0.png");
	AddPrefab(L"Templar Archives", pTemplarArchives);
	
	//// TemplarArchieve
	//CTexture* pProtossUI = CResMgr::GetInst()->Load<CTexture>(L"ProtossUI", L"Texture\\MainUI\\MainFrame_1.png");
	//AddPrefab(L"ProtossUI", pProtossUI);
	
	// Zealot
	AddPrefab(L"Zealot", pUniverseTex);
	
	// Dragoon
	AddPrefab(L"Dragoon", pUniverseTex);
	
	// Scout
	AddPrefab(L"Scout", pUniverseTex);
	
	// Probe
	AddPrefab(L"Probe", pUniverseTex);
	
	// DarkTemplar
	AddPrefab(L"DarkTemplar", pUniverseTex);
	
	// Arbiter
	AddPrefab(L"Arbiter", pUniverseTex);
	
	// Corsair
	AddPrefab(L"Corsair", pUniverseTex);
	
	// Carrier
	AddPrefab(L"Carrier", pUniverseTex);
	
	// Shuttle
	AddPrefab(L"Shuttle", pUniverseTex);
	
	// Observer
	AddPrefab(L"Observer", pUniverseTex);
	
	// Archon
	AddPrefab(L"Archon", pUniverseTex);
	
	// Reaver
	AddPrefab(L"Reaver", pUniverseTex);
	
	// HighTemplar
	AddPrefab(L"HighTemplar", pUniverseTex);
	
	// DarkArchon
	AddPrefab(L"DarkArchon", pUniverseTex);
	
	// Intersceptor
	AddPrefab(L"Interceptor", pUniverseTex);
	
	// Button
	AddPrefab(L"BtnUI", nullptr);

	pCurScene->awake();
	pCurScene->start();
}

void CTestSceneMaker::AddPrefab(const wstring & _strName, CTexture * _pTex)
{
	wstring strFolderPath;
	strFolderPath = L"Texture\\Animation2D\\Protoss\\Unit\\";

	wstring strBuildingPath;
	strBuildingPath = L"Texture\\Animation2D\\Protoss\\";

	wstring strBuildingShadPath;
	strBuildingShadPath = L"Texture\\Texture\\Protoss\\Shad\\";

	wstring strButtonPath;
	strButtonPath = L"Texture\\Texture\\Protoss\\UI\\Button\\";
	
	OBJ_TYPE eUnitType = OBJ_TYPE::GROUNDUNIT;
	OBJ_TYPE eBuildingType = OBJ_TYPE::BUILDING;
	// material 세팅
	CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");

	int i = 1;
	pMtrl->SetData(SHADER_PARAM::INT_0, &i);

	CString strPrefabName = _strName.c_str();

	//strPrefabName += L"Prefab";

	CGameObject* pPrefab = new CGameObject;

	pPrefab->SetName(strPrefabName.GetBuffer());

	pPrefab->AddComponent(new CMeshRender);
	if(L"BtnUI" != _strName )
		pPrefab->AddComponent(new CCollider);
	pPrefab->AddComponent(new CResourceScript);


	pPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pPrefab->MeshRender()->SetMaterial(pMtrl);

	if (L"Mineral" == _strName) // 		neutral
	{
		pPrefab->AddComponent(new CMineralScript);

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0Shad00", L"Texture\\Resource\\Resource_00\\Shad\\ResourceShad_000.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0Shad01", L"Texture\\Resource\\Resource_00\\Shad\\ResourceShad_001.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0Shad02", L"Texture\\Resource\\Resource_00\\Shad\\ResourceShad_002.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0Shad03", L"Texture\\Resource\\Resource_00\\Shad\\ResourceShad_003.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0_00", L"Texture\\Resource\\Resource_00\\Img\\Resource_000.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0_01", L"Texture\\Resource\\Resource_00\\Img\\Resource_001.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0_02", L"Texture\\Resource\\Resource_00\\Img\\Resource_002.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral0_03", L"Texture\\Resource\\Resource_00\\Img\\Resource_003.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1Shad00", L"Texture\\Resource\\Resource_01\\Shad\\ResourceShad_010.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1Shad01", L"Texture\\Resource\\Resource_01\\Shad\\ResourceShad_011.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1Shad02", L"Texture\\Resource\\Resource_01\\Shad\\ResourceShad_012.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1Shad03", L"Texture\\Resource\\Resource_01\\Shad\\ResourceShad_013.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1_00", L"Texture\\Resource\\Resource_01\\Img\\Resource_010.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1_01", L"Texture\\Resource\\Resource_01\\Img\\Resource_011.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1_02", L"Texture\\Resource\\Resource_01\\Img\\Resource_012.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral1_03", L"Texture\\Resource\\Resource_01\\Img\\Resource_013.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2Shad00", L"Texture\\Resource\\Resource_02\\Shad\\ResourceShad_020.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2Shad01", L"Texture\\Resource\\Resource_02\\Shad\\ResourceShad_021.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2Shad02", L"Texture\\Resource\\Resource_02\\Shad\\ResourceShad_022.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2Shad03", L"Texture\\Resource\\Resource_02\\Shad\\ResourceShad_023.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2_00", L"Texture\\Resource\\Resource_02\\Img\\Resource_020.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2_01", L"Texture\\Resource\\Resource_02\\Img\\Resource_021.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2_02", L"Texture\\Resource\\Resource_02\\Img\\Resource_022.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Mineral2_03", L"Texture\\Resource\\Resource_02\\Img\\Resource_023.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"MineralOreChunck00", L"Texture\\Resource\\Mineral\\OreChunk05.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"GasOreChunck00", L"Texture\\Resource\\Gas\\GasOrb0.png");


		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectNeutral", L"Texture\\Texture\\Protoss\\UI\\Select\\Nertual\\0.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly0", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly1", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly2", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly3", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_3.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly4", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_4.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly5", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_5.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly6", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_6.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly7", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_7.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly8", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_8.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"SelectAlly9", L"Texture\\Texture\\Protoss\\UI\\Select\\Ally\\Ally_9.png");

		pPrefab->Transform()->SetLocalScale(Vec3(64.f, 96.f, 1.f));

		pPrefab->SetObjType(OBJ_TYPE::RESOURCE);
	}
	else if (L"Gas" == _strName)
	{
		pPrefab->AddComponent(new CGasScript);

		pPrefab->Transform()->SetLocalScale(Vec3(128.f, 64.f, 1.f));
		pPrefab->SetObjType(OBJ_TYPE::RESOURCE);
	}
	else if (L"Zealot" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::ZEALOT);
		pUnitScript->SetUnitSpeed(68.f);
		pUnitScript->SetUnitHp(100);
		pUnitScript->SetUnitShield(60);
		pUnitScript->SetMaxHp(100);
		pUnitScript->SetMaxShield(60);
		pUnitScript->SetUnitGroundAtt(8);
		pUnitScript->SetUnitRange(1);
		pUnitScript->SetMineralCost(100);

		wstring ZealotAnimationName = strFolderPath + L"Zealot\\ZealotMove\\";
		pPrefab->Animator2D()->AddAnimation(ZealotAnimationName, L"ZealotMove",true);
		ZealotAnimationName = strFolderPath + L"Zealot\\ZealotAtt\\";
		pPrefab->Animator2D()->AddAnimation(ZealotAnimationName, L"ZealotAtt", true);
		ZealotAnimationName = strFolderPath + L"Zealot\\ZealotDie\\";
		pPrefab->Animator2D()->AddAnimation(ZealotAnimationName, L"ZealotDie", true);
		pPrefab->Animator2D()->SetCurAnimName(L"ZealotMove");
			
		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Zealot\\ZealotMove\\move_016.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f)); // 8천에 4천 잡히는데 _ptex->getwidth()하면 // 다른 이미지가 들어가있나?

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(23.f / vPrefabScale.x, 19.f / vPrefabScale.y, 1.f));
	}
	else if (L"Dragoon" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::DRAGOON);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(100);
		pUnitScript->SetUnitShield(80);
		pUnitScript->SetMaxHp(100);
		pUnitScript->SetMaxShield(80);
		pUnitScript->SetUnitGroundAtt(20);
		pUnitScript->SetUnitAirAtt(20);
		pUnitScript->SetUnitRange(4);
		pUnitScript->SetMineralCost(125);
		pUnitScript->SetGasCost(50);

		wstring DragoonAnimationName = strFolderPath + L"Dragoon\\DragoonMove\\";
		pPrefab->Animator2D()->AddAnimation(DragoonAnimationName, L"DragoonMove", true, 0.1f);
		DragoonAnimationName = strFolderPath + L"Dragoon\\DragoonAtt\\";
		pPrefab->Animator2D()->AddAnimation(DragoonAnimationName, L"DragoonAtt", true);
		DragoonAnimationName = strFolderPath + L"Dragoon\\DragoonDie\\";
		pPrefab->Animator2D()->AddAnimation(DragoonAnimationName, L"DragoonDie", true, 0.1f);
		DragoonAnimationName = strFolderPath + L"Dragoon\\DragoonNormal\\";
		pPrefab->Animator2D()->AddAnimation(DragoonAnimationName, L"DragoonNormal", true);
		pPrefab->Animator2D()->SetCurAnimName(L"DragoonMove");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Dragoon\\DragoonNormal\\Normal_7.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(96.f, 96.f, 1.f)); // 8천에 4천 잡히는데 _ptex->getwidth()하면 // 다른 이미지가 들어가있나?

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(32.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"Scout" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::AIRUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::SCOUT);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(150);
		pUnitScript->SetUnitShield(100);
		pUnitScript->SetMaxHp(150);
		pUnitScript->SetMaxShield(100);
		pUnitScript->SetUnitGroundAtt(8);
		pUnitScript->SetUnitAirAtt(28);
		pUnitScript->SetUnitRange(4);
		pUnitScript->SetMineralCost(250);
		pUnitScript->SetGasCost(125);

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		wstring AnimationName = strFolderPath + L"Scout\\ScoutAtt\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ScoutAtt", true);
		AnimationName = strFolderPath + L"Scout\\ScoutNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ScoutNormal", true);
		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ScoutDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"ScoutNormal");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Scout\\ScoutNormal\\normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(72.f, 72.f, 1.f)); 

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(36.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"Probe" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->AddComponent(new CProbeScript);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::PROBE);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(20);
		pUnitScript->SetUnitShield(20);
		pUnitScript->SetMaxHp(20);
		pUnitScript->SetMaxShield(20);
		pUnitScript->SetUnitGroundAtt(5);
		pUnitScript->SetUnitRange(2);
		pUnitScript->SetMineralCost(50);

		wstring AnimationName = strFolderPath + L"Probe\\ProbeNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ProbeNormal", true);

		AnimationName = strBuildingPath + L"Effect\\Probe_Att\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ProbeAtt", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ProbeDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"ProbeNormal");


		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Probe\\ProbeNormal\\Normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(32.f, 32.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(23.f / vPrefabScale.x, 23.f / vPrefabScale.y, 1.f));

	}
	else if (L"DarkTemplar" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::DARKTEMPLAR);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(40);
		pUnitScript->SetUnitShield(40);
		pUnitScript->SetMaxHp(40);
		pUnitScript->SetMaxShield(40);
		pUnitScript->SetUnitGroundAtt(40);
		pUnitScript->SetUnitRange(1);
		pUnitScript->SetMineralCost(125);
		pUnitScript->SetGasCost(125);

		wstring AnimationName = strFolderPath + L"Dark Templar\\Dark TemplarAtt\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark TemplarAtt", true);
		AnimationName = strFolderPath + L"Dark Templar\\Dark TemplarDie\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark TemplarDie", true);
		AnimationName = strFolderPath + L"Dark Templar\\Dark TemplarMove\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark TemplarMove", true);

		pPrefab->Animator2D()->SetCurAnimName(L"Dark TemplarMove");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Dark Templar\\Dark TemplarMove\\move_016.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(64.f, 64.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(24.f / vPrefabScale.x, 26.f / vPrefabScale.y, 1.f));

	}
	else if (L"Arbiter" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::AIRUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::ARBITER);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(200);
		pUnitScript->SetUnitShield(150);
		pUnitScript->SetMaxHp(200);
		pUnitScript->SetMaxShield(150);
		pUnitScript->SetUnitGroundAtt(10);
		pUnitScript->SetUnitAirAtt(10);
		pUnitScript->SetUnitRange(5);
		pUnitScript->SetMineralCost(150);
		pUnitScript->SetGasCost(350);

		wstring AnimationName = strFolderPath + L"Arbiter\\ArbiterNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArbiterNormal", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArbiterDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"ArbiterNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Arbiter\\ArbiterNormal\\Normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(76.f, 76.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(44.f / vPrefabScale.x, 44.f / vPrefabScale.y, 1.f));

	}
	else if (L"Carrier" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::AIRUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::CARRIER);
		pUnitScript->SetUnitSpeed(56.f);
		pUnitScript->SetUnitHp(300);
		pUnitScript->SetUnitShield(150);
		pUnitScript->SetMaxHp(300);
		pUnitScript->SetMaxShield(150);
		pUnitScript->SetUnitRange(8);
		pUnitScript->SetMineralCost(350);
		pUnitScript->SetGasCost(250);

		wstring AnimationName = strFolderPath + L"Carrier\\CarrierNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"CarrierNormal", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_M\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"CarrierDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"CarrierNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Carrier\\CarrierNormal\\Normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(64.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));

	}
	else if (L"Corsair" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::AIRUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::CORSAIR);
		pUnitScript->SetUnitSpeed(113.f);
		pUnitScript->SetUnitHp(100);
		pUnitScript->SetUnitShield(80);
		pUnitScript->SetMaxHp(100);
		pUnitScript->SetMaxShield(80);
		pUnitScript->SetUnitAirAtt(5);
		pUnitScript->SetUnitRange(5);
		pUnitScript->SetMineralCost(125);
		pUnitScript->SetGasCost(100);

		wstring AnimationName = strFolderPath + L"Corsair\\CorsairNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"CorsairNormal", true);

		AnimationName = strFolderPath + L"Corsair\\CorsairAtt\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"CorsairAtt", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"CorsairDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"CorsairNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Corsair\\CorsairNormal\\normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(60.f, 60.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(36.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"Shuttle" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::AIRUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::SHUTTLE);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(80);
		pUnitScript->SetUnitShield(60);
		pUnitScript->SetMaxHp(80);
		pUnitScript->SetMaxShield(60);
		pUnitScript->SetUnitRange(1);
		pUnitScript->SetMineralCost(200);

		wstring AnimationName = strFolderPath + L"Shuttle\\ShuttleNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ShuttleNormal", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ShuttleDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"ShuttleNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Shuttle\\ShuttleNormal\\normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(60.f, 60.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(40.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"Observer" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::AIRUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::OBSERVER);
		pUnitScript->SetUnitSpeed(56.f);
		pUnitScript->SetUnitHp(40);
		pUnitScript->SetUnitShield(20);
		pUnitScript->SetMaxHp(40);
		pUnitScript->SetMaxShield(20);
		pUnitScript->SetUnitRange(7); // 시야
		pUnitScript->SetMineralCost(25);
		pUnitScript->SetGasCost(75);

		wstring AnimationName = strFolderPath + L"Observer\\ObserverNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ObserverNormal", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ObserverDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"ObserverNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Observer\\ObserverNormal\\normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(40.f, 40.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(32.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"Archon" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::ARCHON);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(10);
		pUnitScript->SetUnitShield(350);
		pUnitScript->SetMaxHp(10);
		pUnitScript->SetMaxShield(350);
		pUnitScript->SetUnitGroundAtt(30);
		pUnitScript->SetUnitAirAtt(30);
		pUnitScript->SetUnitRange(3);

		wstring AnimationName = strFolderPath + L"Archon\\ArchonAtt\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonAtt", true);
		AnimationName = strFolderPath + L"Archon\\ArchonAura\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonAura", true);
		AnimationName = strFolderPath + L"Archon\\ArchonBody\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonBody", true);
		AnimationName = strFolderPath + L"Archon\\ArchonCreate\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonCreate", true);
		AnimationName = strFolderPath + L"Archon\\ArchonNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonNormal", true);
		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"ArchonNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Archon\\ArchonNormal\\normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(120.f, 120.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(32.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"DarkArchon" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::DARKARCHON);
		pUnitScript->SetUnitSpeed(84.f);
		pUnitScript->SetUnitHp(25);
		pUnitScript->SetUnitShield(200);
		pUnitScript->SetMaxHp(25);
		pUnitScript->SetMaxShield(200);
		pUnitScript->SetUnitRange(6);

		wstring AnimationName = strFolderPath + L"Dark Archon\\Dark ArchonDie\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark ArchonDie", true);
		AnimationName = strFolderPath + L"Dark Archon\\Dark ArchonAura\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark ArchonAura", true);
		AnimationName = strFolderPath + L"Dark Archon\\Dark ArchonBody\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark ArchonBody", true);
		AnimationName = strFolderPath + L"Dark Archon\\Dark ArchonCreate\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark ArchonCreate", true);
		AnimationName = strFolderPath + L"Dark Archon\\Dark ArchonNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark ArchonNormal", true);

		pPrefab->Animator2D()->SetCurAnimName(L"Dark ArchonNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Dark Archon\\Dark ArchonNormal\\normal_016.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(120.f, 120.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(32.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"HighTemplar" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::HIGHTEMPLAR);
		pUnitScript->SetUnitSpeed(55.f);
		pUnitScript->SetUnitHp(40);
		pUnitScript->SetUnitShield(40);
		pUnitScript->SetMaxHp(40);
		pUnitScript->SetMaxShield(40);
		pUnitScript->SetUnitRange(6);
		pUnitScript->SetMineralCost(50);
		pUnitScript->SetGasCost(150);

		wstring AnimationName = strFolderPath + L"High Templar\\High TemplarAtt\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarAtt", true);
		AnimationName = strFolderPath + L"High Templar\\High TemplarDie\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarDie", true);
		AnimationName = strFolderPath + L"High Templar\\High TemplarMove\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarMove", true);
		AnimationName = strFolderPath + L"High Templar\\High TemplarNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarNormal", true);
		AnimationName = strFolderPath + L"High Templar\\High TemplarShad\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarShad", true);

		pPrefab->Animator2D()->SetCurAnimName(L"High TemplarMove");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\High Templar\\High TemplarNormal\\normal_016.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(24.f / vPrefabScale.x, 24.f / vPrefabScale.y, 1.f));

	}
	else if (L"Reaver" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::GROUNDUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::REAVER);
		pUnitScript->SetUnitSpeed(30.f);
		pUnitScript->SetUnitHp(100);
		pUnitScript->SetUnitShield(80);
		pUnitScript->SetMaxHp(100);
		pUnitScript->SetMaxShield(80);
		pUnitScript->SetUnitGroundAtt(100); // 스캐럽이어야 함
		pUnitScript->SetUnitRange(8);
		pUnitScript->SetMineralCost(200);
		pUnitScript->SetGasCost(100);

		wstring AnimationName = strFolderPath + L"Reaver\\ReaverMove\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ReaverMove", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"ReaverDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"ReaverMove");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Reaver\\ReaverMove\\move_016.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(84.f, 84.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(32.f / vPrefabScale.x, 32.f / vPrefabScale.y, 1.f));

	}
	else if (L"Interceptor" == _strName)
	{
		CUnitScript* pUnitScript = new CUnitScript;
		pPrefab->AddComponent(pUnitScript);
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->SetObjType(OBJ_TYPE::AIRUNIT);
		pUnitScript->SetUnitType(UNIT_TYPE::INTERCEPTOR);
		pUnitScript->SetUnitSpeed(50.f);
		pUnitScript->SetUnitHp(40);
		pUnitScript->SetUnitShield(40);
		pUnitScript->SetMaxHp(40);
		pUnitScript->SetMaxShield(40);
		pUnitScript->SetUnitGroundAtt(10);
		pUnitScript->SetUnitAirAtt(10);
		pUnitScript->SetMineralCost(25);

		wstring AnimationName = strFolderPath + L"Interceptor\\InterceptorNormal\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"InterceptorNormal", true);
		AnimationName = strFolderPath + L"Interceptor\\InterceptorAtt\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"InterceptorAtt", true);

		AnimationName = strBuildingPath + L"Effect\\Explosion_S\\";
		pPrefab->Animator2D()->AddAnimation(AnimationName, L"InterceptorDie", true);

		pPrefab->Animator2D()->SetCurAnimName(L"InterceptorNormal");

		pPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"UnitMtrl"));
		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Interceptor\\InterceptorNormal\\normal_16.png");
		pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pPrefab->Transform()->SetLocalScale(Vec3(32.f, 32.f, 1.f));

		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		pPrefab->Collider()->SetOffsetScale(Vec3(16.f / vPrefabScale.x, 16.f / vPrefabScale.y, 1.f));

	}
	else if (L"BtnUI" == _strName)
	{
		pPrefab->AddComponent(new CIconScript);
		pPrefab->SetObjType(OBJ_TYPE::UI);
		pPrefab->Transform()->SetLocalScale(Vec3(0.1f, 0.1f, 1.f));
	}
	else 
	{
		CBuildingScript* pBuildingScript = new CBuildingScript;
		pPrefab->AddComponent(new CAnimator2D);
		pPrefab->AddComponent(pBuildingScript);
		pPrefab->AddComponent(new CProduceScript);
		pPrefab->SetObjType(OBJ_TYPE::BUILDING);
		pPrefab->SetObjType(eBuildingType);
		//pPrefab->AddComponent(new CNexusScript);
		if (L"Nexus" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(750);
			pBuildingScript->SetBuildingShield(750);
			pBuildingScript->SetMaxHp(750);
			pBuildingScript->SetMaxShield(750);
			pBuildingScript->SetMineralCost(400);
		}
		else if (L"Pylon" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(300);
			pBuildingScript->SetBuildingShield(300);
			pBuildingScript->SetMaxHp(300);
			pBuildingScript->SetMaxShield(300);
			pBuildingScript->SetMineralCost(100);
		}
		else if (L"Assimilator" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(450);
			pBuildingScript->SetBuildingShield(450);
			pBuildingScript->SetMaxHp(450);
			pBuildingScript->SetMaxShield(450);
			pBuildingScript->SetMineralCost(100);
		}
		else if (L"Gateway" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(500);
			pBuildingScript->SetBuildingShield(500);
			pBuildingScript->SetMaxHp(500);
			pBuildingScript->SetMaxShield(500);
			pBuildingScript->SetMineralCost(150);
		}
		else if (L"Forge" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(550);
			pBuildingScript->SetBuildingShield(550);
			pBuildingScript->SetMaxHp(550);
			pBuildingScript->SetMaxShield(550);
			pBuildingScript->SetMineralCost(150);
		}
		else if (L"Cybernetics Core" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(550);
			pBuildingScript->SetBuildingShield(550);
			pBuildingScript->SetMaxHp(550);
			pBuildingScript->SetMaxShield(550);
			pBuildingScript->SetMineralCost(200);
		}
		else if (L"Photon Cannon" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(100);
			pBuildingScript->SetBuildingShield(100);
			pBuildingScript->SetMaxHp(100);
			pBuildingScript->SetMaxShield(100);
			pBuildingScript->SetMineralCost(150);
		}
		else if (L"Shield Battery" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(200);
			pBuildingScript->SetBuildingShield(200);
			pBuildingScript->SetMaxHp(200);
			pBuildingScript->SetMaxShield(200);
			pBuildingScript->SetMineralCost(100);
		}
		else if (L"Robotics Facility" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(500);
			pBuildingScript->SetBuildingShield(500);
			pBuildingScript->SetMaxHp(500);
			pBuildingScript->SetMaxShield(500);
			pBuildingScript->SetMineralCost(200);
			pBuildingScript->SetGasCost(200);
		}
		else if (L"Robotics Support Bay" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(450);
			pBuildingScript->SetBuildingShield(450);
			pBuildingScript->SetMaxHp(450);
			pBuildingScript->SetMaxShield(450);
			pBuildingScript->SetMineralCost(150);
			pBuildingScript->SetGasCost(150);
		}
		else if (L"Observatory" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(250);
			pBuildingScript->SetBuildingShield(250);
			pBuildingScript->SetMaxHp(250);
			pBuildingScript->SetMaxShield(250);
			pBuildingScript->SetMineralCost(50);
			pBuildingScript->SetGasCost(100);
		}
		else if (L"Citadel of Adun" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(450);
			pBuildingScript->SetBuildingShield(450);
			pBuildingScript->SetMaxHp(450);
			pBuildingScript->SetMaxShield(450);
			pBuildingScript->SetMineralCost(150);
			pBuildingScript->SetGasCost(100);
		}
		else if (L"Templar Archives" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(500);
			pBuildingScript->SetBuildingShield(500);
			pBuildingScript->SetMaxHp(500);
			pBuildingScript->SetMaxShield(500);
			pBuildingScript->SetMineralCost(150);
			pBuildingScript->SetGasCost(200);
		}
		else if (L"Stargate" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(600);
			pBuildingScript->SetBuildingShield(600);
			pBuildingScript->SetMaxHp(600);
			pBuildingScript->SetMaxShield(600);
			pBuildingScript->SetMineralCost(150);
			pBuildingScript->SetGasCost(150);
		}
		else if (L"Fleet Beacon" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(500);
			pBuildingScript->SetBuildingShield(500);
			pBuildingScript->SetMaxHp(500);
			pBuildingScript->SetMaxShield(500);
			pBuildingScript->SetMineralCost(300);
			pBuildingScript->SetGasCost(200);
		}
		else if (L"Arbiter Tribunal" == pPrefab->GetName())
		{
			pBuildingScript->SetBuildingHp(500);
			pBuildingScript->SetBuildingShield(500);
			pBuildingScript->SetMaxHp(500);
			pBuildingScript->SetMaxShield(500);
			pBuildingScript->SetMineralCost(200);
			pBuildingScript->SetGasCost(200);
		}

		wstring AnimName = strBuildingPath + L"Effect\\Warp\\";
		pPrefab->Animator2D()->AddAnimation(AnimName, L"Warp", true);

		AnimName = strBuildingPath + L"Effect\\Explosion_L\\";
		pPrefab->Animator2D()->AddAnimation(AnimName, L"Explosion_L", true);

		AnimName = strBuildingPath + L"Effect\\Vestige\\";
		pPrefab->Animator2D()->AddAnimation(AnimName, L"Vestige", true);

		wstring temp = pPrefab->GetName();

		AnimName = strBuildingPath + L"BuildTime\\";
		AnimName += temp;
		AnimName += L"\\";

		//wstring AnimationName = strBuildingPath + L"Effect\\Explosion_L\\";
		//pPrefab->Animator2D()->AddAnimation(AnimationName, L"InterceptorDie", true);

		wstring AnimKey = pPrefab->GetName();
		pPrefab->Animator2D()->AddAnimation(AnimName, AnimKey, false);
		pPrefab->Animator2D()->SetCurAnimName(L"Warp");
	}

	if (L"Zealot" != _strName && L"Dragoon" != _strName && L"Scout" != _strName && L"Probe" != _strName && L"DarkTemplar" != _strName
		&& L"Carrier" != _strName && L"Corsair" != _strName && L"Shuttle" != _strName && L"Observer" != _strName && L"Arbiter" != _strName
		&& L"Archon" != _strName && L"DarkArchon" != _strName && L"Reaver" != _strName && L"HighTemplar" != _strName && L"Interceptor" != _strName)
	{
		if (nullptr != _pTex)
		{
			pPrefab->Transform()->SetLocalScale(Vec3(_pTex->GetWidth(), _pTex->GetHeight(), 1.f));
			pPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, _pTex); // 여기가 문제
		}
	}
	//else
	//{
	//	pPrefab->SetObjType(eUnitType);
	//}

	if (L"BtnUI" != _strName && OBJ_TYPE::GROUNDUNIT != pPrefab->GetObjType() && OBJ_TYPE::AIRUNIT != pPrefab->GetObjType() 
		&& OBJ_TYPE::BUILDING != pPrefab->GetObjType())
	{
		pPrefab->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
		pPrefab->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	}
	else if (L"BtnUI" != _strName)
	{
		pPrefab->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
	}

	if (OBJ_TYPE::RESOURCE == pPrefab->GetObjType())
	{
		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		if (L"Mineral" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(64.f / vPrefabScale.x, 72.f / vPrefabScale.y, 1.f));
		}
		if (L"Gas" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(128.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
	}

	if (OBJ_TYPE::BUILDING == pPrefab->GetObjType())
	{
		Vec3 vPrefabScale = pPrefab->Transform()->GetLocalScale();
		if (L"Nexus" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(128.f / vPrefabScale.x, 96.f / vPrefabScale.y, 1.f));
		}
		else if (L"Pylon" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(64.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Assimilator" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(128 / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Forge" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Gateway" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(128.f / vPrefabScale.x, 96.f / vPrefabScale.y, 1.f));
		}
		else if (L"Photon Cannon" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(64.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Cybernetics Core" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Shield Battery" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Robotics Facility" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Stargate" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(128.f / vPrefabScale.x, 96.f / vPrefabScale.y, 1.f));
		}
		else if (L"Citadel of Adun" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Templar Archives" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Fleet Beacon" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(128.f / vPrefabScale.x, 96.f / vPrefabScale.y, 1.f));
		}
		else if (L"Arbiter Tribunal" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Robotics Support Bay" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}
		else if (L"Observatory" == pPrefab->GetName())
		{
			pPrefab->Collider()->SetOffsetScale(Vec3(96.f / vPrefabScale.x, 64.f / vPrefabScale.y, 1.f));
		}


	}


	CResMgr::GetInst()->AddResource<CPrefab>(_strName, new CPrefab(pPrefab));


	// 그림자 및 이펙트 & 버튼 리소스
	if (L"Zealot" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"ZealotShadPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitShadScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring ZealotAnimationName = strFolderPath + L"Zealot\\ZealotMoveShad\\";
		pShadPrefab->Animator2D()->AddAnimation(ZealotAnimationName, L"ZealotMoveShad", true);
		ZealotAnimationName = strFolderPath + L"Zealot\\ZealotAttShad\\";
		pShadPrefab->Animator2D()->AddAnimation(ZealotAnimationName, L"ZealotAttShad", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"ZealotMoveShad");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Zealot\\ZealotMoveShad\\zealotShad_016.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		Vec3 vParentPos = pPrefab->Transform()->GetLocalPos();

		pShadPrefab->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(vParentPos);

		pPrefab->AddChild(pShadPrefab);
	}
	else if (L"HighTemplar" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"High TemplarShadPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitShadScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"High Templar\\High TemplarMoveShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarMoveShad", true);
		AnimationName = strFolderPath + L"High Templar\\High TemplarAttShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarAttShad", true);
		AnimationName = strFolderPath + L"High Templar\\High TemplarNormalShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarNormalShad", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"High TemplarMoveShad");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\High Templar\\High TemplarNormalShad\\Shad_016.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		Vec3 vParentPos = pPrefab->Transform()->GetLocalPos();

		pShadPrefab->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(vParentPos);

		pPrefab->AddChild(pShadPrefab);
	}
	else if (L"Dragoon" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"DragoonShadPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitShadScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"Dragoon\\DragoonMoveShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"DragoonMoveShad", true);
		AnimationName = strFolderPath + L"Dragoon\\DragoonAttShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"DragoonAttShad", true);
		AnimationName = strFolderPath + L"Dragoon\\DragoonNormalShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"DragoonNormalShad", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"DragoonMoveShad");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Dragoon\\DragoonNormalShad\\Stand_07.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		Vec3 vParentPos = pPrefab->Transform()->GetLocalPos();

		pShadPrefab->Transform()->SetLocalScale(Vec3(96.f, 96.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(vParentPos);

		pPrefab->AddChild(pShadPrefab);
	}
	else if (L"Shuttle" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"ShuttleEffectPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitEffectScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"Shuttle\\ShuttleMoveEffect\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"ShuttleMoveEffect", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"ShuttleMoveEffect");

		Vec3 vParentPos = pPrefab->Transform()->GetLocalPos();

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Shuttle\\ShuttleMoveEffect\\moveEff_16.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);

		pShadPrefab->Transform()->SetLocalScale(Vec3(60.f, 60.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(vParentPos);

		pPrefab->AddChild(pShadPrefab);
	}
	else if (L"Scout" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"ScoutEffectPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitEffectScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"Scout\\ScoutMoveEffect\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"ScoutMoveEffect", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"ScoutMoveEffect");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Scout\\ScoutMoveEffect\\moveEff_16.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		Vec3 vParentPos = pPrefab->Transform()->GetLocalPos();

		pShadPrefab->Transform()->SetLocalScale(Vec3(72.f, 72.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(vParentPos);

		pPrefab->AddChild(pShadPrefab);
	}
	else if (L"Carrier" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"CarrierEffectPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitEffectScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"Carrier\\CarrierMoveEffect\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"CarrierMoveEffect", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"CarrierMoveEffect");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Carrier\\CarrierMoveEffect\\moveEff_16.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		Vec3 vParentPos = pPrefab->Transform()->GetLocalPos();

		pShadPrefab->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(vParentPos);

		pPrefab->AddChild(pShadPrefab);
	}
	else if (L"Arbiter" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"ArbiterEffectPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitEffectScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"Arbiter\\ArbiterMoveEffect\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"ArbiterMoveEffect", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"ArbiterMoveEffect");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Arbiter\\ArbiterMoveEffect\\moveEff_16.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		Vec3 vParentPos = pPrefab->Transform()->GetLocalPos();

		pShadPrefab->Transform()->SetLocalScale(Vec3(76.f, 76.f, 76.f));
		pShadPrefab->Transform()->SetLocalPos(vParentPos);

		pPrefab->AddChild(pShadPrefab);
	}
	else if (L"Reaver" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"ReaverShadPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitShadScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"Reaver\\ReaverMoveShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"ReaverMoveShad", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"ReaverMoveShad");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Reaver\\ReaverMoveShad\\Shad_016.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pShadPrefab->Transform()->SetLocalScale(Vec3(84.f, 84.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pShadPrefab);
	}
	if (L"BtnUI" == _strName)
	{
		CTexture* pLBuildMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"LBuildBtnMouseOn", strButtonPath + L"LBuild\\LBuild_0.png");
		CTexture* pHBuildMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"HBuildBtnMouseOn", strButtonPath + L"HBuild\\HBuild_0.png");
		CTexture* pMiningMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"MiningBtnMouseOn", strButtonPath + L"Mining\\Mining_0.png");
		CTexture* pMoveMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMouseOn", strButtonPath + L"Move\\move_0.png");
		CTexture* pStopMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMouseOn", strButtonPath + L"Stop\\Stop_0.png");
		CTexture* pAttMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"AttBtnMouseOn", strButtonPath + L"Att\\att_0.png");

		CTexture* pNexusMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"NexusBtnMouseOn", strButtonPath + L"Nexus\\Nexus_0.png");
		CTexture* pPylonMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"PylonBtnMouseOn", strButtonPath + L"Pylon\\Pylon_0.png");
		CTexture* pAssimilatorMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"AssimilatorBtnMouseOn", strButtonPath + L"Assimilator\\Assimilator_0.png");
		CTexture* pForgeMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"ForgeBtnMouseOn", strButtonPath + L"Forge\\Forge_0.png");
		CTexture* pGatewayMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"GatewayBtnMouseOn", strButtonPath + L"Gateway\\Gateway_0.png");
		CTexture* pCyberNeticsCoreTex = CResMgr::GetInst()->Load<CTexture>(L"CyberneticsCoreBtnMouseOn", strButtonPath + L"Cybernetics Core\\Cybernetics Core_0.png");
		pCyberNeticsCoreTex = CResMgr::GetInst()->Load<CTexture>(L"CyberneticsCoreBtnMousePressed", strButtonPath + L"Cybernetics Core\\Cybernetics Core_1.png");
		pCyberNeticsCoreTex = CResMgr::GetInst()->Load<CTexture>(L"CyberneticsCoreBtnMouseOff", strButtonPath + L"Cybernetics Core\\Cybernetics Core_2.png");
		CTexture* pPhotonCannonTex = CResMgr::GetInst()->Load<CTexture>(L"PhotonCannonBtnMouseOn", strButtonPath + L"Photon Cannon\\Photon Cannon_0.png");
		pPhotonCannonTex = CResMgr::GetInst()->Load<CTexture>(L"PhotonCannonBtnMousePressed", strButtonPath + L"Photon Cannon\\Photon Cannon_1.png");
		pPhotonCannonTex = CResMgr::GetInst()->Load<CTexture>(L"PhotonCannonBtnMouseOff", strButtonPath + L"Photon Cannon\\Photon Cannon_2.png");
		CTexture* pShieldBatteryTex = CResMgr::GetInst()->Load<CTexture>(L"ShieldBatteryBtnMouseOn", strButtonPath + L"Shield Battery\\Shield Battery_0.png");
		pShieldBatteryTex = CResMgr::GetInst()->Load<CTexture>(L"ShieldBatteryBtnMousePressed", strButtonPath + L"Shield Battery\\Shield Battery_1.png");
		pShieldBatteryTex = CResMgr::GetInst()->Load<CTexture>(L"ShieldBatteryBtnMouseOff", strButtonPath + L"Shield Battery\\Shield Battery_2.png");

		CTexture* pCancelMouseOnTex = CResMgr::GetInst()->Load<CTexture>(L"CancelBtnMouseOn", strButtonPath + L"Cancel\\Cancel_0.png");

		CTexture* pLBuildMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"LBuildBtnMousePressed", strButtonPath + L"LBuild\\LBuild_1.png");
		CTexture* pHBuildMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"HBuildBtnMousePressed", strButtonPath + L"HBuild\\HBuild_1.png");
		CTexture* pMiningMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"MiningBtnMousePressed", strButtonPath + L"Mining\\Mining_1.png");
		CTexture* pMoveMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"MoveBtnMousePressed", strButtonPath + L"Move\\move_1.png");
		CTexture* pStopMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"StopBtnMousePressed", strButtonPath + L"Stop\\Stop_1.png");
		CTexture* pAttMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"AttBtnMousePressed", strButtonPath + L"Att\\att_1.png");

		CTexture* pNexusMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"NexusBtnMousePressed", strButtonPath + L"Nexus\\Nexus_1.png");
		CTexture* pPylonMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"PylonBtnMousePressed", strButtonPath + L"Pylon\\Pylon_1.png");
		CTexture* pAssimilatorMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"AssimilatorBtnMousePressed", strButtonPath + L"Assimilator\\Assimilator_1.png");
		CTexture* pForgeMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"ForgeBtnMousePressed", strButtonPath + L"Forge\\Forge_1.png");
		CTexture* pGatewayMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"GatewayBtnMousePressed", strButtonPath + L"Gateway\\Gateway_1.png");

		CTexture* pCancelMousePressedTex = CResMgr::GetInst()->Load<CTexture>(L"CancelBtnMousePressed", strButtonPath + L"Cancel\\Cancel_1.png");

		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalOn", strButtonPath + L"Arbiter Tribunal\\Arbiter Tribunal_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalPressed", strButtonPath + L"Arbiter Tribunal\\Arbiter Tribunal_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalOff", strButtonPath + L"Arbiter Tribunal\\Arbiter Tribunal_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StargateOn", strButtonPath + L"Stargate\\Stargate_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StargatePressed", strButtonPath + L"Stargate\\Stargate_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StargateOff", strButtonPath + L"Stargate\\Stargate_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityOn", strButtonPath + L"Robotics Facility\\Robotics Facility_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityPressed", strButtonPath + L"Robotics Facility\\Robotics Facility_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityOff", strButtonPath + L"Robotics Facility\\Robotics Facility_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunOn", strButtonPath + L"Citadel of Adun\\Citadel of Adun_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunPressed", strButtonPath + L"Citadel of Adun\\Citadel of Adun_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunOff", strButtonPath + L"Citadel of Adun\\Citadel of Adun_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesOn", strButtonPath + L"Templar Archives\\Templar Archives_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesPressed", strButtonPath + L"Templar Archives\\Templar Archives_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesOff", strButtonPath + L"Templar Archives\\Templar Archives_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayOn", strButtonPath + L"Robotics Support Bay\\Robotics Support Bay_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayPressed", strButtonPath + L"Robotics Support Bay\\Robotics Support Bay_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayOff", strButtonPath + L"Robotics Support Bay\\Robotics Support Bay_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryOn", strButtonPath + L"Observatory\\Observatory_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryPressed", strButtonPath + L"Observatory\\Observatory_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryOff", strButtonPath + L"Observatory\\Observatory_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconOn", strButtonPath + L"Fleet Beacon\\Fleet Beacon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconPressed", strButtonPath + L"Fleet Beacon\\Fleet Beacon_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconOff", strButtonPath + L"Fleet Beacon\\Fleet Beacon_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"HoldOn", strButtonPath + L"Hold\\Hold_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"HoldPressed", strButtonPath + L"Hold\\Hold_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"PatrolOn", strButtonPath + L"Patrol\\Patrol_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"PatrolPressed", strButtonPath + L"Patrol\\Patrol_1.png");

		//

		pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyOn", strButtonPath + L"Rally\\Rally_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"RallyPressed", strButtonPath + L"Rally\\Rally_1.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"ProbeOn", strButtonPath + L"Probe\\Probe_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ProbePressed", strButtonPath + L"Probe\\Probe_1.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"ZealotOn", strButtonPath + L"Zealot\\Zealot_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ZealotPressed", strButtonPath + L"Zealot\\Zealot_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"DragoonOn", strButtonPath + L"Dragoon\\Dragoon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"DragoonPressed", strButtonPath + L"Dragoon\\Dragoon_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"DragoonOff", strButtonPath + L"Dragoon\\Dragoon_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"HighTemplarOn", strButtonPath + L"HighTemplar\\HighTemplar_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"HighTemplarPressed", strButtonPath + L"HighTemplar\\HighTemplar_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"HighTemplarOff", strButtonPath + L"HighTemplar\\HighTemplar_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"DarkTemplarOn", strButtonPath + L"DarkTemplar\\DarkTemplar_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"DarkTemplarPressed", strButtonPath + L"DarkTemplar\\DarkTemplar_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"DarkTemplarOff", strButtonPath + L"DarkTemplar\\DarkTemplar_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"ShuttleOn", strButtonPath + L"Shuttle\\Shuttle_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ShuttlePressed", strButtonPath + L"Shuttle\\Shuttle_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObserverOn", strButtonPath + L"Observer\\Observer_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObserverPressed", strButtonPath + L"Observer\\Observer_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObserverOff", strButtonPath + L"Observer\\Observer_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ReaverOn", strButtonPath + L"Reaver\\Reaver_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ReaverPressed", strButtonPath + L"Reaver\\Reaver_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ReaverOff", strButtonPath + L"Reaver\\Reaver_1.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"CorsairOn", strButtonPath + L"Corsair\\Corsair_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"CorsairPressed", strButtonPath + L"Corsair\\Corsair_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ScoutOn", strButtonPath + L"Scout\\Scout_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ScoutPressed", strButtonPath + L"Scout\\Scout_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"CarrierOn", strButtonPath + L"Carrier\\Carrier_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"CarrierPressed", strButtonPath + L"Carrier\\Carrier_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"CarrierOff", strButtonPath + L"Carrier\\Carrier_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArbiterOn", strButtonPath + L"Arbiter\\Arbiter_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArbiterPressed", strButtonPath + L"Arbiter\\Arbiter_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArbiterOff", strButtonPath + L"Arbiter\\Arbiter_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonOn", strButtonPath + L"Dark Archon\\Dark Archon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonPressed", strButtonPath + L"Dark Archon\\Dark Archon_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonOff", strButtonPath + L"Dark Archon\\Dark Archon_2.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonOn", strButtonPath + L"Archon\\Archon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonPressed", strButtonPath + L"Archon\\Archon_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonOff", strButtonPath + L"Archon\\Archon_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"RecallOn", strButtonPath + L"Recall\\Recall_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"RecallPressed", strButtonPath + L"Recall\\Recall_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"RecallOff", strButtonPath + L"Recall\\Recall_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"StasisFieldOn", strButtonPath + L"StasisField\\StasisField0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StasisFieldOff", strButtonPath + L"StasisField\\StasisField1.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"StormOn", strButtonPath + L"Storm\\Storm_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StormPressed", strButtonPath + L"Storm\\Storm_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StormOff", strButtonPath + L"Storm\\Storm_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonCoalescenceOn", strButtonPath + L"Archon\\Archon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonCoalescencePressed", strButtonPath + L"Archon\\Archon_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ArchonCoalescenceOff", strButtonPath + L"Archon\\Archon_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonCoalescenceOn", strButtonPath + L"Dark Archon\\Dark Archon_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonCoalescencePressed", strButtonPath + L"Dark Archon\\Dark Archon_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Dark ArchonCoalescenceOff", strButtonPath + L"Dark Archon\\Dark Archon_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"IllusionOn", strButtonPath + L"illusion\\illusion0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"IllusionOff", strButtonPath + L"illusion\\illusion1.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"WapOn", strButtonPath + L"Wap\\Wap0.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"FeedBackOn", strButtonPath + L"FeedBack\\FeedBack0.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"MindControlOn", strButtonPath + L"MindControl\\MindControl_0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"MindControlPressed", strButtonPath + L"MindControl\\MindControl_1.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"MindControlOff", strButtonPath + L"MindControl\\MindControl_2.png");

		pTex = CResMgr::GetInst()->Load<CTexture>(L"ConfusionUpgradeOn", strButtonPath + L"ConfusionUpgrade\\ConfusionUpgrade0.png");
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ConfusionUpgradeOff", strButtonPath + L"ConfusionUpgrade\\ConfusionUpgrade1.png");


		for (UINT i = 0; i < 9; ++i)
		{
			CGameObject*  pButtonPrefab = new CGameObject;
			pButtonPrefab->AddComponent(new CMeshRender);
			pButtonPrefab->AddComponent(new CCollider);
			pButtonPrefab->AddComponent(new CButtonScript);
			pButtonPrefab->SetObjType(OBJ_TYPE::UI);
			CButtonScript* pButtonScript = (CButtonScript*)pButtonPrefab->Script()[0];

			Vec3 vPrefabScale = Vec3(pStopMouseOnTex->GetWidth(), pStopMouseOnTex->GetHeight(), 1.f);
			Vec3 vPrefabPos = pPrefab->Transform()->GetLocalPos();

			pButtonPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
			CMaterial* pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl");
			pButtonPrefab->MeshRender()->SetMaterial(pMtrl);

			pButtonPrefab->Transform()->SetLocalScale(vPrefabScale);
			if (0 == i)
			{
				pButtonPrefab->SetName(L"Btn_00");
			}
			else if (1 == i)
			{
				pButtonPrefab->SetName(L"Btn_01");
			}
			else if (2 == i)
			{
				pButtonPrefab->SetName(L"Btn_02");
			}
			else if (3 == i)
			{
				pButtonPrefab->SetName(L"Btn_03");
			}
			else if (4 == i)
			{
				pButtonPrefab->SetName(L"Btn_04");
			}
			else if (5 == i)
			{
				pButtonPrefab->SetName(L"Btn_05");
			}
			else if (6 == i)
			{
				pButtonPrefab->SetName(L"Btn_06");
			}
			else if (7 == i)
			{
				pButtonPrefab->SetName(L"Btn_07");
			}
			else if (8 == i)
			{
				pButtonPrefab->SetName(L"Btn_08");
			}
			pButtonScript->SetButtonIdx(i);

			pButtonPrefab->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pButtonPrefab->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

			pPrefab->AddChild(pButtonPrefab);
			pButtonPrefab->SetLayerIdx(pPrefab->GetLayerIdx());
		}
	}

	if (L"Dragoon" == _strName)
	{
		CGameObject* pDragoonBallPrefab = new CGameObject;
		pDragoonBallPrefab->SetName(L"DragoonBallPrefab");

		pDragoonBallPrefab->AddComponent(new CMeshRender);
		pDragoonBallPrefab->AddComponent(new CAnimator2D);
		pDragoonBallPrefab->AddComponent(new CArchonEffectScript);

		pDragoonBallPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pDragoonBallPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName;

		AnimationName = strBuildingPath + L"Effect\\Ball\\";
		pDragoonBallPrefab->Animator2D()->AddAnimation(AnimationName, L"DragoonBall", true);
		AnimationName = strBuildingPath + L"Effect\\BallEx\\";
		pDragoonBallPrefab->Animator2D()->AddAnimation(AnimationName, L"DragoonBallEx", true);
		pDragoonBallPrefab->Animator2D()->SetCurAnimName(L"DragoonBall");

		pDragoonBallPrefab->Transform()->SetLocalScale(Vec3(32.f, 32.f, 1.f));
		pDragoonBallPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pDragoonBallPrefab);
	}

	if (L"Arbiter" == _strName)
	{
		CGameObject* pArbiterBallPrefab = new CGameObject;
		pArbiterBallPrefab->SetName(L"ArbiterBallPrefab");

		pArbiterBallPrefab->AddComponent(new CMeshRender);
		pArbiterBallPrefab->AddComponent(new CAnimator2D);
		pArbiterBallPrefab->AddComponent(new CArchonEffectScript);

		pArbiterBallPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pArbiterBallPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName;

		AnimationName = strBuildingPath + L"Effect\\Ball\\";
		pArbiterBallPrefab->Animator2D()->AddAnimation(AnimationName, L"ArbiterBall", true);
		AnimationName = strBuildingPath + L"Effect\\BallEx\\";
		pArbiterBallPrefab->Animator2D()->AddAnimation(AnimationName, L"ArbiterBallEx", true);
		pArbiterBallPrefab->Animator2D()->SetCurAnimName(L"ArbiterBall");

		pArbiterBallPrefab->Transform()->SetLocalScale(Vec3(32.f, 32.f, 1.f));
		pArbiterBallPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pArbiterBallPrefab);
	}

	if (L"Scout" == _strName)
	{
		CGameObject* pScoutAirPrefab = new CGameObject;
		pScoutAirPrefab->SetName(L"ScoutAirPrefab");

		pScoutAirPrefab->AddComponent(new CMeshRender);
		pScoutAirPrefab->AddComponent(new CAnimator2D);
		pScoutAirPrefab->AddComponent(new CArchonEffectScript);

		pScoutAirPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pScoutAirPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName;

		AnimationName = strBuildingPath + L"Effect\\Scout_Air\\";
		pScoutAirPrefab->Animator2D()->AddAnimation(AnimationName, L"Scout_Air", true);
		AnimationName = strBuildingPath + L"Effect\\Scout_Ground\\";
		pScoutAirPrefab->Animator2D()->AddAnimation(AnimationName, L"Scout_Ground", true);
		pScoutAirPrefab->Animator2D()->SetCurAnimName(L"Scout_Air");

		pScoutAirPrefab->Transform()->SetLocalScale(Vec3(32.f, 32.f, 1.f));
		pScoutAirPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pScoutAirPrefab);
	}

	if (L"Corsair" == _strName)
	{
		CGameObject* pCorsairPrefab = new CGameObject;
		pCorsairPrefab->SetName(L"CorsairSplashPr	efab");

		pCorsairPrefab->AddComponent(new CMeshRender);
		pCorsairPrefab->AddComponent(new CAnimator2D);
		pCorsairPrefab->AddComponent(new CArchonEffectScript);

		pCorsairPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pCorsairPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName;

		AnimationName = strBuildingPath + L"Effect\\Corsair_Splash\\";
		pCorsairPrefab->Animator2D()->AddAnimation(AnimationName, L"Corsair_Splash", true);
		pCorsairPrefab->Animator2D()->SetCurAnimName(L"Corsair_Splash");

		pCorsairPrefab->Transform()->SetLocalScale(Vec3(64.f, 64.f, 1.f));
		pCorsairPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pCorsairPrefab);
	}

	if (L"Archon" == _strName)
	{
		CGameObject* pShockPrefab = new CGameObject;
		pShockPrefab->SetName(L"ArchonShockwavePrefab");

		pShockPrefab->AddComponent(new CMeshRender);
		pShockPrefab->AddComponent(new CAnimator2D);
		pShockPrefab->AddComponent(new CArchonEffectScript);

		pShockPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShockPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName;

		AnimationName = strBuildingPath + L"Effect\\Shockball\\";
		pShockPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonShockball", true);
		pShockPrefab->Animator2D()->SetCurAnimName(L"ArchonShockball");

		pShockPrefab->Transform()->SetLocalScale(Vec3(80.f, 80.f, 1.f));
		pShockPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pShockPrefab);

		CGameObject* pShockwavePrefab = new CGameObject;
		pShockwavePrefab->SetName(L"ArchonShockballPrefab");

		pShockwavePrefab->AddComponent(new CMeshRender);
		pShockwavePrefab->AddComponent(new CAnimator2D);
		pShockwavePrefab->AddComponent(new CArchonEffectScript);

		pShockwavePrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShockwavePrefab->MeshRender()->SetMaterial(pMtrl);

		AnimationName = strBuildingPath + L"Effect\\Shockwave\\";
		pShockwavePrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonShockwave", true);
		pShockwavePrefab->Animator2D()->SetCurAnimName(L"ArchonShockwave");

		pShockwavePrefab->Transform()->SetLocalScale(Vec3(192, 192, 1.f));
		pShockwavePrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pShockwavePrefab);
	}
	if (L"Archon" == _strName || L"DarkArchon" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		if (_strName == L"Archon")
			pShadPrefab->SetName(L"ArchonBodyEffectPrefab");
		else if (_strName == L"DarkArchon")
			pShadPrefab->SetName(L"DarkArchonBodyEffectPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CArchonEffectScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName;

		if (_strName == L"Archon")
		{
			AnimationName = strFolderPath + L"Archon\\ArchonBody\\";
			pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonBody", true);
			pShadPrefab->Animator2D()->SetCurAnimName(L"ArchonBody");

			CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Archon\\ArchonBody\\body_00.png");
			pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		}

		else if (_strName == L"DarkArchon")
		{
			AnimationName = strFolderPath + L"Dark Archon\\Dark ArchonBody\\";
			pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark ArchonBody", true);
			pShadPrefab->Animator2D()->SetCurAnimName(L"Dark ArchonBody");

			CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Dark Archon\\Dark ArchonBody\\body_00.png");
			pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		}

		pShadPrefab->Transform()->SetLocalScale(Vec3(120.f, 120.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pShadPrefab);
	}
	if (L"Archon" == _strName || L"DarkArchon" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		if (_strName == L"Archon")
			pShadPrefab->SetName(L"ArchonAuraEffectPrefab");
		else if (_strName == L"DarkArchon")
			pShadPrefab->SetName(L"DarkArchonAuraEffectPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CArchonEffectScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName;

		if (_strName == L"Archon")
		{
			AnimationName = strFolderPath + L"Archon\\ArchonAura\\";
			pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"ArchonAura", true);
			pShadPrefab->Animator2D()->SetCurAnimName(L"ArchonAura");

			CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Archon\\ArchonAura\\aura_00.png");
			pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (_strName == L"DarkArchon")
		{
			AnimationName = strFolderPath + L"Dark Archon\\Dark ArchonAura\\";
			pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"Dark ArchonAura", true);
			pShadPrefab->Animator2D()->SetCurAnimName(L"Dark ArchonAura");

			CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\Dark Archon\\Dark ArchonAura\\aura_00.png");
			pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		}

		pShadPrefab->Transform()->SetLocalScale(Vec3(120.f, 120.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pShadPrefab);
	}
	if (L"HighTemplar" == _strName)
	{
		CGameObject* pShadPrefab = new CGameObject;
		pShadPrefab->SetName(L"High TemplarShadPrefab");
		pShadPrefab->AddComponent(new CMeshRender);
		pShadPrefab->AddComponent(new CAnimator2D);
		pShadPrefab->AddComponent(new CUnitShadScript);

		pShadPrefab->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShadPrefab->MeshRender()->SetMaterial(pMtrl);

		wstring AnimationName = strFolderPath + L"High Templar\\High TemplarShad\\";
		pShadPrefab->Animator2D()->AddAnimation(AnimationName, L"High TemplarShad", true);
		pShadPrefab->Animator2D()->SetCurAnimName(L"High TemplarShad");

		CTexture* pTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Animation2D\\Protoss\\Unit\\High Templar\\High TemplarShad\\shad_16.png");
		pShadPrefab->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTexture);
		pShadPrefab->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
		pShadPrefab->Transform()->SetLocalPos(pPrefab->Transform()->GetLocalPos());

		pPrefab->AddChild(pShadPrefab);
	}

	if (L"Nexus" == _strName)
	{
		wstring ShadName = strBuildingShadPath + L"Nexus\\nexusShad0.png";
		CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(L"NexusShad", ShadName);

		ShadName = strBuildingShadPath + L"Arbiter Tribunal\\arbiterShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Arbiter TribunalShad", ShadName);

		ShadName = strBuildingShadPath + L"Assimilator\\assimShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"AssimilatorShad", ShadName);

		ShadName = strBuildingShadPath + L"Citadel of Adun\\adunShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Citadel of AdunShad", ShadName);

		ShadName = strBuildingShadPath + L"Cybernetics Core\\coreShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Cybernetics CoreShad", ShadName);

		ShadName = strBuildingShadPath + L"Fleet Beacon\\beaconShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Fleet BeaconShad", ShadName);

		ShadName = strBuildingShadPath + L"Forge\\forgeShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ForgeShad", ShadName);

		ShadName = strBuildingShadPath + L"Gateway\\gatewayShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"GatewayShad", ShadName);

		ShadName = strBuildingShadPath + L"Observatory\\observShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"ObservatoryShad", ShadName);

		ShadName = strBuildingShadPath + L"Photon Cannon\\photonShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Photon CannonShad", ShadName);

		ShadName = strBuildingShadPath + L"Pylon\\pylonShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"PylonShad", ShadName);

		ShadName = strBuildingShadPath + L"Robotics Facility\\robotShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics FacilityShad", ShadName);

		ShadName = strBuildingShadPath + L"Robotics Support Bay\\robotspShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Robotics Support BayShad", ShadName);

		ShadName = strBuildingShadPath + L"Shield Battery\\batteryShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Shield BatteryShad", ShadName);

		//ShadName = strBuildingShadPath + L"Shield Battery\\batteryShad0.png";
		//pTex = CResMgr::GetInst()->Load<CTexture>(L"Shield BatteryShad", ShadName);

		ShadName = strBuildingShadPath + L"Stargate\\stgateShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"StargateShad", ShadName);

		ShadName = strBuildingShadPath + L"Templar Archives\\templarShad0.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"Templar ArchivesShad", ShadName);

		ShadName = L"Texture\\Texture\\Protoss\\Building\\Pylon\\Pylon_1.png";
		pTex = CResMgr::GetInst()->Load<CTexture>(L"PylonRadius", ShadName);

		// 생산창

		//ShadName = L"Texture\\Texture\\Protoss\\UI\\Produce\\Frame\\frame_0.png";
		//pTex = CResMgr::GetInst()->Load<CTexture>(L"ProduceFrame", ShadName);

		//ShadName = L"Texture\\Texture\\Protoss\\UI\\Produce\\Icon\\Icon_0.png";
		//pTex = CResMgr::GetInst()->Load<CTexture>(L"ProbeIcon", ShadName);

		//ShadName = L"Texture\\Texture\\Protoss\\UI\\Produce\\Bar\\bar_0.png";
		//pTex = CResMgr::GetInst()->Load<CTexture>(L"ProduceBar0", ShadName);

		//ShadName = L"Texture\\Texture\\Protoss\\UI\\Produce\\Bar\\bar_1.png";
		//pTex = CResMgr::GetInst()->Load<CTexture>(L"ProduceBar1", ShadName);
	}
}

void CTestSceneMaker::InitSound()
{
	CSound* pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotAtt", L"Sound\\ZealotAtt.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterStasisField", L"Sound\\ArbiterStasisField.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterRecall", L"Sound\\ArbiterRecall.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonAtt", L"Sound\\DragoonBall.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterAtt", L"Sound\\DragoonBall.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairAtt", L"Sound\\CorsairAtt.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonAtt", L"Sound\\ArchonAtt.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Button", L"Sound\\Button.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarDie", L"Sound\\DarkTemplarDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotDie", L"Sound\\ZealotDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonDie", L"Sound\\ArchonDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarDie", L"Sound\\HighTemplarDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonDie", L"Sound\\DragoonDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterDie", L"Sound\\ArbiterDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairDie", L"Sound\\CorsairDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverDie", L"Sound\\ReaverDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutDie", L"Sound\\ScoutDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ObserverDie", L"Sound\\ObserverDie.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierDie", L"Sound\\CarrierDie.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeBirth", L"Sound\\ProbeBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotBirth", L"Sound\\ZealotBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonBirth", L"Sound\\DragoonBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarBirth", L"Sound\\HighTemplarBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarBirth", L"Sound\\DarkTemplarBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ObserverBirth", L"Sound\\ObserverBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleBirth", L"Sound\\ShuttleBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverBirth", L"Sound\\ReaverBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairBirth", L"Sound\\CorsairBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierBirth", L"Sound\\CarrierBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutBirth", L"Sound\\ScoutBirth.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterBirth", L"Sound\\ArbiterBirth.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript00", L"Sound\\ProbeScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript01", L"Sound\\ProbeScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript02", L"Sound\\ProbeScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript03", L"Sound\\ProbeScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript04", L"Sound\\ProbeScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript05", L"Sound\\ProbeScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript06", L"Sound\\ProbeScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ProbeScript07", L"Sound\\ProbeScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript00", L"Sound\\ZealotScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript01", L"Sound\\ZealotScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript02", L"Sound\\ZealotScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript03", L"Sound\\ZealotScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript04", L"Sound\\ZealotScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript05", L"Sound\\ZealotScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript06", L"Sound\\ZealotScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ZealotScript07", L"Sound\\ZealotScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript00", L"Sound\\DragoonScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript01", L"Sound\\DragoonScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript02", L"Sound\\DragoonScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript03", L"Sound\\DragoonScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript04", L"Sound\\DragoonScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript05", L"Sound\\DragoonScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript06", L"Sound\\DragoonScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DragoonScript07", L"Sound\\DragoonScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript00", L"Sound\\HighTemplarScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript01", L"Sound\\HighTemplarScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript02", L"Sound\\HighTemplarScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript03", L"Sound\\HighTemplarScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript04", L"Sound\\HighTemplarScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript05", L"Sound\\HighTemplarScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript06", L"Sound\\HighTemplarScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"HighTemplarScript07", L"Sound\\HighTemplarScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript00", L"Sound\\DarkTemplarScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript01", L"Sound\\DarkTemplarScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript02", L"Sound\\DarkTemplarScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript03", L"Sound\\DarkTemplarScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript04", L"Sound\\DarkTemplarScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript05", L"Sound\\DarkTemplarScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript06", L"Sound\\DarkTemplarScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkTemplarScript07", L"Sound\\DarkTemplarScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript00", L"Sound\\DarkArchonScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript01", L"Sound\\DarkArchonScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript02", L"Sound\\DarkArchonScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript03", L"Sound\\DarkArchonScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript04", L"Sound\\DarkArchonScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript05", L"Sound\\DarkArchonScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript06", L"Sound\\DarkArchonScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"DarkArchonScript07", L"Sound\\DarkArchonScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript00", L"Sound\\ArchonScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript01", L"Sound\\ArchonScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript02", L"Sound\\ArchonScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript03", L"Sound\\ArchonScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript04", L"Sound\\ArchonScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript05", L"Sound\\ArchonScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript06", L"Sound\\ArchonScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArchonScript07", L"Sound\\ArchonScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript00", L"Sound\\ShuttleScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript01", L"Sound\\ShuttleScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript02", L"Sound\\ShuttleScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript03", L"Sound\\ShuttleScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript04", L"Sound\\ShuttleScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript05", L"Sound\\ShuttleScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript06", L"Sound\\ShuttleScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ShuttleScript07", L"Sound\\ShuttleScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript00", L"Sound\\ReaverScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript01", L"Sound\\ReaverScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript02", L"Sound\\ReaverScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript03", L"Sound\\ReaverScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript04", L"Sound\\ReaverScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript05", L"Sound\\ReaverScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript06", L"Sound\\ReaverScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ReaverScript07", L"Sound\\ReaverScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ObserverScript00", L"Sound\\ObserverScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ObserverScript01", L"Sound\\ObserverScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ObserverScript02", L"Sound\\ObserverScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ObserverScript03", L"Sound\\ObserverScript03.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript00", L"Sound\\CorsairScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript01", L"Sound\\CorsairScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript02", L"Sound\\CorsairScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript03", L"Sound\\CorsairScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript04", L"Sound\\CorsairScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript05", L"Sound\\CorsairScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript06", L"Sound\\CorsairScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CorsairScript07", L"Sound\\CorsairScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript00", L"Sound\\ScoutScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript01", L"Sound\\ScoutScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript02", L"Sound\\ScoutScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript03", L"Sound\\ScoutScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript04", L"Sound\\ScoutScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript05", L"Sound\\ScoutScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript06", L"Sound\\ScoutScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ScoutScript07", L"Sound\\ScoutScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript00", L"Sound\\CarrierScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript01", L"Sound\\CarrierScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript02", L"Sound\\CarrierScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript03", L"Sound\\CarrierScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript04", L"Sound\\CarrierScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript05", L"Sound\\CarrierScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript06", L"Sound\\CarrierScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"CarrierScript07", L"Sound\\CarrierScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript00", L"Sound\\ArbiterScript00.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript01", L"Sound\\ArbiterScript01.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript02", L"Sound\\ArbiterScript02.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript03", L"Sound\\ArbiterScript03.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript04", L"Sound\\ArbiterScript04.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript05", L"Sound\\ArbiterScript05.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript06", L"Sound\\ArbiterScript06.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"ArbiterScript07", L"Sound\\ArbiterScript07.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"Nexus", L"Sound\\Nexus.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Pylon", L"Sound\\Pylon.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Assimilator", L"Sound\\Assimilator.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Forge", L"Sound\\Forge.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Gateway", L"Sound\\Gateway.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Photon Cannon", L"Sound\\Nexus.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Cybernetics Core", L"Sound\\Cybernetics Core.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Shield Battery", L"Sound\\Shield Battery.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Robotics Facility", L"Sound\\Robotics Facility.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Stargate", L"Sound\\Gateway.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Citadel of Adun", L"Sound\\Citadel of Adun.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Observatory", L"Sound\\Observatory.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Fleet Beacon", L"Sound\\Fleet Beacon.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Arbiter Tribunal", L"Sound\\Arbiter Tribunal.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Robotics Support Bay", L"Sound\\Robotics Support Bay.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"Templar Archives", L"Sound\\Templar Archives.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"Victory", L"Sound\\Victory.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"BuildStart", L"Sound\\BuildStart.wav");
	pSound = CResMgr::GetInst()->Load<CSound>(L"BuildEnd", L"Sound\\BuildEnd.wav");

	pSound = CResMgr::GetInst()->Load<CSound>(L"StructureExplosion", L"Sound\\StructureExplosion.wav");
	
}



//// 선택
//CGameObject* pSelectObject = new CGameObject;
//pSelectObject->SetName(L"Selection");

//pSelectObject->AddComponent(new CMeshRender);
//pSelectObject->AddComponent(new CCollider);
//pSelectObject->AddComponent(new CSeclectScript);

//pSelectObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
//pSelectObject->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

//pSelectObject->Transform()->SetLocalScale(Vec3(64.f, 64.f, 1.f));
//pSelectObject->Transform()->SetLocalPos(Vec3(vMousePos.x, vMousePos.y, vMousePos.z));

//pSelectObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
//pSelectObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

//pCurScene->AddGameObject(L"Selection", pSelectObject);
