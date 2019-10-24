
Texture2D text : register(t0);

sampler samLinear : register(s0);

struct PS_INPUT 
{
   float4 Position : SV_POSITION;
   float2 TexCoord : TEXCOORD0;
};

float4 PS(PS_INPUT Input) : SV_Target
{
  return float4(text.Sample(samLinear, Input.TexCoord));
}