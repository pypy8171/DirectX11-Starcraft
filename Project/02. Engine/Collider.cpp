#include "Collider.h"

#include "Transform.h"

#include "ResMgr.h"
#include "ConstBuffer.h"
#include "Device.h"

#include "Script.h"
#include "CollisionMgr.h"

DWORD CCollider::g_iID = 0;


CCollider::CCollider()
	: m_dwID(g_iID++)
	, m_bCollide(false)
	, m_fRadius(1.f)
	, m_fFinalRadius(0.f)
	, m_pCloneMtrl(nullptr)
	, m_pMtrl(nullptr)
	, m_pMesh(nullptr)
{
	SetComponentType(COMPONENT_TYPE::COLLIDER);
	m_pMtrl = CResMgr::GetInst()->Load<CMaterial>(L"ColliderMtrl");

	m_mapColliderType.insert(make_pair(L"COLLIDER_2D_BOX", (UINT)COLLIDER_TYPE::COLLIDER_2D_BOX));
	m_mapColliderType.insert(make_pair(L"COLLIDER_2D_CIRCLE", (UINT)COLLIDER_TYPE::COLLIDER_2D_CIRCLE));
	m_mapColliderType.insert(make_pair(L"COLLIDER_3D_CUBE", (UINT)COLLIDER_TYPE::COLLIDER_2D_BOX));
	m_mapColliderType.insert(make_pair(L"COLLIDER_3D_SPHERE", (UINT)COLLIDER_TYPE::COLLIDER_2D_CIRCLE));

	//m_arrColliderType[0] = L"COLLIDER_2D_BOX";
	//m_arrColliderType[1] = L"COLLIDER_2D_CIRCLE";
	//m_arrColliderType[2] = L"COLLIDER_2D_CUBE";
	//m_arrColliderType[3] = L"COLLIDER_2D_SPHERE";

}

CCollider::CCollider(const CCollider & _other)
	//: m_pMesh(_other.m_pMesh)
{
	*this = _other;
	m_dwID = g_iID++;
}

CCollider::~CCollider()
{
}

int CCollider::update()
{
	CCollisionMgr::GetInst()->Register(this, Object()->GetLayerIdx());
	return 0;
}


void CCollider::CalColliderMat()
{
	Matrix matScale, matTrans;

	// 이동 행렬
	matTrans = XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	switch (m_eType)
	{
	case COLLIDER_TYPE::COLLIDER_2D_BOX:
	case COLLIDER_TYPE::COLLIDER_3D_CUBE:
		matScale = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
		// 월드행렬
		m_matCol = matScale * matTrans;
		m_matCol *= Transform()->GetWolrdMat();

		break;
	case COLLIDER_TYPE::COLLIDER_2D_CIRCLE:
	case COLLIDER_TYPE::COLLIDER_3D_SPHERE:
	{
		{
			matScale = XMMatrixScaling(m_fRadius, m_fRadius, m_fRadius);
			m_matCol = matScale * matTrans;

			Vec3 vScale, vPos;
			Quaternion qRot;
			Matrix matObjWorld = Transform()->GetWolrdMat();
			matObjWorld.Decompose(vScale, qRot, vPos);

			float fMaxScale = max(vScale.x, vScale.y);

			if (COLLIDER_TYPE::COLLIDER_3D_SPHERE == m_eType)
			{
				fMaxScale = max(fMaxScale, vScale.z);
			}

			Matrix matObjTrans = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
			Matrix matObjScale = XMMatrixScaling(fMaxScale, fMaxScale, fMaxScale);

			m_matCol *= matObjScale * matObjTrans;

			m_fFinalRadius = (float)(m_fRadius * fMaxScale * 0.5); // 0.5 : 최종 지름 -> 최종 반지름 // 이거 박스랑 통일시켜야함.
		}
	}
		break;
	default:
		break;
	}
}


int CCollider::finalupdate()
{
	CalColliderMat();

	// CollisionMgr 에 등록
	CCollisionMgr::GetInst()->AddCollider(Object()->GetLayerIdx(), this);

	return 0;
}

