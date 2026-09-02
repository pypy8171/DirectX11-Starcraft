#include "PlayerScript.h"
#include "BulletScript.h"
#include "MonsterScript.h"
#include "MarkScript.h"
#include "MuzzleScript.h"
#include "Script.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "SceneMgr.h"

#include "Transform.h"
#include "MeshRender.h"
#include "Camera.h"
#include "Collider.h"

#include "Scene.h"

#include "Mesh.h"
#include "Material.h"

#include "Animator2D.h"
#include "Animation2D.h"

CPlayerScript::CPlayerScript()
	: m_pMonster(NULL)
	, m_pMark(NULL)
	, m_pMuzzle(NULL)
	, m_bTarget(false)
	, m_bCollide(0)
	, m_eBulletType(BULLET_TYPE::NORMAL)
	, m_iCurTex(0)
	, m_pAnimation2D(nullptr)
{
}


CPlayerScript::~CPlayerScript()
{
}

int CPlayerScript::update()
{

	MoveDir();
	Key();


	if (nullptr == Object()->Animator2D())
		return 0;
	else
	{
		map<wstring, CAnimation2D*> maplist = Object()->Animator2D()->GetAnimationMap();
		
		map<wstring, CAnimation2D*>::iterator iter = maplist.find(Object()->Animator2D()->GetCurAnimName());
		if (iter == maplist.end())
		{
			return 0;
		}

		m_pAnimation2D = iter->second;
		Animation();
	}

	return 0;
}

#include <iostream>
using namespace std;

void CPlayerScript::MoveDir()
{
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vAngle = Transform()->GetLocalAngle();


	CScene* pCurScene = (CScene*)CSceneMgr::GetInst()->GetCurrentScene();

	if (KEYHOLD(KEY_TYPE::KEY_LEFT)/*|| KEYHOLD(KEY_TYPE::KEY_A)*/)
	{
		vPos.x -= 100.f*DT;
	}
	if (KEYHOLD(KEY_TYPE::KEY_RIGHT)/*|| KEYHOLD(KEY_TYPE::KEY_D)*/)
	{
		vPos.x += 100.f * DT;
	}
	if (KEYHOLD(KEY_TYPE::KEY_UP) /*|| KEYHOLD(KEY_TYPE::KEY_W)*/)
	{
		vPos.y += 100.f*DT;
	}
	if (KEYHOLD(KEY_TYPE::KEY_DOWN)/*||KEYHOLD(KEY_TYPE::KEY_S)*/)
	{
		vPos.y -= 100.f*DT;
	}
	//if (KEYHOLD(KEY_TYPE::KEY_W))
	//{
	//	vPos.z += 100.f*DT;
	//}
	//if (KEYHOLD(KEY_TYPE::KEY_S))
	//{
	//	vPos.z -= 100.f*DT;
	//}

	//if (KEYHOLD(KEY_TYPE::KEY_A))
	//{
	//	vAngle.y += XM_PI *DT;
	//}
	//if (KEYHOLD(KEY_TYPE::KEY_D))
	//{
	//	vAngle.y -= XM_PI *DT;
	//}

	//if (KEYHOLD(KEY_TYPE::KEY_Q))
	//{
	//	vAngle.x += XM_PI *DT;
	//}
	//if (KEYHOLD(KEY_TYPE::KEY_E))
	//{
	//	vAngle.x -= XM_PI *DT;
	//}

	if (KEYHOLD(KEY_TYPE::KEY_Z))
	{
		vAngle.z += XM_PI * DT;
	}
	if (KEYHOLD(KEY_TYPE::KEY_X))
	{
		vAngle.z -= XM_PI * DT;
	}

	//if (vAngle.z > 360.f)
	//	vAngle.z = 0.f;
	//else if (vAngle.z < -360.f)
	//	vAngle.z = 0.f;

	Transform()->SetLocalPos(vPos);
	Transform()->SetLocalRotate(vAngle);

}

