#include "Commons.hlsl"

//TODO: Get this from a constant fear
const float nearZ = 0.01f;
const float farZ = 1000.0f;

cbuffer cbMain : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    matrix skyProjection;
};

cbuffer cbShading : register(b0)
{
    float4 eyePosition;
    float4 lightDirection;
    float4 radiance;
    //float4 meshColor;
};

struct VS_INPUT
{
    float4 Position  : POSITION;
    float2 TexCoord  : TEXCOORD;
    float3 Normal    : NORMAL;
    float3 Tangent   : TANGENT;
    float3 BiNormal  : BINORMAL;
    float3 vertColor : COLOR;
};

struct PS_INPUT
{
    float4 worldPosition : SV_POSITION;
    float3 Position      : POSITION;
    float2 TexCoord      : TEXCOORD0;
    float3x3 TBN         : TEXCOORD1;
};

struct PS_OUTPUT
{
    float4 PositionMetal : SV_Target0;
    float4 AlbedoTrans   : SV_Target1;
    float4 NormalRough   : SV_Target2;
    //float AO            : SV_Target3;
};

Texture2D texAlbedo    : register(t0);
Texture2D texNormal    : register(t1);
Texture2D texMetalness : register(t2);
Texture2D texRoughness : register(t3);
//This is going to be calculated on the SSAO pass
//Texture2D texAO        : register(t4);

SamplerState samLinear : register(s0);



PS_INPUT VS(VS_INPUT Input)
{
    PS_INPUT Output;

    Output.worldPosition = mul(Input.Position, World);
    Output.Position = Output.worldPosition.xyz;
    Output.worldPosition = mul(Output.worldPosition, View);
    Output.worldPosition = mul(Output.worldPosition, Projection);

    Output.TexCoord = Input.TexCoord;
  
    float3x3 TBN = float3x3(Input.Tangent, Input.BiNormal, Input.Normal);
    Output.TBN = mul(transpose(TBN), (float3x3) World);
    
    return Output;
}

PS_OUTPUT PS(PS_INPUT Input) : SV_Target
{
    PS_OUTPUT Output;

    float4 albedo = texAlbedo.Sample(samLinear, Input.TexCoord);
    float4 normalTex = texNormal.Sample(samLinear, Input.TexCoord);

    float3 normal = 2.0f * normalTex.xyz - 1;
    normal = normalize(mul(normal, Input.TBN));   

    Output.PositionMetal = float4(Input.Position, 1.0f);
    Output.PositionMetal.a = texMetalness.Sample(samLinear, Input.TexCoord).r;

    Output.AlbedoTrans.rgb = albedo.rgb;
    Output.AlbedoTrans.a = albedo.a;
    
    Output.NormalRough.rgb = normal.rgb;
    Output.NormalRough.a = texRoughness.Sample(samLinear, Input.TexCoord).r;

    //Output.AO.r = texAO.Sample(samLinear, Input.TexCoord).r;

    return Output;

} 