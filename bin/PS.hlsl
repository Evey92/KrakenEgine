Texture2D txDiffuse : register( t0 );
Texture2D txNormal : register(t1);

SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register(b1)
{
  float4 viewPos;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
    float3x3 TBN: TEXCOORD1;

};

struct PS_OUTPUT
{
  float4 Position : SV_TARGET0;
  float4 Normal   : SV_TARGET0;
  float4 Color    : SV_TARGET0;
};

PS_OUTPUT PS(PS_INPUT input) : SV_TARGET
{
  PS_OUTPUT Output = (PS_OUTPUT)0;

  float4 Diffusecolor = txDiffuse.Sample(samLinear, input.Tex);
  float4 normal = txNormal.Sample(samLinear, input.Tex);

  Output.Position = input.Pos;
  Output.Color = Diffusecolor;
  Output.Normal = normal;

  return Output;
}