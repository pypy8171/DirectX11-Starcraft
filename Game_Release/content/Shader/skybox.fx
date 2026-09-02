#include "value.fx"

#ifndef _HLSL_SKYBOX
#define _HLSL_SKYBOX

struct VS_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 vOutPos : SV_Position;
    float2 vOutUV : TEXCOORD;
};

//======================================================
// SkyBox Shader - SkyBox 전용 쉐이더
// AlphaBlend = false
// CullMod = 
// g_Tex_0 : SkyBox Texture
//=======================================================

VS_OUTPUT VS_SkyBox(VS_INPUT _input)
{
    // input 으로 들어온 위치정보를 투영좌표계 까지 변환한다.
    VS_OUTPUT output = (VS_OUTPUT) 0.f;
   
    output.vOutPos = mul(float4(_input.vPos, 0.f), matView); // 투영행렬 그대로 가져오는 x w값 곱해진 상태로 옴(W는 안하는 이유 -> 항상 센터(로컬 기준으로 하기 위함)
    output.vOutPos = mul(output.vOutPos, matProj);
    output.vOutPos.z = output.vOutPos.w;

    output.vOutUV = _input.vUV;

    return output;
}

float4 PS_SkyBox(VS_OUTPUT _input) : SV_Target
{
    return g_tex_0.Sample(g_sam_0, _input.vOutUV);
}




#endif