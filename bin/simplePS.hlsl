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

  float3 normal = (2.0f * normalTex.Sample(samLinear, input.Tex)) - 1.0f;
  normal = normalize(mul(normal, input.TBN));
  
  //Difuse
  float3 dirLight = normalize(lightPos - input.Pos);
  float diffIncidence = saturate(dot(dirLight, normal));

  //Specular
  float3 dirView = normalize(viewPos.xyz - input.Pos);
  float3 Ref = normalize(reflect(dirLight, normal));

  float SpecIncidence = max(0.0f, dot(dirView, Ref));
  SpecIncidence = pow(SpecIncidence, 5.5f);

  //Blinn Spec Incidence
  float3 H = normalize(dirLight + dirView);
  float BlinnIncidence = max(0.0f, dot(dirView, H));
  BlinnIncidence = pow(BlinnIncidence, 5.5f);

  
  float4 Diffusecolor = albedoTex.Sample( samLinear, input.Tex );

  float RefV = normalize(reflect(-dirView, normal));
  
  //Output.Position = input.Pos;
  Output.Color = Diffusecolor;
  Output.Normal = float4(normal, 1.0f);

  finalColor = (Diffusecolor);
  return Output;

}