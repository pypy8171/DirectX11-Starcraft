#pragma once

#include "define.h"

struct tResolution
{
	float x, y;
};

struct tTexInfo
{
	wstring		strTexName;
	POINT		vLeftTop;
	POINT		vCropSize;
	POINT		vImageSize; // vColliderSize 아직 어떤건지는 모름
};

// 정점 구조체
struct VTX
{
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;

	// 명암을 결정
	Vec3 vTangent;
	Vec3 vBinormal;
	Vec3 vNormal;
};

struct IDX32
{
	UINT _i1, _i2, _i3;

	IDX32()
		: _i1(0)
		, _i2(0)
		, _i3(0)
	{}

	IDX32(UINT __1, UINT __2, UINT __3)
		: _i1(__1)
		, _i2(__2)
		, _i3(__3)
	{}
};

struct tTransformMatrix // 320 바이트 vec4 4개짜리 5묶음
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
	Matrix matWV;
	Matrix matWVP;
	Matrix matInvWorld;
};

struct InstanceType
{
	Vec3	vPosition;
};

struct InstancedData
{
	Matrix World;
	//Vec4 Color;
};

struct tShaderParam
{
	int arrInt[4];
	float arrFloat[4];
	Vec2 arrVec2[4];
	Vec4 arrVec4[4];
};

struct tAnim2DInfo
{
	Vec2 vLT;
	Vec2 vSize;
	int g_bAnim2dUse;
	int g_bBlendUse;
	int g_iPadding[2];
};

struct tEvent
{
	EVENT_TYPE eType;
	INT_PTR	wParam;
	INT_PTR lParam;
};

struct tLightCol
{
	Vec4 vDiff;	// 확산광
	Vec4 vSpec; // 반사광
	Vec4 vAmb;	// 환경광
};

struct tLightInfo
{
	tLightCol tCol;		// 광원 색상 정보
	Vec4	  vDir;		// 광원 방향
	Vec4	  vPos;    // 광원 위치	
	float	  fDist;   // 광원이 닿는 거리
	float     fAngle;  // Spot Light 각도
	int		  iType;   // 광원 타입
	int       iPad;    // 패딩
};

struct tGlobalValue
{
	float fDT;
	float fAccTime;
	int   iLightCount;
	int   iPadding;
};