void CPlayerScript::Key()
{
	CWell512 random;
	int iColor = random.GetValue(0, 3);

	CScene* pCurScene = (CScene*)CSceneMgr::GetInst()->GetCurrentScene();

	Vec3 vMarkPos = ((CMarkScript*)m_pMark)->GetMarkPos();
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vAngle = Transform()->GetLocalAngle();

	Vec3 vDir = vMarkPos - vPos;

	//CScript* pBulletScript = new CBulletScript;
	//((CBulletScript*)pBulletScript)->SetGuided(((CMarkScript*)m_pMark)->GetMarkOn());

	if (KEYTAB(KEY_TYPE::KEY_F1))
	{
		m_eBulletType = BULLET_TYPE::NORMAL;

	}
	else if (KEYTAB(KEY_TYPE::KEY_F2))
	{
		m_eBulletType = BULLET_TYPE::GUIDED;
	}

	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		Vec3 vMuzzlePos = ((CMuzzleScript*)m_pMuzzle)->GetMuzzlePos();

		vMuzzlePos.x = ((CMuzzleScript*)m_pMuzzle)->GetMuzzlePos().x + 25 * cos(vAngle.z);
		vMuzzlePos.y = ((CMuzzleScript*)m_pMuzzle)->GetMuzzlePos().y + 25 * sin(vAngle.z);

		Instantiate(m_pBullet, L"PlayerBullet", vMuzzlePos, vAngle); // 불렛 타입
		//CGameObject* pBulletObject = new CGameObject;
		//pBulletObject->AddComponent<CMeshRender>(new CMeshRender);

		//if (iColor%3 == 0)
		//{
		//	pBulletObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"Bluehexahedron"));
		//}
		//else if (iColor%3 == 1)
		//{
		//	pBulletObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"Redhexahedron"));
		//}
		//else if (iColor%3 == 2)
		//{
		//	pBulletObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"Greenhexahedron"));
		//}

		//pBulletObject->MeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));

		//pBulletObject->Transform()->SetLocalScale(Vec3(10.f, 10.f, 10.f));
		//pBulletObject->Transform()->SetLocalPos(vMuzzlePos);

		//((CBulletScript*)pBulletScript)->SetSrcPos(vMuzzlePos);

		//if (true == ((CMarkScript*)m_pMark)->GetMarkOn())
		//{
		//	((CBulletScript*)pBulletScript)->SetDestPos(((CMarkScript*)m_pMark)->GetMarkPos());
		//	m_bTarget = true;
		//}
		//else
		//{
 	//		((CBulletScript*)pBulletScript)->SetDestPos(((CMonsterScript*)m_pMonster)->GetMonsterPos());
		//	m_bTarget = false;
		//}
		//((CBulletScript*)pBulletScript)->SetBulletType(m_eBulletType);
		//((CBulletScript*)pBulletScript)->SetPlayerAngle(vAngle);
		//((CBulletScript*)pBulletScript)->SetBullet(pBulletObject);
		//pBulletObject->AddComponent<CScript>(pBulletScript);

		//pCurScene->AddGameObject(L"Default", pBulletObject);
	}

	if (((CMarkScript*)m_pMark)->GetMarkOn())
	{
		Vec3 vDirPos = ((CMarkScript*)m_pMark)->GetMarkPos() - vPos;
		vDirPos.Normalize();

		Vec3 vDir = Vec3(1.f, 0.f, 0.f);
		vDir.Normalize(); 

		Vec3 fAngle = (Vec3)XMVector3AngleBetweenNormals(vDirPos, vDir);
		Vec3 vTemp = Vec3(0.f, 0.f, 0.f);
		//if(((CMarkScript*)m_pMark)->GetMarkPos().y>vPos.y)
		//	vTemp.z = fAngle.z;
		//else if (((CMarkScript*)m_pMark)->GetMarkPos().y<vPos.y)
		//	vTemp.z = 3.14f + (3.14f - fAngle.z);

		//if (vAngle.z < vTemp.z /*|| (vTemp.z - vAngle.z) > 3.14*/)
		//	vAngle.z += 1* DT;
		//else if(vAngle.z > vTemp.z /*|| (vTemp.z - vAngle.z) < -3.14*/)
		//	vAngle.z -= 1 * DT;

		//if (vAngle.z*180/3.141592 > 360.f)
		//	vAngle.z = 0.f;
		//else if (vAngle.z * 180 / 3.141592 < 0.f)
		//	vAngle.z = 360.f;

		vPos.x += DT * 100.f*vDirPos.x;
		vPos.y += DT * 100.f*vDirPos.y;
	}

	Transform()->SetLocalRotate(vAngle);

	if (sqrt(vDir.x*vDir.x + vDir.y*vDir.y) < 1)
		return;

	Transform()->SetLocalPos(vPos);
}



