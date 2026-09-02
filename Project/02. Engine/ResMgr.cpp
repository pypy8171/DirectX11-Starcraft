#include "ResMgr.h"

#include "Ptr.h"
#include "Mesh.h"
#include "Sound.h"

#include "Animation2D.h"

#include "ShaderMgr.h"

CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	for (UINT i = 0; i < (UINT)RESOURCE_TYPE::END; ++i)
	{
		Safe_Delete_Map(m_mapRes[i]);
	}
	Safe_Delete_Vec(m_vecCloneRes);


	// FMOD 객체 해제
	CSound::g_pFMOD->release();
}

void CResMgr::init()
{
	CreateDefaultMesh();
	CreateDefaultMaterial();

	// FMOD 초기화
	SoundInit();
}

void CResMgr::SoundInit()
{
	FMOD::System_Create(&CSound::g_pFMOD);

	if (nullptr == CSound::g_pFMOD)
	{
		assert(nullptr);
	}

	CSound::g_pFMOD->init(32, FMOD_DEFAULT, nullptr);

}

void CResMgr::CreateDefaultMesh()
{
	///////////
	// 3D Mesh
	///////////

	// 정점
	VTX arrVTX[8] = {};
	arrVTX[0].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrVTX[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[0].vUV = Vec2(0.f, 0.f);

	arrVTX[1].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrVTX[1].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[1].vUV = Vec2(1.f, 0.f);

	arrVTX[2].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrVTX[2].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[2].vUV = Vec2(1.f, 1.f);

	arrVTX[3].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrVTX[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[3].vUV = Vec2(0.f, 1.f);

	arrVTX[4].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrVTX[4].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[4].vUV = Vec2(0.f, 0.f);

	arrVTX[5].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrVTX[5].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[5].vUV = Vec2(1.f, 0.f);

	arrVTX[6].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrVTX[6].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[6].vUV = Vec2(1.f, 1.f);

	arrVTX[7].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrVTX[7].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[7].vUV = Vec2(0.f, 1.f);

	// 인덱스 버퍼 만들기 앞
	IDX32 arrIdx[12] = {};
	arrIdx[0]._i1 = 0;
	arrIdx[0]._i2 = 1;
	arrIdx[0]._i3 = 2;

	arrIdx[1]._i1 = 0;
	arrIdx[1]._i2 = 2;
	arrIdx[1]._i3 = 3;

	// 오른
	arrIdx[2]._i1 = 1;
	arrIdx[2]._i2 = 5;
	arrIdx[2]._i3 = 6;

	arrIdx[3]._i1 = 1;
	arrIdx[3]._i2 = 6;
	arrIdx[3]._i3 = 2;

	// 왼
	arrIdx[4]._i1 = 4;
	arrIdx[4]._i2 = 0;
	arrIdx[4]._i3 = 3;

	arrIdx[5]._i1 = 4;
	arrIdx[5]._i2 = 3;
	arrIdx[5]._i3 = 7;

	// 뒤
	arrIdx[6]._i1 = 5;
	arrIdx[6]._i2 = 4;
	arrIdx[6]._i3 = 7;

	arrIdx[7]._i1 = 5;
	arrIdx[7]._i2 = 7;
	arrIdx[7]._i3 = 6;

	//// 위
	arrIdx[8]._i1 = 4;
	arrIdx[8]._i2 = 5;
	arrIdx[8]._i3 = 1;

	arrIdx[9]._i1 = 4;
	arrIdx[9]._i2 = 1;
	arrIdx[9]._i3 = 0;

	// 아래
	arrIdx[10]._i1 = 3;
	arrIdx[10]._i2 = 2;
	arrIdx[10]._i3 = 6;

	arrIdx[11]._i1 = 3;
	arrIdx[11]._i2 = 6;
	arrIdx[11]._i3 = 7;


	CMesh* pMesh = CMesh::Create(arrVTX, sizeof(VTX), 8, D3D11_USAGE_DEFAULT
		, arrIdx, sizeof(UINT), 36, D3D11_USAGE_DEFAULT);

	AddResource<CMesh>(L"FirstCubeMesh", pMesh);


	//////////////////////
	// Collider Rect Mesh (3D)
	//////////////////////
	// 인덱스 버퍼 만들기
	UINT arrCollider3DIdx[5][5] = {
		{0,1,2,3,0},
		{0,4,7,3,0},
		{0,4,7,6,5},
		{4,5,6,2,1},
		{5,1}
	};
	/*{ 5,1,0,3,2,1,5,4,0,4,7,3,7,6,2,6,5,4,7 };*/

	pMesh = CMesh::Create(arrVTX, sizeof(VTX), 8, D3D11_USAGE_DEFAULT
		, arrCollider3DIdx, sizeof(UINT), 25, D3D11_USAGE_DEFAULT,  D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	AddResource<CMesh>(L"ColliderCubeMesh", pMesh);

	////////////////////////////////////////
	arrVTX[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[1].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[2].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[4].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[5].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[6].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[7].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	pMesh = CMesh::Create(arrVTX, sizeof(VTX), 8, D3D11_USAGE_DEFAULT
		, arrIdx, sizeof(UINT), 36, D3D11_USAGE_DEFAULT);

	AddResource<CMesh>(L"Redhexahedron", pMesh);

	////////////////////////////////////////
	arrVTX[0].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVTX[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVTX[2].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVTX[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVTX[4].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVTX[5].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVTX[6].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVTX[7].vColor = Vec4(0.f, 1.f,  0.f, 1.f);

	pMesh = CMesh::Create(arrVTX, sizeof(VTX), 8, D3D11_USAGE_DEFAULT
		, arrIdx, sizeof(UINT), 36, D3D11_USAGE_DEFAULT);

	AddResource<CMesh>(L"Bluehexahedron", pMesh);
	////////////////////////////////////////
	arrVTX[0].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVTX[1].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVTX[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVTX[3].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVTX[4].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVTX[5].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVTX[6].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVTX[7].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	pMesh = CMesh::Create(arrVTX, sizeof(VTX), 8, D3D11_USAGE_DEFAULT
		, arrIdx, sizeof(UINT), 36, D3D11_USAGE_DEFAULT);

	AddResource<CMesh>(L"Greenhexahedron", pMesh);

	///////////////
	// 2D RectMesh
	///////////////
	arrVTX[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVTX[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[0].vUV = Vec2(0.f, 0.f);

	arrVTX[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVTX[1].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[1].vUV = Vec2(1.f, 0.f);

	arrVTX[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVTX[2].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[2].vUV = Vec2(1.f, 1.f);

	arrVTX[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVTX[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVTX[3].vUV = Vec2(0.f, 1.f);

	arrIdx[0]._i1 = 0;
	arrIdx[0]._i2 = 1;
	arrIdx[0]._i3 = 2;

	arrIdx[1]._i1 = 0;
	arrIdx[1]._i2 = 2;
	arrIdx[1]._i3 = 3;

	pMesh = CMesh::Create(arrVTX, sizeof(VTX), 4, D3D11_USAGE_DEFAULT
		, arrIdx, sizeof(UINT), 6, D3D11_USAGE_DEFAULT);

	AddResource<CMesh>(L"RectMesh", pMesh);

	//////////////////////
	// 2D ColliderRectMesh
	//////////////////////
	UINT arrColliderIdx[5] = {0,1,2,3,0};

	pMesh = CMesh::Create(arrVTX, sizeof(VTX), 4, D3D11_USAGE_DEFAULT
		, arrColliderIdx, sizeof(UINT), 5, D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	AddResource<CMesh>(L"ColliderRectMesh", pMesh);

	/////////////////
	// 2D CircleMesh
	/////////////////
	vector<VTX> vecVTX;
	vector<UINT> vecIDX;
	VTX vtx;

	int iSliceCount = 64;
	float fTheta = XM_2PI / (float)iSliceCount;

	vtx.vPos = Vec3(0.f, 0.f, 0.f);
	vtx.vColor = Vec4(1.f,0.f, 0.f, 1.f);

	vecVTX.push_back(vtx);

	for (int i = 0; i < iSliceCount; ++i)
	{
		vtx.vPos = Vec3(0.5f * cos(fTheta*i), 0.5f*sin(fTheta*i), 0.f);
		vtx.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
		vecVTX.push_back(vtx);
	}

	for (UINT i = 0; i < iSliceCount - 1; ++i)
	{
		vecIDX.push_back(0);
		vecIDX.push_back(i + 2);
		vecIDX.push_back(i + 1);
	}

	vecIDX.push_back(0);
	vecIDX.push_back(1);
	vecIDX.push_back(iSliceCount);

	pMesh = CMesh::Create(&vecVTX[0], sizeof(VTX), vecVTX.size(), D3D11_USAGE_DEFAULT
		, &vecIDX[0], sizeof(UINT), vecIDX.size(), D3D11_USAGE_DEFAULT);

	AddResource<CMesh>(L"CircleMesh", pMesh);

	/////////////////////////
	// 2D ColliderCircleMesh
	/////////////////////////
	vecVTX.clear();
	vecIDX.clear();

	for (int i = 0; i < iSliceCount; ++i)
	{
		vtx.vPos = Vec3(0.5f * cos(fTheta*i), 0.5f*sin(fTheta*i), 0.f);
		vtx.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
		vecVTX.push_back(vtx);
	}

	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIDX.push_back(i);
	}

	pMesh = CMesh::Create(&vecVTX[0], sizeof(VTX), vecVTX.size(), D3D11_USAGE_DEFAULT
		, &vecIDX[0], sizeof(UINT), vecIDX.size(), D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	AddResource<CMesh>(L"ColliderCircleMesh", pMesh);

	//======================
	// Cube Mesh
	//======================
	VTX arrCube[24] = {};

	// 윗면
	arrCube[0].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[0].vUV = Vec2(0.f, 0.f);
	arrCube[0].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[1].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[1].vUV = Vec2(0.f, 0.f);
	arrCube[1].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[2].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[2].vUV = Vec2(0.f, 0.f);
	arrCube[2].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[3].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[3].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[3].vUV = Vec2(0.f, 0.f);
	arrCube[3].vNormal = Vec3(0.f, 1.f, 0.f);


	// 아랫 면	
	arrCube[4].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[4].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[4].vUV = Vec2(0.f, 0.f);
	arrCube[4].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[5].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[5].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[5].vUV = Vec2(0.f, 0.f);
	arrCube[5].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[6].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[6].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[6].vUV = Vec2(0.f, 0.f);
	arrCube[6].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[7].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[7].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[7].vUV = Vec2(0.f, 0.f);
	arrCube[7].vNormal = Vec3(0.f, -1.f, 0.f);

	// 왼쪽 면
	arrCube[8].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[8].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[8].vUV = Vec2(0.f, 0.f);
	arrCube[8].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[9].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[9].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[9].vUV = Vec2(0.f, 0.f);
	arrCube[9].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[10].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[10].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[10].vUV = Vec2(0.f, 0.f);
	arrCube[10].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[11].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[11].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[11].vUV = Vec2(0.f, 0.f);
	arrCube[11].vNormal = Vec3(-1.f, 0.f, 0.f);

	// 오른쪽 면
	arrCube[12].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[12].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[12].vUV = Vec2(0.f, 0.f);
	arrCube[12].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[13].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[13].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[13].vUV = Vec2(0.f, 0.f);
	arrCube[13].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[14].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[14].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[14].vUV = Vec2(0.f, 0.f);
	arrCube[14].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[15].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[15].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[15].vUV = Vec2(0.f, 0.f);
	arrCube[15].vNormal = Vec3(1.f, 0.f, 0.f);

	// 앞 면
	arrCube[16].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[16].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[16].vUV = Vec2(0.f, 0.f);
	arrCube[16].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[17].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[17].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[17].vUV = Vec2(0.f, 0.f);
	arrCube[17].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[18].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[18].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[18].vUV = Vec2(0.f, 0.f);
	arrCube[18].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[19].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[19].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[19].vUV = Vec2(0.f, 0.f);
	arrCube[19].vNormal = Vec3(0.f, 0.f, 1.f);

	// 뒷 면
	arrCube[20].vPos = Vec3(-0.5f, 0.5f, -0.5f);;
	arrCube[20].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[20].vUV = Vec2(0.f, 0.f);
	arrCube[20].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[21].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[21].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[21].vUV = Vec2(0.f, 0.f);
	arrCube[21].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[22].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[22].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[22].vUV = Vec2(0.f, 0.f);
	arrCube[22].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[23].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[23].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[23].vUV = Vec2(0.f, 0.f);
	arrCube[23].vNormal = Vec3(0.f, 0.f, -1.f);

	// 인덱스
	IDX32 arrCubeIdx[12] = {};

	for (int i = 0; i < 12; i += 2)
	{
		arrCubeIdx[i] = IDX32(i * 2, i * 2 + 1, i * 2 + 2);
		arrCubeIdx[i + 1] = IDX32(i * 2, i * 2 + 2, i * 2 + 3);
	}

	pMesh = CMesh::Create(arrCube, sizeof(VTX), 24, D3D11_USAGE_DEFAULT
		, arrCubeIdx, sizeof(UINT), 36, D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	AddResource<CMesh>(L"CubeMesh", pMesh);

	//==============
	// Sphere Mesh
	//==============
	vecVTX.clear();
	vecIDX.clear();
	VTX v;

	float fRadius = 1.f;

	// Top
	v.vPos = Vec3(0.f, fRadius, 0.f);
	v.vUV = Vec2(0.5f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vNormal = v.vPos;
	v.vNormal.Normalize();
	v.vTangent = Vec3(1.f, 0.f, 0.f);
	v.vBinormal = Vec3(0.f, 0.f, 1.f);
	vecVTX.push_back(v);

	// Body
	UINT iStackCount = 40; // 가로 분할 개수
	iSliceCount = 40; // 세로 분할 개수

	float fStackAngle = XM_PI / iStackCount;
	float fSliceAngle = XM_2PI / iSliceCount;

	float fUVXStep = 1.f / (float)iSliceCount;
	float fUVYStep = 1.f / (float)iStackCount;

	for (UINT i = 1; i < iStackCount; ++i)
	{
		float phi = i * fStackAngle;

		for (UINT j = 0; j <= iSliceCount; ++j)
		{
			float theta = j * fSliceAngle;

			v.vPos = Vec3(fRadius * sinf(i * fStackAngle) * cosf(j * fSliceAngle)
				, fRadius * cosf(i * fStackAngle)
				, fRadius * sinf(i * fStackAngle) * sinf(j * fSliceAngle));
			v.vUV = Vec2(fUVXStep * j, fUVYStep * i);
			v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
			v.vNormal = v.vPos;
			v.vNormal.Normalize();

			v.vTangent.x = -fRadius * sinf(phi) * sinf(theta);
			v.vTangent.y = 0.f;
			v.vTangent.z = fRadius * sinf(phi) * cosf(theta);
			v.vTangent.Normalize();

			v.vTangent.Cross(v.vNormal, v.vBinormal);
			v.vBinormal.Normalize();

			vecVTX.push_back(v);
		}
	}

	// Bottom
	v.vPos = Vec3(0.f, -fRadius, 0.f);
	v.vUV = Vec2(0.5f, 1.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vNormal = v.vPos;
	v.vNormal.Normalize();
	v.vTangent = Vec3(1.f, 0.f, 0.f);
	v.vBinormal = Vec3(0.f, 0.f, -1.f);
	vecVTX.push_back(v);

	// 인덱스
	// 북극점
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIDX.push_back(0);
		vecIDX.push_back(i + 2);
		vecIDX.push_back(i + 1);
	}

	// 몸통
	for (UINT i = 0; i < iStackCount - 2; ++i)
	{
		for (UINT j = 0; j < iSliceCount; ++j)
		{
			// + 
			// | \
						// +--+
			vecIDX.push_back((iSliceCount + 1) * (i)+(j)+1);
			vecIDX.push_back((iSliceCount + 1) * (i + 1) + (j + 1) + 1);
			vecIDX.push_back((iSliceCount + 1) * (i + 1) + (j)+1);

			// +--+
			//  \ |
			//    +
			vecIDX.push_back((iSliceCount + 1) * (i)+(j)+1);
			vecIDX.push_back((iSliceCount + 1) * (i)+(j + 1) + 1);
			vecIDX.push_back((iSliceCount + 1) * (i + 1) + (j + 1) + 1);
		}
	}

	// 남극점
	UINT iBottomIdx = vecVTX.size() - 1;
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIDX.push_back(iBottomIdx);
		vecIDX.push_back(iBottomIdx - (i + 2));
		vecIDX.push_back(iBottomIdx - (i + 1));
	}

	pMesh = CMesh::Create(&vecVTX[0], sizeof(VTX), vecVTX.size(), D3D11_USAGE_DEFAULT
		, &vecIDX[0], sizeof(UINT), vecIDX.size(), D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	AddResource<CMesh>(L"SphereMesh", pMesh);

}
void CResMgr::CreateDefaultMaterial()
{
	CMaterial* pMtrl = nullptr;

	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	AddResource<CMaterial>(L"ColorMtrl", pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"ColliderShader"));
	AddResource<CMaterial>(L"ColliderMtrl", pMtrl); 

	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"Std2DShader"));
	AddResource<CMaterial>(L"Std2DMtrl", pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"UnitShader"));
	AddResource<CMaterial>(L"UnitMtrl", pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"StdGrid2DShader"));
	AddResource<CMaterial>(L"StdGrid2DShader", pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"SkyBoxShader"));
	AddResource<CMaterial>(L"SkyBoxMtrl", pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TestShader"));
	AddResource<CMaterial>(L"TestMtrl", pMtrl);
}

void CResMgr::DeleteResource(RESOURCE_TYPE _eType, const wstring & _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapRes[(UINT)_eType].find((wstring)_strKey);

	if (iter != m_mapRes[(UINT)_eType].end())
	{
		if (nullptr != iter->second)
			delete iter->second;
		m_mapRes[(UINT)_eType].erase(_strKey);
	}
}

