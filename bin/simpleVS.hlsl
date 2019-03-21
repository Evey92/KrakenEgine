
cbuffer ConstantBuffer : register( b0 )
{
    matrix World;
    matrix View;
    matrix Projection;
};
struct VS_INPUT 
{
   float4 Position : POSITION0;
   float4 TexCoord : TEXCOORD0;

};

struct VS_OUTPUT 
{
   float4 Position : SV_POSITION;
   float2 TexCoord: TEXCOORD0;

};

VS_OUTPUT VS( VS_INPUT Input )
{
   VS_OUTPUT Output = (VS_OUTPUT)0;
   Output.Position = mul(Input.Position, World);
   Output.Position = mul(Output.Position, View);
   Output.Position = mul(Output.Position, Projection);
   Output.TexCoord = Input.TexCoord;
   return Output ;

}