void CCollider::render()
{
	if (nullptr == m_pMesh || m_pMtrl == nullptr)
		return;

	// Collider 행렬정보를 버퍼에 업데이트 시켜야 한다.
	g_tTransMatrix.matWorld = m_matCol;
	g_tTransMatrix.matWV = g_tTransMatrix.matWorld * g_tTransMatrix.matView;
	g_tTransMatrix.matWVP = g_tTransMatrix.matWV * g_tTransMatrix.matProj;

	static CConstBuffer* pBuffer = CDevice::GetInst()->FindCBuffer(L"Transform");

	pBuffer->UpdateData(&g_tTransMatrix, sizeof(tTransformMatrix));
	pBuffer->UpdateRegister(SHADER_TYPE::ST_VERTEX);

	// Material 정보를 업데이트 시킨다.
	CMaterial* pMtrl = nullptr;

	if (m_pCloneMtrl)
		pMtrl = m_pCloneMtrl;
	else
		pMtrl = m_pMtrl;

	pMtrl->UpdateData();

	m_pMesh->SetShader(pMtrl->GetShader());
	m_pMesh->render();
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	if (!m_pCloneMtrl)
		m_pCloneMtrl = m_pMtrl->Clone();
	
	for (UINT i = 0; i < Script().size(); ++i)
	{
		if(m_pCloneMtrl)
			Script()[i]->SetMaterial(m_pCloneMtrl);
		else
			Script()[i]->SetMaterial(m_pMtrl);

		Script()[i]->OnCollisionEnter(_pOther);
	}
}

void CCollider::OnCollision(CCollider* _pOther)
{
	vector<CScript*>& vecScript = Object()->Script();
	for (auto pScript : vecScript)
	{
		pScript->OnCollision(_pOther);
	}
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	m_pCloneMtrl = nullptr;
	for (UINT i = 0; i < Script().size(); ++i)
	{
		Script()[i]->SetMaterial(m_pMtrl);
		Script()[i]->OnCollisionExit(_pOther);
	}
}

void CCollider::SetColliderType(COLLIDER_TYPE _eType)
{
	m_eType = _eType;

	switch (m_eType)
	{
	case COLLIDER_TYPE::COLLIDER_2D_BOX:
		m_pMesh = CResMgr::GetInst()->Load<CMesh>(L"ColliderRectMesh");
		break;
	case COLLIDER_TYPE::COLLIDER_2D_CIRCLE:
		m_pMesh = CResMgr::GetInst()->Load<CMesh>(L"ColliderCircleMesh");
		break;
	case COLLIDER_TYPE::COLLIDER_3D_CUBE:
		m_pMesh = CResMgr::GetInst()->Load<CMesh>(L"ColliderCubeMesh");
		break;
	case COLLIDER_TYPE::COLLIDER_3D_SPHERE:
		m_pMesh = CResMgr::GetInst()->Load<CMesh>(L"ColliderSphereMesh");
		break;
	}
}


void CCollider::Save(FILE * _pFile)
{
	CComponent::Save(_pFile);

	fwrite(&m_eType, sizeof(UINT), 1, _pFile);
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vRot, sizeof(Vec3), 1, _pFile);

	bool bMtrl = false;
	if (nullptr != m_pMtrl)
		bMtrl = true;

	fwrite(&bMtrl, sizeof(bool), 1, _pFile);

	if (bMtrl)
		SaveWString(m_pMtrl->GetName(), _pFile);

	fwrite(&m_fRadius, sizeof(float), 1, _pFile);

}

void CCollider::Load(FILE * _pFile)
{
	CComponent::Load(_pFile);

	fread(&m_eType, sizeof(UINT), 1, _pFile); 		// 충돌체 타입
	SetColliderType(m_eType);

	fread(&m_vOffsetPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _pFile);
	fread(&m_vRot, sizeof(Vec3), 1, _pFile);

	bool bMtrl = false;
	fread(&bMtrl, sizeof(bool), 1, _pFile);

	if (bMtrl)
	{
		m_pMtrl = CResMgr::GetInst()->Load<CMaterial>(LoadWString(_pFile));
	}

	fread(&m_fRadius, sizeof(float), 1, _pFile);
}