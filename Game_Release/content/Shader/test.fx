#include "value.fx"

#ifndef _HLSL_TEST
#define _HLSL_TEST

struct VS_INPUT
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;

    float3 vNormal : NORMAL;
    float3 vTangent : TANGENT;
    float3 vBinormal : BINORMAL;
};

struct VS_OUTPUT
{
    float4 vOutPos : SV_Position;
    float4 vOutCol : COLOR;
    float2 vOutUV : TEXCOORD;

    float2 vTexCoord1 : TEXCOORD1;
    float2 vTexCoord2 : TEXCOORD2;
    float2 vTexCoord3 : TEXCOORD3;

    float3 vNormal : NORMAL;
    float3 vTangent : TANGENT;
    float3 vBinormal : BINORMAL;
    float3 vViewPos : POSITION;

};
//  coord = 1 , normal = 0
//======================================================
// Test Rambert Shader
// AlphaBlend = false
// CullMod = 
// g_Tex_0 : SkyBox Texture
//=======================================================

VS_OUTPUT VS_TEST(VS_INPUT _input)
{
    // input 으로 들어온 위치정보를 투영좌표계 까지 변환한다.
    VS_OUTPUT output = (VS_OUTPUT) 0.f;
   
    output.vOutPos = mul(float4(_input.vPos, 1.f), matWVP);
    output.vOutCol = _input.vColor;

    output.vOutUV = _input.vUV;

    float3 scrollspeed = float3(1.3f, 2.1f, 2.3f);
    
    output.vTexCoord1 = (_input.vUV * 1.f);
    output.vTexCoord1.y = output.vTexCoord1.y + (scrollspeed.x);

    output.vTexCoord2 = (_input.vUV * 1.f);
    output.vTexCoord2.y = output.vTexCoord2.y + ( scrollspeed.y);

    output.vTexCoord3 = (_input.vUV * 1.f);
    output.vTexCoord3.y = output.vTexCoord3.y + ( scrollspeed.z);

    // Normal vector 의 월드 변환은 월드행렬 역행렬의 전치를 곱한다.    
    output.vNormal = mul(matInvWorld, float4(_input.vNormal, 0.f));
    output.vNormal = normalize(mul(float4(output.vNormal, 0.f), matView));

    //output.vNormal = normalize(mul(float4(_input.vNormal, 0.f), matWV));
    output.vViewPos = mul(float4(_input.vPos, 1.f), matWV);
       
    return output;
}

float4 PS_TEST(VS_OUTPUT _input) : SV_Target
{
    tLightInfo LTInfo = (tLightInfo) 0.f;

   //LTInfo.iType = 0;
   //LTInfo.tCol.vDiff = float4(1.f, 1.f, 1.f, 0.f);
   //LTInfo.vDir = float4(1, -1, 1.f, 0.f);
   //LTInfo.tCol.vSpec = float4(0.4f, 0.4f, 0.4f, 0.f);
   //LTInfo.tCol.vAmb = float4(0.1f, 0.1f, 0.1f, 0.f);

    LTInfo.iType = 1;
    LTInfo.tCol.vDiff = float4(1.f, 1.f, 1.f, 0.f);
    LTInfo.tCol.vSpec = float4(0.0f, 0.0f, 0.0f, 0.f);
    LTInfo.vPos = float4(0.f, 0.f, 5000.f, 1.f);
    LTInfo.fDist = 5000.f;  
       
    float3x3 matTNB =
    {
        _input.vTangent
        , _input.vBinormal
        , _input.vNormal
    };
       
    float3 vNormal = _input.vNormal;

    if (g_int[1])
    {
        vNormal = g_tex_1.Sample(g_sam_0, _input.vOutUV).xyz;
        vNormal = vNormal * 2.f - 1.f;
        vNormal = normalize(mul(-vNormal, matTNB));
    }

    float4 noise1;
    float4 noise2;
    float4 noise3;
    float4 finalnoise;
    float perturb;
    float2 noisecoords;
    float4 firecolor;
    float4 alphacolor;

   // _input.vUV.y += sin(abs((_input.vUV.x - g_fAccTime * 파장 속도) * 진폭 밀도)) * 파장 크기
    

    if (g_int[2])
    {
        _input.vOutUV.y += sin(abs((_input.vOutUV.x - g_fAccTime * 0.01f) * 200.f)) * 0.001f;
        //noise1 = g_tex_0.Sample(g_sam_0, _input.vTexCoord1);
        //noise2 = g_tex_0.Sample(g_sam_0, _input.vTexCoord2);
        //noise3 = g_tex_0.Sample(g_sam_0, _input.vTexCoord3);

        //noise1 = (noise1 - 0.5f) * 2.0f;
        //noise2 = (noise2 - 0.5f) * 2.0f;
        //noise3 = (noise3 - 0.5f) * 2.0f;
        
        //noise1.xy = noise1.xy * float2(0.1f, 0.2f);
        //noise2.xy = noise2.xy * float2(0.1f, 0.3f);
        //noise3.xy = noise3.xy * float2(0.1f, 0.1f);

        //finalnoise = noise1 + noise2 + noise3;

        //perturb = ((1.f - _input.vOutUV.y) * 100.f) * 100.f;

        //noisecoords.xy = (finalnoise.xy * perturb) + _input.vOutUV.xy;

        //firecolor = g_tex_0.Sample(g_sam_0, noisecoords.xy);

        //return float4(firecolor.xyz, 0.4f);

    }

    float4 vColor = g_tex_0.Sample(g_sam_0, _input.vOutUV);


    tLightCol col = CalculateLight(vNormal, _input.vViewPos, LTInfo);

    float3 fCol = (vColor * col.vDiff + col.vSpec + col.vAmb);

    //tLightCol col = (tLightCol) 0.f;
    //float3 fCol = (float3) 0.f;
    //for (int i = 0; i < g_iLightCount; ++i)
    //{
    //    col = CalculateLight(vNormal, _input.vViewPos, g_arrLights[i]);
    //    fCol += vColor * col.vDiff + col.vSpec + col.vAmb;
    //}

    if (g_int[0])
    {
        return float4(fCol, 0.4f);
    }
    else
    {
        return float4(fCol, 1.f);
    }


}

#endif