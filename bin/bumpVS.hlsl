cbuffer cbMain : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
};

struct VS_INPUT 
{
   float4 Position : POSITION;
   float2 TexCoord : TEXCOORD0;
   float3 Normal   : NORMAL;
   float3 Tangent  : TANGENT;
   float3 BiNormal : BINORMAL;

};

struct PS_INPUT 
{
   float4 Position : SV_POSITION;
   float2 TexCoord : TEXCOORD0;
   float3 normal   : NORMAL;
   float3 tangent  : TANGENT;
   float3 binormal : BINORMAL;
};

PS_INPUT VS( VS_INPUT Input )
{
   PS_INPUT Output;
   
   Input.Position.w = 1.0f;

   Output.Position = mul(Input.Position, World);
   Output.Position = mul(Output.Position, View);
   Output.Position = mul(Output.Position, Projection);
  
   Output.TexCoord = Input.TexCoord;

   Output.normal = normalize(mul(Input.Normal, (float3x3)World));
   Output.tangent = normalize(mul(Input.Tangent, (float3x3)World));
   Output.binormal = normalize(mul(Input.BiNormal, (float3x3)World));

   return Output;

}

