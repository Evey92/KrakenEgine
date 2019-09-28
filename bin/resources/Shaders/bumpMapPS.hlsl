Texture2D albedoTex: register( t0 );
Texture2D normalTex: register( t1 );
Texture2D metallicTex: register( t2 );
Texture2D RoughnessTex: register( t3 );

SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register(b1)
{
  float4 viewPos;
};

struct PS_INPUT
{
   float4 Position : SV_POSITION;
   float4 WorldPos : POSITION;
   float2 TexCoord : TEXCOORD0;
   float3x3 TBN    : TEXCOORD1;
};

struct PS_OUTPUT
{
  float4 Color : SV_TARGET0;
  //float4 Normal    : SV_TARGET1;
  //float4 Normal   : SV_TARGET2;
};

PS_OUTPUT PS(PS_INPUT input) : SV_TARGET
{
  PS_OUTPUT Output = (PS_OUTPUT)0;
  float3 lightPos = float3(100.0f, 0.0f, 100.0f);
  float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
  float3 lightDirection = float3(0.0f, 0.0f, 1.0f);
  float3 lightDir;
  float3 bumpNormal;
  float intensity;
  float4 finalColor;

  float4 Diffusecolor = albedoTex.Sample( samLinear, input.TexCoord);

  float4 normal = normalTex.Sample(samLinear, input.TexCoord); 
  normal = (2.0f * normal) - 1.0f;

  bumpNormal = (normal.x * input.TBN[0]) + (normal.y * input.TBN[1]) + (normal.z * input.TBN[2]);
  bumpNormal = normalize(bumpNormal);

  lightDir = -lightDirection;

  intensity = saturate(dot(bumpNormal, lightDir));

  finalColor = (lightColor * intensity);

  finalColor = finalColor * Diffusecolor;
  
  Output.Color = finalColor;
  return Output;

}