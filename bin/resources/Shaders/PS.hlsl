Texture2D txDiffuse : register(t0);

SamplerState samLinear : register(s0);

PS_OUTPUT PS(PS_INPUT input) : SV_Target
{
  return = float4(txDiffuse.Sample( samLinear, input.texCoord));
}