void CPlayerScript::Animation()
{
	// 오브젝트가 유닛일때랑 아닐때랑 구분 -> 유닛일때는 방향에 맞춰서 돌아가도록 // 안돌아가는 유닛도 구분 ( 드라군 같은 애들 )
	// if(
	// wstring adsf = Object()->GetName(); // 레이어 이름인지 

	// 움직임에 따른 이미지(애니메이션 출력)
	Vec3 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vMarkPos = ((CMarkScript*)m_pMark)->GetMarkPos();
	Vec3 vUp = Vec3(0.f, 1.f, 0.f);

	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vRot = Transform()->GetLocalAngle();
	Vec3 vDir = vMarkPos - vPos;

	if (sqrt(vDir.x*vDir.x + vDir.y*vDir.y) < 1)
		return;

	vDir.Normalize();

	Vec3 vAngle = (Vec3)XMVector3AngleBetweenNormals(vUp, vDir); // 사잇각

	float fAngle = (float)(vAngle.z *180.f / 3.14);

	if (fAngle > 180.f)
	{
		fAngle -= 180.f;
	}

	//int a = Object()->Animator2D()->GetFrmCount();

	int iTex = (int)(fAngle / (180.f / 17)); // 17인 것은 텍스쳐 숫자를 받아가게 해야 할듯. Object()->Animator2D()->GetFrmCount()/2;

	if (m_iCurTex == iTex)
		return;

	m_iCurTex = iTex;

	//if ((vUp.x*vDir.y - vDir.x*vUp.y < 0))
	//{
	//	vRot.y = 0.f;
	//	Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), m_pAnimation2D->GetRepeat()); // Battlecr 자리에 문자열 들어가야함
	//	//Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, iTex);
	//}
	//else
	//{
	//	vRot.y = XM_PI;
	//	//vRot.z = XM_PI;// (180 - fAngle)*(3.14 / 180);
	//	iTex = (int)((/*180.f +*/(180.f-fAngle)) / (180.f / 17));
	//	//Object()->Animator2D()->PlayNumAnimation(Object()->Animator2D()->GetCurAnimName(), false, 16-iTex); // 텍스쳐는 1인거 쓰고 180도 회전
	//}
	Object()->Animator2D()->PlayAnim(Object()->Animator2D()->GetCurAnimName(), m_pAnimation2D->GetRepeat());

	Transform()->SetLocalRotate(vRot);
}

void CPlayerScript::awake()
{
	m_pBullet = CResMgr::GetInst()->Load<CPrefab>(L"Bullet");
}

void CPlayerScript::OnCollisionEnter(const CCollider * _pOther)
{
	m_bCollide = 1;
	for (UINT i = 0; i < Script().size(); ++i)
	{
		CMaterial* pMtrl = Script()[i]->GetMaterial();
		if(pMtrl != nullptr)
			pMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}
}

void CPlayerScript::OnCollision(const CCollider * _pOther)
{
}

void CPlayerScript::OnCollisionExit(const CCollider * _pOther)
{
	m_bCollide = 0;
	for (UINT i = 0; i < Script().size(); ++i)
	{
		CMaterial* pMtrl = Script()[i]->GetMaterial();
		if (pMtrl != nullptr)
			pMtrl->SetData(SHADER_PARAM::INT_0, &m_bCollide);
	}
}