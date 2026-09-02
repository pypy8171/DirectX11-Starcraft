#include "MeshRender.h"

#include "Device.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Collider.h"
#include "Animator2D.h"
#include "Camera.h"
#include "Grid.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Core.h"

#include "Scene.h"

#include "Texture.h"

#include "ResMgr.h"

CMeshRender::CMeshRender()
	: m_pMesh(nullptr)
	, m_pMaterial(nullptr)
	, m_pTex(nullptr)
	, m_bClone(false)
	, m_bRender(true)
	, m_bColRender(false)
{
	SetComponentType(COMPONENT_TYPE::MESHRENDER);
}

CMeshRender::~CMeshRender()
{

}


int CMeshRender::update()
{
	return 0;
}

void CMeshRender::render()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	Vec3 vObjPos = Object()->Transform()->GetLocalPos();

	if (KEYAWAY(KEY_TYPE::KEY_6))
	{
		vector<CGameObject*> vec = pCurScene->GetLayer(L"ColTile")->GetObjVec();
	
		for (size_t i = 0;  i < vec.size(); ++i)
		{
			vec[i]->MeshRender()->SetRender(false);
		}
	}
	if (KEYAWAY(KEY_TYPE::KEY_7))
	{
		vector<CGameObject*> vec = pCurScene->GetLayer(L"ColTile")->GetObjVec();

		for (size_t i = 0; i < vec.size(); ++i)
		{
			vec[i]->MeshRender()->SetRender(true);
		}
	}

	if (Object()->GetName() == L"RouteTile")
	{

		static bool f = false;

		CLayer* pLayer = CSceneMgr::GetInst()->GetLayer(L"Camera");
		CGameObject* pCameraObject = pLayer->GetObjVec()[0];
		Vec3 vCamPos = pCameraObject->Transform()->GetLocalPos();

		tResolution vResolution = CCore::GetInst()->GetResoultion();

		if (Object()->Transform()->GetLocalPos().x<vCamPos.x + vResolution.x / 2 + 65
			&& Object()->Transform()->GetLocalPos().x>vCamPos.x - vResolution.x / 2 - 65
			&& Object()->Transform()->GetLocalPos().y<vCamPos.y + vResolution.y / 2 + 65
			&& Object()->Transform()->GetLocalPos().y>vCamPos.y - vResolution.y / 2 - 65)
		{
			Object()->MeshRender()->SetRender(true);
		}
		else
		{
			Object()->MeshRender()->SetRender(false);
			return;
		}
	}


	if (Object()->GetLayerIdx() == pCurScene->GetLayer(L"Skill")->GetIdx())
	{
		if (vObjPos.x == 0.f && vObjPos.y == 0.f)
		{
			Object()->MeshRender()->SetRender(false);
			return;
		}
		else
		{
			Object()->MeshRender()->SetRender(true);
		}
	}

	if (Object() == nullptr || Object()->MeshRender() == nullptr )
		return;

	if (false == Object()->MeshRender()->GetRender())
		return;

	if (nullptr == m_pMesh || m_pMaterial == nullptr)
		return;



	// Transform 행렬정보를 버퍼에 업데이트 시켜야 한다.
	Transform()->UpdateData();

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		CAnimator2D::ClearData();
	}

	m_pMaterial->UpdateData();

	m_pMesh->SetShader(m_pMaterial->GetShader());
	m_pMesh->render();

	if (Collider())
	{
		//if(m_bColRender)
		//	Collider()->render();
	}
}

CMaterial * CMeshRender::GetCloneMaterial()
{
	m_pMaterial = m_pMaterial->Clone();
	m_bClone = true;
	return m_pMaterial;
}


void CMeshRender::Save(FILE * _pFile)
{
	CComponent::Save(_pFile);

	bool bMesh = false;
	bool bMaterial = false;
	bool bTex = false;

	if (nullptr != m_pMesh)
	{
		bMesh = true;
	}
	if (nullptr != m_pMaterial)
	{
		bMaterial = true;
	}
	if (nullptr != m_pTex)
	{
		bTex = true;
	}

	fwrite(&bMesh, sizeof(bool), 1, _pFile);
	fwrite(&bMaterial, sizeof(bool), 1, _pFile);
	fwrite(&bTex, sizeof(bool), 1, _pFile);

	fwrite(&m_bClone, sizeof(bool), 1, _pFile);

	if (bMesh)
		SaveWString(m_pMesh->GetName(), _pFile);
	if (bMaterial)
	{
		SaveWString(m_pMaterial->GetName(), _pFile);
		if (m_bClone)
		{
			if (nullptr != m_pMaterial->GetTexture())
			{
				SaveWString(m_pMaterial->GetTexture()->GetName(), _pFile);
				wstring a = m_pMaterial->GetTexture()->GetName();
			}
			else
				SaveWString(L"NULL", _pFile);

		}
	}
	if (bTex)
		SaveWString(m_pTex->GetName(), _pFile);
}

void CMeshRender::Load(FILE * _pFile)
{
	CComponent::Load(_pFile);

	bool bMesh = false;
	bool bMaterial = false;
	bool bTex = false;

	fread(&bMesh, sizeof(bool), 1, _pFile);
	fread(&bMaterial, sizeof(bool), 1, _pFile);
	fread(&bTex, sizeof(bool), 1, _pFile);


	fread(&m_bClone, sizeof(bool), 1, _pFile);

	if (bMesh)
	{
		m_pMesh = CResMgr::GetInst()->Load<CMesh>(LoadWString(_pFile));
	}
	if (bMaterial)
	{
		m_pMaterial = CResMgr::GetInst()->Load<CMaterial>(LoadWString(_pFile));
		if (m_bClone)
		{
			wstring a = LoadWString(_pFile);
			if (L"NULL" != a)
			{
				CTexture* pTex = CResMgr::GetInst()->Load<CTexture>(a);
				CMaterial* pMtrl = GetCloneMaterial();
				pMtrl->SetData(SHADER_PARAM::TEX_0, pTex);
			}
		}
	}
	if (bTex)
	{
		m_pTex = CResMgr::GetInst()->Load<CTexture>(LoadWString(_pFile));
	}

}
//if (nullptr != m_pTex)
//{
//	ID3D11ShaderResourceView* pSRV = m_pTex->GetSRV();
//	if (pSRV != nullptr)
//		CONTEXT->PSSetShaderResources(0, 1, &pSRV);
//}