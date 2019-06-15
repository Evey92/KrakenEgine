#define m_PI  3.141592653f
#define Epsilon 0.00000000001f

float ndfGGX(float cosLH, float roughness )
{
  float alpha = roughness * roughness;
  float alphaSQ = alpha * alpha;

  float denom = (cosLH * cosLH) * (alphaSQ - 1.0) + 1.0;

  return alphaSQ / (m_PI * denom * denom);
}

float kraSchlickG1(float cosTheta, float k)
{
  return cosTheta / (cosTheta * (1.0 - k) + k);
}

float kraShlickGGX(float cosLi, float cosLo, float roughness)
{
  float r = roughness + 1.0;
  float k = (r * r) / 8.0;

  return kraSchlickG1(cosLi, k) * kraSchlickG1(cosLo, k);
}

float3 fresnelShlick(float3 F0, float cosTheta)
{
  return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

sampler AlbedoSampler;
sampler MetalnessSampler;
sampler RoughnessSampler;
sampler NormalSampler;
sampler EmissiveSampler;
sampler IrradianceSampler;

float3 m_lightPos;
float4 m_eyePos;

struct PS_INPUT
{
  float3 PosWorld : TEXCOORD0;
  float2 TexCoord : TEXCOORD1;
  float3x3 TBN    : TEXCOORD2;
  float4 Depth    : TEXCOORD5;
};

struct PS_OUTPUT
{
  float4 Position  : COLOR0;
  float4 Normal    : COLOR1;
  float4 Color     : COLOR2;
  float4 Depth     : COLOR3;
};

float3 fresnelShlcik(float3 F0, float cosTheta)
{
  return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float4 ps_main(PS_INPUT Input) : COLOR0
{
  float Fdielectric = 0.03;

  float4 albedo = tex2D(AlbedoSampler, Input.TexCoord);
  float3 normal = tex2D(NormalSampler, Input.TexCoord);
  float metalness = tex2D(MetalnessSampler, Input.TexCoord);
  float roughness = tex2D(RoughnessSampler, Input.TexCoord);

  normal = 2.0f * mul(normal, Input.TBN) - 1.0f;
  normal = normalize(normal);


  float3 lightDir = normalize(m_lightPos - Input.PosWorld);
  float3 viewDir = normalize(m_eyePos.xyz - Input.PosWorld);
  float3 h = normalize(lightDir + viewDir);

  float NdL = max(0.0, dot(normal, lightDir));
  float NdH = max(0.0, dot(normal, h));
  float NdV = max(0.0, dot(normal, viewDir));

  float3 F0 = lerp(Fdielectric, albedo, metalness);

  float3 F = fresnelShlick(F0, max(0.0f, 1.0f));
  float D = ndfGGX(NdH, roughness);
  float G = kraShlickGGX(NdL, NdV, roughness);

  float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metalness);
  float3 diffuseBRDF = kd * albedo;
  float3 specularBRDF = (F * G * D) / max(Epsilon, 4.0 * NdL * NdV);

  float3 directLight = (diffuseBRDF + specularBRDF)  * NdL;

  float3 ambientLight;
  {
    float3 irradiance = texCUBE(IrradianceSampler, normal).rgb;
    float3 F = fresnelShlick(F0, NdV);
    float3 kd = lerp(1.0f - F, 0.0f, metalness);

    float3 diffuseBRDF = kd * albedo * irradiance;

    ambientLight = diffuseBRDF;

  }

  return float4(ambientLight, 1);
}