#include "CollisionMgr.h"
#include "Collider.h"

#include "SceneMgr.h"
#include "Layer.h"




CCollisionMgr::CCollisionMgr()
	: m_iColliderCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

int CCollisionMgr::update()
{
	// 충돌 진행
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		for (int j = i; j < MAX_LAYER; ++j)
		{
			if (m_iColliderCheck[i] & (1 << j))
			{
				Collision(i, j);
			}
		}
	}

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrCollider[i].clear();
	}
	return 0;
}

void CCollisionMgr::CollisionCheck(UINT _iLayerIdx1, UINT _iLayerIdx2)
{
	assert(CSceneMgr::GetInst()->GetLayer(_iLayerIdx1));
	assert(CSceneMgr::GetInst()->GetLayer(_iLayerIdx2));

	// 두 값중 더 작은 값을 행 인덱스로...
	UINT iRow = _iLayerIdx1;
	UINT iCol = _iLayerIdx2;

	if (iRow > _iLayerIdx2)
	{
		iRow = _iLayerIdx2;
		iCol = _iLayerIdx1;
	}

	UINT iCheck = 1 << iCol;
	m_iColliderCheck[iRow] |= iCheck;
}

void CCollisionMgr::CollisionCheck(const wstring & _strLayerName1, const wstring & _strLayerName2)
{
	UINT iLayerIdx1 = CSceneMgr::GetInst()->GetLayer(_strLayerName1)->GetIdx();
	UINT iLayerIdx2 = CSceneMgr::GetInst()->GetLayer(_strLayerName2)->GetIdx();

	m_vecFirst.push_back(_strLayerName1);
	m_vecSecond.push_back(_strLayerName2);

	CollisionCheck(iLayerIdx1, iLayerIdx2);
}

