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
    float3 Position : POSITION;
    float4 WorldPosition : SV_Position;
};

PS_INPUT VS(VS_INPUT Input)
{
    PS_INPUT Output;

    Output.Position = Input.Position;
    float4x4 viewProjMat = mul(View, Projection);
    Output.WorldPosition = mul(viewProjMat, float4(Input.Position, 1.0));

    return Output;
}

float4 PS(PS_INPUT Input) : SV_Target
{
    float3 envVector = normalize(Input.Position);
    return enviroMap.SampleLevel(samLinear, envVector, 0);
}