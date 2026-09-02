#include "Value.fx"

#ifndef _HLSL_STD
#define _HLSL_STD

struct VS_INPUT
{
	float3 vPos : POSITION; // 시멘틱은 코어에서 만들어주는 것과 같은 이름으로
	float4 vColor : COLOR;
	float2 vUV : TEXCOORD;
	//row_major matrix World : WORLD;
	//uint InstanceId : SV_InstanceID;

};

struct VS_OUTPUT
{
	float4 vOutPos : SV_Position; // system_value  시멘틱은 고정 // float4로 하는 이유는 행렬때문이지 않을까
	float4 vOutColor : COLOR;
	float2 vOutUV : TEXCOORD;
	//row_major matrix vOutWorld : WORLD;
};


//==========================
// Std Shader - 2D 표준 쉐이더
// AlphaBlend = true
// g_tex_0 : diffuse texture
//==========================

VS_OUTPUT VS_Std2D(VS_INPUT _input)
{
	// input 으로 들어온 위치정보를 투영좌표계까지 변환한다.
	VS_OUTPUT output = (VS_OUTPUT) 0.f; // hlsl 에서의 초기화 방법

	float4 vWorldPos = mul(float4(_input.vPos, 1.f), matWorld);
	float4 vViewPos = mul(vWorldPos, matView);
	float4 vProjPos = mul(vViewPos, matProj);



	output.vOutPos = vProjPos;
	output.vOutColor = _input.vColor;
	output.vOutUV = _input.vUV;

    return output;
}

// rasterize 이후 pixelshader

// 픽셀 쉐이더
float4 PS_Std2D(VS_OUTPUT _input) : SV_Target // 0은 생략 // 보간된 픽셀들이 들어감 // 이후 present 하면 우리 윈도우 화면에 출력
{

    float4 vCol = (float4)0.f;
    
    if (g_bAnim2dUse)
    {
        // 정점에서 가져온 UV 값을 픽셀의 상대적인 위치를 찾는 비율로 활용한다.
        float2 vAnimUV = float2(g_vLT.x + (g_vSize.x * _input.vOutUV.x), g_vLT.y + (g_vSize.y * _input.vOutUV.y));
        vCol = g_tex_Anim.Sample(g_sam_0, vAnimUV);
        if (vCol.r > 0.2 && vCol.g < 0.1)
        {
            vCol.r = 0.7f;
            vCol.g = 0.2f;
            vCol.b = 0.2f;
        }
    }
    else
    {   
       vCol = g_tex_0.Sample(g_sam_0, _input.vOutUV);
    }


    if (0.f == vCol.a)
        clip(-1);
    return vCol;
}

//==========================
// UnitShader - 유닛만 사용하는 쉐이더
// AlphaBlend = true
// g_tex_0 : diffuse texture
//==========================

VS_OUTPUT VS_Unit(VS_INPUT _input)
{
	// input 으로 들어온 위치정보를 투영좌표계까지 변환한다.
    VS_OUTPUT output = (VS_OUTPUT) 0.f; // hlsl 에서의 초기화 방법

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), matWorld);
    float4 vViewPos = mul(vWorldPos, matView);
    float4 vProjPos = mul(vViewPos, matProj);

    output.vOutPos = vProjPos;
    output.vOutColor = _input.vColor;
    output.vOutUV = _input.vUV;

    return output;
}

// rasterize 이후 pixelshader

// 픽셀 쉐이더
float4 PS_Unit(VS_OUTPUT _input) : SV_Target // 0은 생략 // 보간된 픽셀들이 들어감 // 이후 present 하면 우리 윈도우 화면에 출력
{
    float4 vCol = (float4) 0.f;
    
    if (g_bAnim2dUse)
    {
        // 정점에서 가져온 UV 값을 픽셀의 상대적인 위치를 찾는 비율로 활용한다.
        float2 vAnimUV = float2(g_vLT.x + (g_vSize.x * _input.vOutUV.x), g_vLT.y + (g_vSize.y * _input.vOutUV.y));
        vCol = g_tex_Anim.Sample(g_sam_0, vAnimUV);
        if (vCol.r > 0.2 && vCol.g < 0.1)
        {
            vCol.r = 0.2f;
            vCol.g = 0.5f;
            vCol.b = 0.5f;
        }
    }
    else
    {   
        vCol = g_tex_0.Sample(g_sam_0, _input.vOutUV);
    }

    if (g_int[0])
    {
        if(vCol.r != 1.f && vCol.g != 1.f && vCol.b != 1.f)
            vCol.a = 0.3f;
    }
    else
    {
        if (0.f == vCol.a)
            clip(-1);
        return vCol;
    }
      

    if (0.f == vCol.a)
        clip(-1);
    return vCol;
}

//===========================================
// Color Shader - 정점 색상으로 출력하는 쉐이더
// AlphaBlend = false
//===========================================


VS_OUTPUT VS_Color(VS_INPUT _input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0.f; // hlsl 에서의 초기화 방법

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), matWorld);
    float4 vViewPos = mul(vWorldPos, matView);
    float4 vProjPos = mul(vViewPos, matProj);

    output.vOutPos = vProjPos;
    output.vOutColor = _input.vColor;
    output.vOutUV = _input.vUV;

    return output;
}

float4 PS_Color(VS_OUTPUT _input) : SV_Target
{
    return _input.vOutColor;
}

//==========================
// Collision Shader
// g_int[0] : true, collision / false, collisionx
//==========================

VS_OUTPUT VS_Collider(VS_INPUT _input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), matWorld);
    float4 vViewPos = mul(vWorldPos, matView);
    float4 vProjPos = mul(vViewPos, matProj);

    output.vOutPos = vProjPos;
    output.vOutColor = _input.vColor;
    output.vOutUV = _input.vUV;

    return output;
}

float4 PS_Collider(VS_OUTPUT _input) : SV_Target
{
    if (g_int[0])
    {
        return float4(1.f, 0.1f, 0.1f, 1.f);
    }
    else
    {
        return float4(0.2f, 1.f, 0.2f, 1.f);
    }
}

// Grid용 충돌 -> 얘만 색 바꾸기 위함.

VS_OUTPUT VS_GridCollider(VS_INPUT _input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), matWorld);
    float4 vViewPos = mul(vWorldPos, matView);
    float4 vProjPos = mul(vViewPos, matProj);

    output.vOutPos = vProjPos;
    output.vOutColor = _input.vColor;
    output.vOutUV = _input.vUV;

    return output;
}

float4 PS_GridCollider(VS_OUTPUT _input) : SV_Target
{
     return float4(0.f, 0.f, 0.f, 1.f);
}
      //if ((0.01f < _input.vOutUV.x && _input.vOutUV.x < 0.99f)
    //  && (0.01f <_input.vOutUV.y && _input.vOutUV.y < 0.99f))
    //{
    //    clip(-1);
    //}

#endif