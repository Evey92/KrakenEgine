
cbuffer cbMain : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
};

struct VS_INPUT 
{
   float4 Position : POSITION;
   float2 TexCoord : TEXCOORD0;
   float3 Normal   : NORMAL;
   float3 Tangent  : TANGENT;
   float3 BiNormal : BINORMAL;

};

struct PS_INPUT
{
    float4 Pos             : SV_POSITION;
    float2 WorldPosition   : TEXCOORD0;
    float2 TexCoord        : TEXCOORD1;
    float3x3 TBN           : TEXCOORD2;
};

float ndf_GGX(float cosLH, float roughness)
{
  float alpha = roughness * roughness;
  float alphaSq = alpha * alpha;

  float denom = (cosLH * cosLH) * (alphaSq - 1.0f) + 1.0f;
  return alphaSq / (M_PI * denom * denom);

}

float ga_SchlickG1(float cosTheta, float k)
{
  return cosTheta / (cosTheta * (1.0 - k) + k);
}

//Schlick-GGX approximation of geometric attenaution function using Smith's methods
float ga_SchlickGGX(float cosLi, float cosLo, float roughness)
{
  float r = roughness + 1.0;

  float k = (r * r) / 8.0;

  return ga_SchlickG1(cosLi, k) * ga_SchlickG1(cosLo, k);
}

//Schlick's aproximation of the Fresnel factor
float3 fresnelSchlick(float3 F0, float cosTheta)
{
  return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}