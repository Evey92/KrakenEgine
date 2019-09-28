Texture2D txDiffuse : register( t0 );
Texture2D txNormal : register(t1);

SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register(b1)
{
  float4 viewPos;
};

struct PS_INPUT
{
    float4 Pos      : SV_POSITION;
    float2 texCoord : TEXCOORD0;

};

struct PS_OUTPUT
{
  float4 Color : SV_TARGET0;
  float4 Normal    : SV_TARGET1;
};

PS_OUTPUT PS(PS_INPUT input) : SV_TARGET
{
  PS_OUTPUT Output;
  float4 Diffusecolor = txDiffuse.Sample( samLinear, input.texCoord);
  Output.Color = Diffusecolor;

  return Output;

 }