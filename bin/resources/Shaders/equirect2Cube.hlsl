struct VS_INPUT 
{
   float4 Position : POSITION;
   float2 TexCoord : TEXCOORD0;
};

struct PS_INPUT 
{
   float4 Position : SV_POSITION;
   float2 TexCoord : TEXCOORD0;
};

PS_INPUT VS( VS_INPUT Input )
{
   PS_INPUT Output = (PS_INPUT)0;

   Output.Position = float4(Input.Position.x, -Input.Position.y, Input.Position.z, Input.Position.w);  
   Output.TexCoord = Input.TexCoord;
   
   return Output;

}

