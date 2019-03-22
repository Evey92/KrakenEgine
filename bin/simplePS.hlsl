Texture2D texture1 : register( t0 );
Texture2D texture2 : register( t1 );
Texture2D texture3 : register( t2 );
Texture2D texture4 : register( t3 );
Texture2D texture5 : register( t4 );

SamplerState samLinear : register( s0 );

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;

};

struct PS_OUTPUT
{

};

float4 PS(PS_INPUT input) : SV_TARGET
{
  float4 color;
  color = texture1.Sample( samLinear, input.Tex );
  
  return color;

}