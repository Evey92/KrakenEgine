Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
Texture2D specNormal : register(t2);

SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register(b1)
{
  float4 viewPos;
};

struct PS_INPUT 
{
   float4 Position : SV_POSITION;
   float2 texCoord : TEXCOORD0;
   float3 mLightDir : TEXCOORD1;
   float3 mviewDir  : TEXCOORD2;
   float3 normal   : NORMAL;
   float3 tangent  : TANGENT;
   float3 binormal : BINORMAL;
};

float4 PS(PS_INPUT input) : SV_TARGET
{
  float4 finalColor;
  float3 lightDirection = float3(0.0f, 0.0f, 1.0f);
  float3 lightDir;
  float lightIntensity;
  float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

  float4 Diffusecolor = txDiffuse.Sample( samLinear, input.texCoord);
  float4 normalMap = txNormal.Sample(samLinear, input.texCoord);
  
  normalMap = (normalMap * 2.0f) - 1.0f;

  float3x3 TBN = float3x3(normalize(input.tangent), normalize(input.binormal), normalize(input.normal));

  TBN = transpose(TBN);

  float3 worldNormal = mul(TBN, normalMap);

  lightDir = normalize(lightDirection);
  float3 diffuse = saturate(dot(worldNormal, -lightDir));

  diffuse = lightColor * Diffusecolor.rgb * diffuse;

  float3 specular = 0;

  if(diffuse.x > 0)
  {
    float3 reflection = reflect(lightDir, worldNormal);
    float3 viewDir = normalize(viewPos);
  }


  float3 ambient = float3(1.0f, 1.0f, 1.0f) * Diffusecolor;

  return float4(ambient + diffuse, 1);

 }