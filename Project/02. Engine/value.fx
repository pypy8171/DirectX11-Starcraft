#ifndef _HLSL_VALUE
#define _HLSL_VALUE


//=========
// Struct
//=========
struct tLightCol
{
    float4 vDiff;
    float4 vSpec;
    float4 vAmb;
};

struct tLightInfo
{
    tLightCol tCol; // 광원 색상 정보
    float4 vDir; // 광원 방향
    float4 vPos; // 광원 위치    
    float fDist; // 광원이 닿는 거리
    float fAngle; // Spot Light 각도
    int iType; // 광원 타입
    int iPadding;
};

cbuffer TransformMatrix : register(b0)
{
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProj;
    row_major matrix matWV;
    row_major matrix matWVP;
    row_major matrix matInvWorld;
};

// 변경될 값들을 위한 변수들
cbuffer SHADER_PARAM : register(b1)
{
    int4 g_int; // 각 자리별 이름을 주어도 됨. 16바이트 단위로 주소를 띄워가서 이렇게 사용.
    float4 g_float;
    float2x4 g_vec2;
    float4x4 g_vec4;
};

cbuffer ANIM2D : register(b2)
{
    float2 g_vLT;
    float2 g_vSize;
    int g_bAnim2dUse;
    int g_bBlendUse;
    int g_iPadding[2];
}

cbuffer LIGHT : register(b3)
{
    tLightInfo g_arrLights[10];
}

cbuffer GLOBAL : register(b4)
{
    float g_fDT;
    float g_fAccTime;
    int g_iLightCount;
    int g_iSomething;
};

// 렌더 타겟 뷰 최대 갯수인 8개
Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);
Texture2D g_tex_6 : register(t6);
Texture2D g_tex_7 : register(t7);


Texture2D g_tex_Anim : register(t16);

SamplerState g_sam_0 : register(s0); // 추출작업

// Shader Function
tLightCol CalculateLight(float3 _vViewNormal, float3 _vViewPos, tLightInfo _info)
{
    tLightCol col = (tLightCol) 0.f;

    // 방향성 광원인 경우
    if (_info.iType == 0)
    {
        // ViewSpacce vLight Vector
        float3 vLightDir = normalize(mul(_info.vDir, matView));
    
        // ViewSpace Reflect Vector
        float3 vReflect = normalize(vLightDir + 2 * _vViewNormal * dot(-vLightDir, _vViewNormal));
         
        // ViewSpace 에서 원점이 관찰자 이기 때문에, 표면의 위치가 곧 그곳을 향하는 방향벡터(eyeVector)
        float3 vEye = -normalize(_vViewPos);

        // Diffuse 강도
        col.vDiff = _info.tCol.vDiff * saturate(dot(_vViewNormal, -vLightDir));

        // Specular 강도
        float fReflectPow = saturate(dot(vReflect, vEye));
        col.vSpec = _info.tCol.vSpec * pow(fReflectPow, 10);

        col.vAmb = _info.tCol.vAmb;
    }

    // 점 광원
    else if (_info.iType == 1)
    {
        // ViewSpacce vLight Vector      
        float4 vViewLightPos = mul(_info.vPos, matView); //mul(_info.vPos, matView);
        float3 vLightDir = normalize(_vViewPos - vViewLightPos.xyz);

        // 거리에 따른 감소 비율
        float fRatio = saturate((_info.fDist - distance(vViewLightPos.xyz, _vViewPos.xyz)) / _info.fDist);
        

        // Diffuse 강도
        if (distance(vViewLightPos.xyz, _vViewPos.xyz) < 125)
            col.vDiff = _info.tCol.vDiff * (dot(_vViewNormal, vLightDir)) * fRatio;
        else
            col.vDiff = _info.tCol.vDiff * (dot(_vViewNormal, -vLightDir)) * fRatio;
    }
    else
    {

    }
       
    return col;
}

float rand_1_05(in float2 uv)
{
    float2 noise = (frac(sin(dot(uv, float2(12.9898, 78.233) * 2.0)) * 43758.5453));
    return abs(noise.x + noise.y) * 0.5;
}

float2 rand_2_10(in float2 uv)
{
    float noiseX = (frac(sin(dot(uv, float2(12.9898, 78.233) * 2.0)) * 43758.5453));
    float noiseY = sqrt(1 - noiseX * noiseX);
    return float2(noiseX, noiseY);
}

float2 rand_2_0004(in float2 uv)
{
    float noiseX = (frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453));
    float noiseY = (frac(sin(dot(uv, float2(12.9898, 78.233) * 2.0)) * 43758.5453));
    return float2(noiseX, noiseY) * 0.004;
}

#endif