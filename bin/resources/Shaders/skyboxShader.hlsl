TextureCube enviroMap : register(t0);
SamplerState samLinear : register(s0);

cbuffer cbMain : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    matrix skyProjection;

};

struct VS_INPUT
{
    float3 Position : POSITION;
};

struct PS_INPUT
{
    float4 Position : SV_Position;
    float3 TexCoord : TEXCOORD;
};

PS_INPUT VS(VS_INPUT Input)
{
    PS_INPUT Output;

    Output.TexCoord = Input.Position;
    Output.Position = mul(skyProjection, float4(Input.Position, 1.0));
    return Output;
}

float4 PS(PS_INPUT Input) : SV_Target
{
    return enviroMap.SampleLevel(samLinear, normalize(Input.TexCoord), 0);
}