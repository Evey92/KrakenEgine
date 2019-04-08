
cbuffer ConstantBuffer : register( b0 )
{
    matrix World;
    matrix View;
    matrix Projection;
};
struct VS_INPUT 
{
   float4 Position : POSITION0;
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
   float4 Depth    : TEXCOORD4;

};

PS_INPUT VS( VS_INPUT Input )
{
  PS_INPUT Output = (PS_INPUT)0;
   
   float4 worldPosition;
   float fNearClipPlane = 0.01f;
   float fFarClipPlane = 1000.0f;
   Output.Position = mul(Input.Position, World);
   Output.Position = mul(Output.Position, View);
   Output.Position = mul(Output.Position, Projection);
   Output.TexCoord = Input.TexCoord;
   Output.TBN[0] = normalize(mul(float4(Input.Tangent, 0.0f), World));
   Output.TBN[1] = normalize(mul(float4(Input.BiNormal, 0.0f), World));
   Output.TBN[2] = normalize(mul(float4(Input.Normal, 0.0f), World));
   
   Output.Depth = (Output.Position.z - fNearClipPlane) / (fFarClipPlane - fNearClipPlane);

   return Output ;

}

