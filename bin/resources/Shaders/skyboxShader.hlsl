TextureCube enviroMap : register(t0);
SamplerState samLinear : register(s0);

cbuffer cbMain : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

struct VS_INPUT
{
    float3 Position : POSITION;
    float3 TexCoord : TEXCOORD;
};

struct PS_INPUT
{
    float4 Position : SV_Position;
    float3 TexCoord : TEXCOORD;
};

PS_INPUT VS(VS_INPUT Input)
{
    PS_INPUT Output;

    float3 pos = mul(Input.Position.xyz, (float3x3) View);
    Output.Position = mul(float4(pos, 1.0f), Projection);
    Output.TexCoord = Input.TexCoord;

    return Output;
}

float4 PS(PS_INPUT Input) : SV_Target
{
    
    float3 albedo = enviroMap.Sample(samLinear, normalize(Input.TexCoord)).rgb;

    return float4(albedo, 0.0f);

}