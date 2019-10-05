#include "gBufferCommons.hlsl"

struct PS_OUTPUT
{
  float4 Position : SV_Target0;
  float4 Albedo   : SV_Target1;
  float4 Normal   : SV_Target2;
  float3 Effects  : SV_Target3;
};

float calculateDepth(float depth);

PS_INPUT VS(VS_INPUT Input)
{
  PS_INPUT Output;

  Output.Position = mul(Input.Position, matWorld);
  Output.WorldPosition = Output.Position.xyz;
  Output.Position = mul(Output.Position, matView);
  Output.Position = mul(Output.Position, matProjection);

  Output.TexCoord = Input.TexCoord;
  Output.TBN = float3x3(Input.Tangent, Input.Binormal, Input.Normal);

  Output.TBN = mul(Output.TBN, (float3x3) matWorld);


  return (Output);

}

PS_OUTPUT PS(PS_INPUT Input) : SV_Target
{
  PS_OUTPUT Output = (PS_OUTPUT)0;

  float3 normal = normalize(texAlbedo.Sample(samLinear, Input.TexCoord).rgb * 2.0f - 1.0f);
  normal.g = -normal.g; //Just in case normal map was made with DX3D coordinates

  Output.Position = Input.PosWorld;
  Output.Albedo.rgb = texAlbedo.Sample(samLinear, Input.TexCoord);
  Output.Albedo.a = texRoughness.Sample(samLinear, Input.TexCoord);
  Output.Normal.rgb = normalize(mul(normal, Input.TBN));
  Output.Normal.a = texMetalness.Sample(samLinear, Input.TexCoord);
  Output.Effects = float3();
}

float calculateDepth(float depth)
{
    float z = depth * 2.0f - 1.0f;
    return (2.0f * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}