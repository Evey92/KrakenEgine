#include "Commons.hlsl"

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
    float3 vertColor      : COLOR;
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
float3 fresnelSchlick(float3 F0, float cosTheta)
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

PS_INPUT VS(VS_INPUT Input)
{
    PS_INPUT Output;

    Output.worldPosition = mul(Input.Position, World);
    Output.Position = Output.worldPosition.xyz;
    Output.worldPosition = mul(Output.worldPosition, View);
    Output.worldPosition = mul(Output.worldPosition, Projection);

    Output.TexCoord = float2(Input.TexCoord.x, 1.0 - Input.TexCoord.y);
  
    float3x3 TBN = float3x3(Input.Tangent, Input.BiNormal, Input.Normal);
    Output.TBN = mul(transpose(TBN), (float3x3) World);

    Output.vertColor = Input.vertColor;

    return Output;
}

float4 PS(PS_INPUT Input) : SV_Target
{

    // Sample input textures to get shading model params.
    float3 albedo = texAlbedo.Sample(samLinear, Input.TexCoord).rgb;
    float metalness = texMetalness.Sample(samLinear, Input.TexCoord).r;
    float roughness = texRoughness.Sample(samLinear, Input.TexCoord).r;

     // Outgoing light direction (vector from world-space fragment position to the "eye").
    float3 Lo = normalize(eyePosition.xyz - Input.Position);

    float3 N = normalize(2.0 * texNormal.Sample(samLinear, Input.TexCoord).rgb - 1.0);
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
        float3 Li = -lightDirection.xyz;
        float3 Lradiance = radiance.xyz;

        // Half-vector between Li and Lo.
	    float3 Lh = normalize(Li + Lo);

        // Calculate angles between surface normal and various light vectors.
	    float cosLi = max(0.0, dot(N, Li));
	    float cosLh = max(0.0, dot(N, Lh));

	    // Calculate Fresnel term for direct lighting. 
        float3 F = fresnelSchlick(F0, max(0.0, dot(Lh, Lo)));

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
  float3 ambientLight = 0;
   /*{
        float3 irradiance = texIrradiance.Sample(samLinear, N).rgb;

        float3 F = fresnelSchlick(F0, cosLo);

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
        ambientLight = diffuseIBL + specularIBL;

    }*/

  // Final fragment color.
    return float4(directLight + ambientLight, 1.0);
}