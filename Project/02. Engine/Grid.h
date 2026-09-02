#pragma once
#include "Component.h"

class CGameObject;
class CCollider;

// 타일 종류

class CGrid :
	public CComponent
{
private:
	vector<vector<CGameObject*>> vecTile;
	vector<Vec2>					m_vecTileIdx;

	Vec2	m_vGridSize;
	Vec2	m_vNextTileNum;

	Vec2 m_vTileNum;
	int m_iTileSize;

	int m_iHorizontalNum;
	int m_iVerticalNum;

	int m_iGapX;
	int m_iGapY;

	bool	m_bRenderOn;


public:
	virtual int update();
	virtual int finalupdate();
	virtual void awake();

	bool& GetRender() { return m_bRenderOn; }

	void ChangeGrid();
	void render();
public:
	//void AddTexture(CGameObject* );
	void SetGridSize(Vec2 _vGridSize);// 

	void SetOccupied(CGameObject* pGameObject, bool _bool) { pGameObject->SetOccupied(_bool); }
	bool& GetOccupied(CGameObject* pGameObject) { return pGameObject->GetOccupied(); }

	void SetColOccupied(CGameObject* pGameObject, bool _bool) { pGameObject->SetColOccupied(_bool); }
	bool& GetColOccupied(CGameObject* pGameObject) { return pGameObject->GetColOccupied(); }
public:
	vector<vector<CGameObject*>>& GetvecTile() { return vecTile; }
	Vec2 GetGridSize() { return m_vGridSize; }
	const Vec2 GetTileNum() { return m_vTileNum; }
	const int GetTileSize() { return m_iTileSize; }

	CGameObject* GetClickedTile(Vec2 _vIdx) { return vecTile[(const unsigned int)_vIdx.y][(const unsigned int)_vIdx.x]; }
	CGameObject* GetClickedTile(CGameObject* pGameObj);
	Vec3 GetTransformed() { return Vec3(m_vGridSize.x / 2, m_vGridSize.y / 2, 0.f); }

	void DeleteTile(CGameObject* pObj);

	void SetTileIdx(Vec2 _vec2) { m_vecTileIdx.push_back(_vec2); }
	vector<Vec2>& GetTileIdx() { return m_vecTileIdx; }

public:
	void CalCurView();

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CLONE(CGrid);


public:
	CGrid();
	virtual ~CGrid();
};

