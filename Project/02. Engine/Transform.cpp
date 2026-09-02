#include "Transform.h"

#include "KeyMgr.h"

#include "Device.h"
#include "ConstBuffer.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"

#include "Camera.h"

tTransformMatrix g_tTransMatrix;

const Vec3 g_vDir[(UINT)DIR_TYPE::END] = { Vec3(1.f,0.f,0.f), Vec3(0.f,1.f,0.f), Vec3(0.f,0.f,1.f) };

CTransform::CTransform()
	: m_vLocalDir{ Vec3::Right,Vec3::Up,Vec3::Front}
	, m_vWorldDir{ Vec3::Right,Vec3::Up,Vec3::Front}
	, m_bUseParent(true)
{
	SetComponentType(COMPONENT_TYPE::TRANSFORM);
}


CTransform::~CTransform()
{
}

int CTransform::update()
{

	return 0;
}

int CTransform::finalupdate()
{
	// 월드 행렬 계산하기
	// 크기 행렬
	Matrix matScale = XMMatrixScaling(m_vLocalScale.x, m_vLocalScale.y, m_vLocalScale.z);

	// 회전(자전) 행렬
	Matrix matRotate = XMMatrixRotationX(m_vLocalRotate.x);
	matRotate *= XMMatrixRotationY(m_vLocalRotate.y);
	matRotate *= XMMatrixRotationZ(m_vLocalRotate.z);

	for (UINT i = 0; i < (UINT)DIR_TYPE::END; ++i)
	{
		m_vLocalDir[i] = XMVector3TransformNormal(g_vDir[i], matRotate);
		m_vLocalDir[i].Normalize();
		m_vWorldDir[i] = m_vLocalDir[i];
	}

	// 이동 행렬
	Matrix matTrans = XMMatrixTranslation(m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	// 월드행렬
	m_matWorld = matScale * matRotate * matTrans;


	if (nullptr != ParentObject())
	{
		m_vParentScale = m_vLocalScale;
		m_vParentPos = m_vLocalPos;

		// 스타 할때는 이거 주석
		//if(m_bUseParent)
		//	m_matWorld *= ParentObject()->Transform()->GetWolrdMat();
		m_matEachWorld = m_matWorld / ParentObject()->Transform()->GetWolrdMat();
		for (UINT i = 0; i < (UINT)DIR_TYPE::END; ++i)
		{
			m_vWorldDir[i] = XMVector3TransformNormal(g_vDir[i], m_matWorld);
			m_vWorldDir[i].Normalize();
		}
	}



	return 0;
}

void CTransform::UpdateData()
{

	g_tTransMatrix.matWorld = m_matWorld;
	g_tTransMatrix.matWV = g_tTransMatrix.matWorld * g_tTransMatrix.matView;
	g_tTransMatrix.matWVP = g_tTransMatrix.matWV * g_tTransMatrix.matProj;
	g_tTransMatrix.matInvWorld = XMMatrixInverse(nullptr, m_matWorld);


	static CConstBuffer* pBuffer = CDevice::GetInst()->FindCBuffer(L"Transform");

	pBuffer->UpdateData(&g_tTransMatrix, sizeof(tTransformMatrix));
	pBuffer->UpdateRegister(SHADER_TYPE::ST_VERTEX | SHADER_TYPE::ST_PIXEL);
}


Vec3 CTransform::GetWolrdPos()
{
	return XMVector3TransformCoord(Vec3::Zero, m_matWorld);
}

void CTransform::Save(FILE * _pFile)
{
	CComponent::Save(_pFile);

	fwrite(&m_vLocalPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vLocalScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vLocalRotate, sizeof(Vec3), 1, _pFile);
}

void CTransform::Load(FILE * _pFile)
{
	CComponent::Load(_pFile);

	fread(&m_vLocalPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vLocalScale, sizeof(Vec3), 1, _pFile);
	fread(&m_vLocalRotate, sizeof(Vec3), 1, _pFile);
}
