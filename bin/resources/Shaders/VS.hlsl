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
};

PS_INPUT VS( VS_INPUT Input )
{
   PS_INPUT Output = (PS_INPUT)0;
   
   float4 worldPosition;
   float fNearClipPlane = 0.01f;
   float fFarClipPlane = 9000.0f;
   
   Input.Position.w = 1.0f;

   Output.Position = mul(Input.Position, World);
   Output.Position = mul(Output.Position, View);
   Output.Position = mul(Output.Position, Projection);
  
   Output.TexCoord = Input.TexCoord;
   return Output;

}