void CCollisionMgr::Collision(UINT _iFirst, UINT _iSecond)
{
	for (UINT i = 0; i < m_arrCollider[_iFirst].size(); ++i)
	{
		for (UINT j = 0; j < m_arrCollider[_iSecond].size(); ++j)
		{
			CID id;
			id._id_1 = m_arrCollider[_iFirst][i]->GetID();
			id._id_2 = m_arrCollider[_iSecond][j]->GetID();
			map<ULONGLONG, bool>::iterator iter = m_mapID.find(id.id);

			// 충돌 했다.
			if (IsCollision(m_arrCollider[_iFirst][i], m_arrCollider[_iSecond][j]))
			{
				if (iter == m_mapID.end())
				{
					// 조합이 등록 x -> 이전에 충돌한적 없다. -> 최초 충돌
					m_mapID.insert(make_pair(id.id, true));
					m_arrCollider[_iFirst][i]->OnCollisionEnter(m_arrCollider[_iSecond][j]);
					m_arrCollider[_iSecond][j]->OnCollisionEnter(m_arrCollider[_iFirst][i]);
				}
				else if (false == iter->second)
				{
					// 이전에 충돌한적 없다 -> 최초 충돌
					iter->second = true;
					m_arrCollider[_iFirst][i]->OnCollisionEnter(m_arrCollider[_iSecond][j]);
					m_arrCollider[_iSecond][j]->OnCollisionEnter(m_arrCollider[_iFirst][i]);
				}
				else
				{
					// 충돌 중
					m_arrCollider[_iFirst][i]->OnCollision(m_arrCollider[_iSecond][j]);
					m_arrCollider[_iSecond][j]->OnCollision(m_arrCollider[_iFirst][i]);
				}
			}
			// 충돌 안함
			else
			{
				if (iter != m_mapID.end() && true == iter->second)
				{
					// 충돌 막 벗어난 시점
					iter->second = false;
					m_arrCollider[_iFirst][i]->OnCollisionExit(m_arrCollider[_iSecond][j]);
					m_arrCollider[_iSecond][j]->OnCollisionExit(m_arrCollider[_iFirst][i]);
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider * _pFirst, CCollider * _pSecond)
{
	Vec3 vCenterFirst = XMVector3TransformCoord(Vec3::Zero, _pFirst->GetCollideMat()); // 첫번째 충돌체 중점
	Vec3 vCenterSecond = XMVector3TransformCoord(Vec3::Zero, _pSecond->GetCollideMat()); // 두번째 충돌체 중점

	if (COLLIDER_TYPE::COLLIDER_2D_BOX == _pFirst->GetColliderType() && COLLIDER_TYPE::COLLIDER_2D_BOX == _pSecond->GetColliderType())
	{
		// 두 충돌체 간의 충돌 여부 확인하기

		// 0 ---- 1
		// |      |
		// |      |
		// 3 ---- 2
		// 충돌체 위치로 가기 전의 로컬스페이스 상의 4개의 정점
		static Vec3 arrLocal[4] = { Vec3(-0.5f, 0.5f,  -0.5f)
			, Vec3(0.5f, 0.5f,  -0.5f)
			, Vec3(0.5f, -0.5f,  -0.5f)
			, Vec3(-0.5f, -0.5f,  -0.5f) };


		Vec3 col1[3] = {};
		// 후보
		Vec3 vSource[4] = {};
		Vec3 vProj[4] = {};
		Vec3 vCenter = vCenterFirst - vCenterSecond;

		// 첫번째 충돌체로 부터 투영축과 투영시킬 벡터 구하기
		col1[0] = XMVector3TransformCoord(arrLocal[3], _pFirst->GetCollideMat()); // w로 1로 세팅
		col1[1] = XMVector3TransformCoord(arrLocal[0], _pFirst->GetCollideMat());
		col1[2] = XMVector3TransformCoord(arrLocal[2], _pFirst->GetCollideMat());

		vSource[0] = col1[2] - col1[0];
		vSource[1] = col1[1] - col1[0];

		vProj[0] = vSource[0];
		vProj[0].Normalize();

		vProj[1] = vSource[1];
		vProj[1].Normalize();

		// 두번째 충돌체로 부터 투영 후보와, 투영 축 얻어내기
		col1[0] = XMVector3TransformCoord(arrLocal[3], _pSecond->GetCollideMat());
		col1[1] = XMVector3TransformCoord(arrLocal[0], _pSecond->GetCollideMat());
		col1[2] = XMVector3TransformCoord(arrLocal[2], _pSecond->GetCollideMat());

		vSource[2] = col1[2] - col1[0];
		vSource[3] = col1[1] - col1[0];

		vProj[2] = vSource[2]; vProj[2].Normalize();
		vProj[3] = vSource[3]; vProj[3].Normalize();

		for (int i = 0; i < 4; ++i)
		{
			float fDist = 0.f;
			float fCenter = 0.f;
			for (int j = 0; j < 4; ++j)
			{
				fDist += abs(vSource[j].Dot(vProj[i]));
			}
			fDist *= 0.5f;
			fCenter = abs(vCenter.Dot(vProj[i]));

			if (fCenter > fDist)
			{
				return false;
			}
		}
		return true;
	}
	else if (COLLIDER_TYPE::COLLIDER_2D_CIRCLE == _pFirst->GetColliderType() && COLLIDER_TYPE::COLLIDER_2D_CIRCLE == _pSecond->GetColliderType())
	{
		float fAddRadius = _pFirst->GetFinalRadius() + _pSecond->GetFinalRadius();
		float fDist = Vec3::Distance(vCenterFirst, vCenterSecond);

		if (fDist < fAddRadius)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (COLLIDER_TYPE::COLLIDER_2D_CIRCLE != _pFirst->GetColliderType())
		{
			CCollider* pTemp = _pFirst;
			_pFirst = _pSecond;
			_pSecond = pTemp;
		}

		// 각을 구하고 그 각만큼 회전
		// 사각형이 회전된 각도를 알아야 한다. 최종적으로 사각형이 회전된 각도를 원에도 적용
		//Matrix matCircle = _pFirst->GetCollideMat();
		//Matrix matBox = _pSecond->GetCollideMat();

		//Vec3 vCenter = vCenterFirst - vCenterSecond;
		//float fDistance = Vec3::Distance(vCenterFirst, vCenterSecond);

		//Vec3 vRight = Vec3(fDistance, 0.f, 0.f);

		//float fRad = atan2f(vCenterFirst.y - vCenterSecond.y, vCenterFirst.x - vCenterSecond.x); // 원하고 사각형 각도
		//float fDegree = atan2f(vCenterFirst.y - vCenterSecond.y, vCenterFirst.x - vCenterSecond.x) * (180.f / 3.14f);

		//matCircle *= cos(-45 * RAD);
		//matBox *= cos(-45 * RAD);

		//float ScaleX = sqrt(matBox(1, 1)*matBox(1, 1) + matBox(1, 2)*matBox(1, 2)); // vCenter.x
		//float ScaleY = sqrt(matBox(2, 2)*matBox(2, 2) + matBox(2, 1)*matBox(2, 1)); // vCenter.y
		//float ScaleZ = matBox(3, 3);

		//float ScaleXY = sqrt(ScaleX / 2.f*ScaleX / 2.f + ScaleY / 2.f * ScaleY / 2.f);

		//float fAddScaleXRadius = _pFirst->GetFinalRadius() + ScaleX / 2.f; // 이것도 회전되었을대의 x값이 되어야 한다.
		//float fAddScaleYRadius = _pFirst->GetFinalRadius() + ScaleY / 2.f;
		//float fAddScaleZRadius = _pFirst->GetFinalRadius() + ScaleZ / 2.f;

		//vCenterFirst = XMVector3TransformCoord(Vec3::Zero, matCircle); // 첫번째 충돌체 중점
		//vCenterSecond = XMVector3TransformCoord(Vec3::Zero, matBox); // 두번째 충돌체 중점

		//float fDist = Vec3::Distance(vCenterFirst, vCenterSecond);

		float ScaleX = _pSecond->GetCollideMat()(1, 1);
		float ScaleY = _pSecond->GetCollideMat()(2, 2);
		float ScaleZ = _pSecond->GetCollideMat()(3, 3);

		float ScaleXY = sqrt(ScaleX / 2.f*ScaleX / 2.f + ScaleY / 2.f * ScaleY / 2.f);

		float fAddScaleXRadius = _pFirst->GetFinalRadius() + ScaleX / 2.f; // 이것도 회전되었을대의 x값이 되어야 한다.
		float fAddScaleYRadius = _pFirst->GetFinalRadius() + ScaleY / 2.f;
		float fAddScaleZRadius = _pFirst->GetFinalRadius() + ScaleZ / 2.f;

		float fDist = Vec3::Distance(vCenterFirst, vCenterSecond);

		if ((vCenterFirst.x > vCenterSecond.x - ScaleX / 2.f && vCenterFirst.x < vCenterSecond.x + ScaleX / 2.f)
			|| (vCenterFirst.y > vCenterSecond.y - ScaleY / 2.f && vCenterFirst.y < vCenterSecond.y + ScaleY / 2.f))
		{
			if (fDist < fAddScaleXRadius)
			{
				// 2,8 section
				if (vCenterFirst.y < vCenterSecond.y/*vCenterFirst.y + _pFirst->GetFinalRadius() > vCenterSecond.y - ScaleY / 2.f*/ // 원의 중점이 사각형 아래이고 원의 상단 점이 사각형 하단 점보다 위일때
					&& vCenterFirst.x > vCenterSecond.x - ScaleX / 2.f &&  vCenterFirst.x < vCenterSecond.x + ScaleX / 2.f) // 원의 중점이 사각형 왼쪽 오른쪽 변 사이
				{
					return true;
				}
				if (vCenterFirst.y > vCenterSecond.y/*vCenterFirst.y - _pFirst->GetFinalRadius() < vCenterSecond.y + ScaleY / 2.f*/ // 원의 중점이 사각형 위이고 원의 하단 점이 사각형 상단 점보다 아래일때
					&& vCenterFirst.x > vCenterSecond.x - ScaleX / 2.f &&  vCenterFirst.x < vCenterSecond.x + ScaleX / 2.f)
				{
					return true;
				}
				// 4,6 section
				if (vCenterFirst.x < vCenterSecond.x/*vCenterFirst.x + _pFirst->GetFinalRadius() > vCenterSecond.x - ScaleX / 2.f*/ // 원의 중점이 사각형 위이고 원의 하단 점이 사각형 상단 점보다 아래일때
					&& vCenterFirst.y > vCenterSecond.y - ScaleY / 2.f &&  vCenterFirst.y < vCenterSecond.y + ScaleY / 2.f)
				{
					return true;
				}
				if (vCenterFirst.x > vCenterSecond.x/*vCenterFirst.x - _pFirst->GetFinalRadius() < vCenterSecond.x + ScaleX / 2.f*/ // 원의 중점이 사각형 위이고 원의 하단 점이 사각형 상단 점보다 아래일때
					&& vCenterFirst.y > vCenterSecond.y - ScaleY / 2.f &&  vCenterFirst.y < vCenterSecond.y + ScaleY / 2.f)
				{
					return true;
				}
			}
		}
		else
		{
			if (_pFirst->GetFinalRadius() + ScaleXY > fDist)
			{
				// 1
				if (vCenterFirst.x < vCenterSecond.x - ScaleX / 2.f && vCenterFirst.y > vCenterSecond.y + ScaleY / 2.f)
				{
					return true;
				}
				// 3
				if (vCenterFirst.x > vCenterSecond.x + ScaleX / 2.f && vCenterFirst.y > vCenterSecond.y + ScaleY / 2.f)
				{
					return true;
				}
				// 5
				if (vCenterFirst.x < vCenterSecond.x - ScaleX / 2.f && vCenterFirst.y < vCenterSecond.y - ScaleY / 2.f)
				{
					return true;
				}
				// 7
				if (vCenterFirst.x > vCenterSecond.x - ScaleX / 2.f && vCenterFirst.y < vCenterSecond.y - ScaleY / 2.f)
				{
					return true;
				}
			}
		}
		return false;
	}
	return true;
}

void CCollisionMgr::SaveFile(FILE * _pFile)
{
	size_t iSize = m_vecFirst.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i <iSize; ++i)
	{
		SaveWString(m_vecFirst[i], _pFile);
		SaveWString(m_vecSecond[i], _pFile);
	}
}

void CCollisionMgr::LoadFile(FILE * _pFile)
{
	if(!m_vecFirst.empty())
		m_vecFirst.clear();
	if(!m_vecSecond.empty())
		m_vecSecond.clear();

	size_t iSize = 0;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i <iSize; ++i)
	{
		//m_vecFirst.push_back(LoadWString(_pFile));
		//m_vecSecond.push_back(LoadWString(_pFile));
	}
	for (size_t i = 0; i < iSize; ++i)
	{
		CollisionCheck(LoadWString(_pFile), LoadWString(_pFile));
	}
}


//if (COLLIDER_TYPE::COLLIDER_2D_CIRCLE != _pFirst->GetColliderType())
//{
//	CCollider * Temp = _pFirst;
//	_pFirst = _pSecond;
//	_pSecond = Temp;
//}

//XMVector3TransformCoord();// 마지막 요소 1로 확장해서 곱해주는 함수. // 이동까지 영향 받고 싶다.
//XmVector3TransformNormal()// 마지막 요소 0으로 확장해서 곱해주는 함수. // 크기 회전만 영향 받고 싶다. // 방향벡터를 회전시킬때만

////////////////////////////////////////////////////

/*const Vec2& vPos1 = _pFirst->GetPos();
const Vec2& vPos2 = _pSecond->GetPos();

const Vec2& vScale1 = _pFirst->GetScale();
const Vec2& vScale2 = _pSecond->GetScale();

if (abs(vPos1.x - vPos2.x) > vScale1.x / 2.f + vScale2.x / 2.f
|| abs(vPos1.y - vPos2.y) > vScale1.y / 2.f + vScale2.y / 2.f)
{
return false;
}

return true;*/

/*if (COL_TYPE::RECT == _pFirst->GetType && COL_TYPE::RECT == _pSecond->GetType())
{
const Vec2& vPos1 = _pFirst->GetPos();
const Vec2& vPos2 = _pSecond->GetPos();

const Vec2& vScale1 = _pFirst->GetScale();

const Vec2& vScale2 = _pSecond->GetScale();

if (abs(vPos1.x - vPos2.x) > vScale1.x / 2.f + vScale2.x / 2.f
|| abs(vPos1.y - vPos2.y) > vScale1.y / 2.f + vScale2.y / 2.f)
{
return false;
}

return true;
}
else if (COL_TYPE::CIRCLE == _pFirst->GetType() && COL_TYPE::CIRCLE == _pSecond->GetType())
{

}
else
{

}	*/



//if (vCenterFirst.x > vCenterSecond.x - ScaleX / 2.f && vCenterFirst.x < vCenterSecond.x + ScaleX / 2.f
//	&&vCenterFirst.y > vCenterSecond.y - ScaleY / 2.f && vCenterFirst.y < vCenterSecond.y + ScaleY / 2.f)
//{
//	return true;
//}