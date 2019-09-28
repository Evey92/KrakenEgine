
cbuffer ConstantBuffer : register( b0 )
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
   float3x3 TBN    : TEXCOORD1;
   //float4 Depth    : TEXCOORD4;

};

PS_INPUT VS( VS_INPUT Input )
{
  PS_INPUT Output = (PS_INPUT)0;
   
   float4 worldPosition;
   float fNearClipPlane = 0.01f;
   float fFarClipPlane = 1000.0f;
   
   Input.Position.w = 1.0f;

   Output.Position = mul(Input.Position, World);
   Output.Position = mul(Output.Position, View);
   Output.Position = mul(Output.Position, Projection);
  
   Output.TexCoord = Input.TexCoord;
  
   Output.TBN[0] = normalize(mul(Input.Tangent, World));
   Output.TBN[1] = normalize(mul(Input.BiNormal, World));
   Output.TBN[2] = normalize(mul(Input.Normal, World));
   
   //Output.Depth = (Output.Position.z - fNearClipPlane) / (fFarClipPlane - fNearClipPlane);

   return Output;

}

