#include "Grid.h"

#include "GameObject.h"

#include "Core.h"

#include "Transform.h"
#include "MeshRender.h"
#include "Collider.h"

#include "EventMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "KeyMgr.h"

#include "Scene.h"
#include "Layer.h"


CGrid::CGrid()
	: m_vGridSize(Vec2(0.f, 0.f))
	, m_vNextTileNum(Vec2(0.f,0.f))
	, m_vTileNum(Vec2(75, 75))
	, m_iTileSize(32)
	, m_iHorizontalNum(0)
	, m_iVerticalNum(0)
	, m_iGapX(0)
	, m_iGapY(0)
	, m_bRenderOn(false)
{
	SetComponentType(COMPONENT_TYPE::GRID);
	vecTile.resize((const unsigned int)m_vTileNum.y);
}


CGrid::~CGrid()
{
	for (int i = 0; i < vecTile.size(); ++i)
	{
		Safe_Delete_Vec(vecTile[i]);
	}
}

int CGrid::update()
{

	// 툴 주석할거
	for (size_t i = m_iGapY; i < m_iVerticalNum + m_iGapY; ++i)
	{
		for (size_t j = m_iGapX; j < m_iHorizontalNum + m_iGapX; ++j)
		{
			vecTile[i][j]->update();
		}
	}

	if (KEYAWAY(KEY_TYPE::KEY_0))
	{
		if(m_bRenderOn)
			m_bRenderOn = false;
		else if (!m_bRenderOn)
			m_bRenderOn = true;
	}
	return 0;
}

int CGrid::finalupdate()
{
	// 툴 주석할거
	for (size_t i = m_iGapY; i < m_iVerticalNum + m_iGapY; ++i)
	{
		for (size_t j = m_iGapX; j < m_iHorizontalNum + m_iGapX; ++j)
		{
			vecTile[i][j]->finalupdate();
		}
	}
	return 0;
}

void CGrid::awake()
{
	CGameObject* pGameObject = nullptr;

	for (int i = 0; i < m_vTileNum.y; ++i)
	{
		for (int j = 0; j < m_vTileNum.x; ++j)
		{
			pGameObject = new CGameObject;
			pGameObject->SetLayerIdx(0);
			pGameObject->AddComponent(new CCollider);
			pGameObject->AddComponent(new CMeshRender);
			pGameObject->Transform()->SetLocalPos(Vec3((float)(m_iTileSize*j - m_vTileNum.x * m_iTileSize*0.5f),
				(float)(m_iTileSize *i - m_vTileNum.y * m_iTileSize*0.5f), g_depthz+50.f));
			pGameObject->Transform()->SetLocalScale(Vec3(m_iTileSize, m_iTileSize, 1.f));

			pGameObject->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
			//pGameObject->MeshRender()->SetMaterial(nullptr);

			pGameObject->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_2D_BOX);
			pGameObject->Collider()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
			pGameObject->Collider()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"StdGrid2DShader"));

			vecTile[i].push_back(pGameObject);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
			//pCurScene->AddGameObject(L"Grid", pGameObject);
		}
	}
	m_vGridSize = Vec2(m_vTileNum.x* m_iTileSize, m_vTileNum.y * m_iTileSize);
}

void CGrid::ChangeGrid()
{
	for (int i = 0; i < vecTile.size(); ++i)
	{
		Safe_Delete_Vec(vecTile[i]);
	}
	vecTile.clear();

	m_vTileNum = m_vNextTileNum;

	vecTile.resize((const unsigned int)m_vTileNum.y);

	awake();
}

void CGrid::render()
{
	// 툴
	CalCurView(); // 주석할거

	//return; // 주석풀거

	if (m_bRenderOn)
	{
		for (size_t i = m_iGapY; i < m_iVerticalNum + m_iGapY; ++i)
		{
			for (size_t j = m_iGapX; j < m_iHorizontalNum + m_iGapX; ++j)
			{

				vecTile[i][j]->render();
			}
		}
	}
}

void CGrid::SetGridSize(Vec2 _vGridSize)
{
	m_vNextTileNum = _vGridSize;
	CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::RENEWAL,(INT_PTR)this,NULL});
}


void CGrid::DeleteTile(CGameObject * pObj)
{
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		Safe_Delete_Vec(vecTile[i]);
	}
}

void CGrid::CalCurView()
{
	CLayer* pLayer = CSceneMgr::GetInst()->GetLayer(L"Camera");
	CGameObject* pCameraObject = pLayer->GetObjVec()[0];
	Vec3 vCamPos = pCameraObject->Transform()->GetLocalPos();

	tResolution vResolution = CCore::GetInst()->GetResoultion();

	m_iHorizontalNum = vResolution.x / m_iTileSize;
	m_iVerticalNum = vResolution.y / m_iTileSize;

	m_iGapX = (m_vGridSize.x*0.5 - vResolution.x*0.5 + vCamPos.x) / m_iTileSize;
	m_iGapY = (m_vGridSize.y*0.5 - vResolution.y*0.5 + vCamPos.y) / m_iTileSize;

	if (m_iHorizontalNum + m_iGapX >= m_vTileNum.x)
	{
		m_iGapX = m_vTileNum.x - m_iHorizontalNum;
	}
	if(m_iVerticalNum + m_iGapY >= m_vTileNum.y)
	{
		m_iGapY = m_vTileNum.y - m_iVerticalNum;
	}
}

void CGrid::Save(FILE * _pFile)
{
	fwrite(&m_vGridSize, sizeof(Vec2), 1, _pFile);
	fwrite(&m_vTileNum, sizeof(Vec2), 1, _pFile);
	fwrite(&m_iTileSize, sizeof(int), 1, _pFile);
	fwrite(&m_iHorizontalNum, sizeof(int), 1, _pFile);
	fwrite(&m_iVerticalNum, sizeof(int), 1, _pFile);
	fwrite(&m_iGapX, sizeof(int), 1, _pFile);
	fwrite(&m_iGapY, sizeof(int), 1, _pFile);

	int iSize = m_vecTileIdx.size();
	fwrite(&iSize, sizeof(int), 1, _pFile);
	for (int i = 0; i < m_vecTileIdx.size(); ++i)
	{
		fwrite(&m_vecTileIdx[i], sizeof(Vec2), 1, _pFile);
	}
}

void CGrid::Load(FILE * _pFile)
{
	fread(&m_vGridSize, sizeof(Vec2), 1, _pFile);
	fread(&m_vTileNum, sizeof(Vec2), 1, _pFile);
	fread(&m_iTileSize, sizeof(int), 1, _pFile);
	fread(&m_iHorizontalNum, sizeof(int), 1, _pFile);
	fread(&m_iVerticalNum, sizeof(int), 1, _pFile);
	fread(&m_iGapX, sizeof(int), 1, _pFile);
	fread(&m_iGapY, sizeof(int), 1, _pFile);

	int iSize = 0;
	Vec2 v = Vec2{};
	fread(&iSize, sizeof(int), 1, _pFile);
	for (int i = 0; i < iSize; ++i)
	{
		fread(&v, sizeof(Vec2), 1, _pFile);
		m_vecTileIdx.push_back(v);
	}

	vecTile.resize((const unsigned int)m_vTileNum.y);

	awake();
}
