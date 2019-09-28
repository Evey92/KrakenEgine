Texture2D albedoTex: register( t0 );
Texture2D normalTex: register( t1 );

SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register(b1)
{
  float4 viewPos;
};

struct PS_INPUT
{
    float4 Pos   : SV_POSITION;
    float2 Tex   : TEXCOORD0;
    float3x3 TBN : TEXCOORD1;
};

struct PS_OUTPUT
{
  //float4 Position : SV_TARGET0;
  float4 Color    : SV_TARGET0;
  float4 Normal   : SV_TARGET1;
};

PS_OUTPUT PS(PS_INPUT input) : SV_TARGET
{
  PS_OUTPUT Output = (PS_OUTPUT)0;
  float3 lightPos = float3(100.0f, 0.0f, 100.0f);
  float4 finalColor;
  float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

  float4 Diffusecolor = albedoTex.Sample( samLinear, input.Tex );

  float3 normal = (2.0f * normalTex.Sample(samLinear, input.Tex)) - 1.0f;
  normal = normalize(mul(normal, input.TBN));
  
  //Difuse
  float3 dirLight = normalize(lightPos - input.Pos);
  dirLight = -dirLight;
  
  float diffIncidence = saturate(dot(dirLight, normal));

 finalColor = saturate(lightColor * diffIncidence);
  
  finalColor = finalColor * Diffusecolor;
  
  //Output.Position = input.Pos;
  Output.Color = finalColor;
  return Output;

}