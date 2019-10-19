
static const float PI = 3.141592;
static const float Epsilon = 0.00001;
static const float3 Fdielectric = 0.04;

//This probably doesn't go here
static const uint NumLights = 3;

cbuffer cbMain : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
};

Texture2D texAlbedo    : register(t0);
Texture2D texNormal    : register(t1);
Texture2D texMetalness : register(t2);
Texture2D texRoughness : register(t3);
Texture2D texAO        : register(t4);
TextureCube texSpecular : register(t4);
TextureCube texIrradiance : register(t5);
Texture2D specularBRDF_LUT : register(t6);

SamplerState samLinear : register(s0);
SamplerState spBRDF_Sampler : register(s1);

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

// GGX/Towbridge-Reitz normal distribution function.
// Uses Disney's reparametrization of alpha = roughness^2.
float ndfGGX(float cosLH, float roughness )
{
  float alpha = roughness * roughness;
  float alphaSQ = alpha * alpha;

  float denom = (cosLH * cosLH) * (alphaSQ - 1.0) + 1.0;

  return alphaSQ / (PI * denom * denom);
}

// Single term for separable Schlick-GGX below.
float gaSchlickG1(float cosTheta, float k)
{
  return cosTheta / (cosTheta * (1.0 - k) + k);
}

// Schlick-GGX approximation of geometric attenuation function using Smith's method.
float gaSchlickGGX(float cosLi, float cosLo, float roughness)
{
	float r = roughness + 1.0;
	float k = (r * r) / 8.0; // Epic suggests using this roughness remapping for analytic lights.
  
	return gaSchlickG1(cosLi, k) * gaSchlickG1(cosLo, k);
}

// Shlick's approximation of the Fresnel factor.
float3 fresnelShlick(float3 F0, float cosTheta)
{
  return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// Returns number of mipmap levels for specular IBL environment map.
uint querySpecularTextureLevels()
{
	uint width, height, levels;
	texSpecular.GetDimensions(0, width, height, levels);
	return levels;
}