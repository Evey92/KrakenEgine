#include "Commons.hlsl"

float3 m_lightPos;
float4 m_eyePos;

cbuffer cbMain : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
};

cbuffer cbShading : register(b1)
{
  float4 eyePosition;
  float4 lightDirection;
  float4 radiance;
};

struct VS_INPUT 
{
   float4 Position : POSITION;
   float2 TexCoord : TEXCOORD;
   float3 Normal   : NORMAL;
   float3 Tangent  : TANGENT;
   float3 BiNormal : BINORMAL;

};

struct PS_INPUT
{
    float4 Position             : SV_POSITION;
    float2 WorldPosition   : POSITION;
    float2 TexCoord        : TEXCOORD0;
    float3x3 TBN           : TEXCOORD1;
};

Texture2D texAlbedo    : register(t0);
Texture2D texNormal    : register(t1);
Texture2D texMetalness : register(t2);
Texture2D texRoughness : register(t3);
TextureCube texSpecular : register(t4);
TextureCube texIrradiance : register(t5);
Texture2D specularBRDF_LUT : register(t6);

SamplerState samLinear : register(s0);
SamplerState spBRDF_Sampler : register(s1);

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

PS_INPUT VS(VS_INPUT Input)
{
  PS_INPUT POutput;
  POutput = mul

  Output.Position = mul(Input.Position, World);
  Output.WorldPosition = Output.Position.xyz;
  Output.Position = mul(Output.Position, View);
  Output.Position = mul(Output.Position, Projection);

  Output.TexCoord = Input.TexCoord;
  
  float3x3 TBN = float3x3(Input.Tangent, Input.Binormal, Input.Normal);

  Output.TBN = mul(TBN, (float3x3) World);

  return Output;
}

float4 PS(PS_INPUT Input) : SV_Target
{

// Sample input textures to get shading model params.
  float4 albedo = tex2D(AlbedoSampler, Input.TexCoord);
  float metalness = tex2D(MetalnessSampler, Input.TexCoord);
  float roughness = tex2D(RoughnessSampler, Input.TexCoord);

  // Outgoing light direction (vector from world-space fragment position to the "eye").
	float3 Lo = normalize(m_eyePos - Input.Pos);

  float N = normalize(2.0 * texNormal.Sample(samLinear, Input.TexCoord).rgb - 1.0);
  N = normalize(mul(Input.TBN, N));

	// Angle between surface normal and outgoing light direction.
  float cosLo = max(0.0, dot(N, Lo));

  // Specular reflection vector.
	float3 Lr = 2.0 * cosLo * N - Lo;

  float3 F0 = lerp(Fdielectric, albedo, metalness);

  // Direct lighting calculation for analytical lights.
	float3 directLight = 0.0;
  for(uint i=0; i<NumLights; ++i)
	{
    float3 Li = -lights[i].direction;
		float3 Lradiance = lights[i].radiance;

    // Half-vector between Li and Lo.
		float3 Lh = normalize(Li + Lo);

    // Calculate angles between surface normal and various light vectors.
		float cosLi = max(0.0, dot(N, Li));
		float cosLh = max(0.0, dot(N, Lh));

		// Calculate Fresnel term for direct lighting. 
    float3 F = fresnelShlick(F0, max(Lh, Lo));

		// Calculate normal distribution for specular BRDF.
    float D = ndfGGX(cosLh, roughness);

		// Calculate geometric attenuation for specular BRDF.
    float G = gaSchlickGGX(cosLi, cosLo, roughness);

    float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metalness);

    float3 diffuseBRDF = kd * albedo;

    float3 specularBRDF = (F * G * D) / max(Epsilon, 4.0 * cosLi * cosLo);

    directLight = (diffuseBRDF + specularBRDF)  *  Lradiance * cosLi;
  }

	// Ambient lighting (IBL).
  float3 ambientLight;
  {
		float3 irradiance = texIrradiance.Sample(samLinear, N).rgb;

    float3 F = fresnelShlick(F0, cosLo);

		// Get diffuse contribution factor (as with direct lighting).
    float3 kd = lerp(1.0f - F, 0.0, metalness);

    float3 diffuseIBL = kd * albedo * irradiance;

    // Sample pre-filtered specular reflection environment at correct mipmap level.
		uint specularTextureLevels = querySpecularTextureLevels();
		float3 specularIrradiance = texSpecular.SampleLevel(samLinear, Lr, roughness * specularTextureLevels).rgb;

    // Split-sum approximation factors for Cook-Torrance specular BRDF.
		float2 specularBRDF = specularBRDF_LUT.Sample(spBRDF_Sampler, float2(cosLo, roughness)).rg;

    // Total specular IBL contribution.
		float3 specularIBL = (F0 * specularBRDF.x + specularBRDF.y) * specularIrradiance;

    // Total ambient lighting contribution.
		ambientLighting = diffuseIBL + specularIBL;

  }

  // Final fragment color.
	return float4(directLight + ambientLighting, 1.0);
}