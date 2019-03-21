cbuffer cbMain : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
};

struct VS_INPUT 
{
  float4 Position : POSITION0;
  float2 TexCoord : TEXCOORD0;
  float3 Normal   : NORMAL0;
  float3 Tangent  : TANGENT0;
  float3 BiNormal : BINORMAL0;

};

struct PS_INPUT 
{
   float4 Position : SV_POSITION;
   float3 WorldPos : TEXCOORD0;
   float2 TexCoord : TEXCOORD1;
   float3x3 TBN    : TEXCOORD2;
   float4 Depth    : TEXCOORD5;
};

PS_INPUT VS( VS_INPUT Input )
{
   PS_INPUT Output = (PS_INPUT)0;

   float angle = 0;
   float4x4 matRot = { cos(angle),0,sin(angle),0,
                      0,         1,   0,      0,
                     -sin(angle),0,cos(angle),0,
                      0,         0,   0,      1 };

   float4x4 matTrans = mul(World, matRot);

   float4 tmpPosW = mul(Input.Position, matTrans);
   Output.WorldPos = tmpPosW.xyz;
   Output.Position = mul(tmpPosW, View);
   Output.Position = mul(tmpPosW, Projection);
   Output.TexCoord = float2(Input.TexCoord.x, 1.0f - Input.TexCoord.y);

   Output.TBN[0] = normalize(mul(float4(Input.Tangent, 0.0f), matTrans));
   Output.TBN[1] = normalize(mul(float4(Input.BiNormal, 0.0f), matTrans));
   Output.TBN[2] = normalize(mul(float4(Input.Normal, 0.0f), matTrans));

   Output.Depth = (Output.Position.z - 0.01f) / (1000.0f - 0.0f);
   return Output;

}

