Texture2D Texture1 : register( t0 );


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
  color = Texture1.Sample( samLinear, input.Tex );
  
  return color;

}