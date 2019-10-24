#include "gBufferCommons.hlsl"

float3 m_lightPos;
float4 m_eyePos;

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