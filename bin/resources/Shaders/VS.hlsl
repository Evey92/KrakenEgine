cbuffer cbMain : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
};

struct VS_INPUT 
{
   float4 Position : POSITION;
   float2 TexCoord : TEXCOORD;
    float3 Normal   : NORMAL;
    float3 Binormal : BINORMAL;
    float3 Tangent  : TANGENT;
};

struct PS_INPUT 
{
   float4 Position : SV_POSITION;
   float2 TexCoord : TEXCOORD0;
   float3 PosWorld : TEXCOORD1;
   float3x3 TBN    : TEXCOORD2;
};

PS_INPUT VS( VS_INPUT Input )
{
   PS_INPUT Output;

  Output.Position = mul(Input.Position, World);
  Output.PosWorld = Output.Position.xyz;
  Output.Position = mul(Output.Position, View);
  Output.Position = mul(Output.Position, Projection);

  Output.TexCoord = Input.TexCoord;
  Output.TBN = float3x3(Input.Tangent, Input.Binormal, Input.Normal);

  Output.TBN = mul(Output.TBN, (float3x3) World);


  return (Output);

}

