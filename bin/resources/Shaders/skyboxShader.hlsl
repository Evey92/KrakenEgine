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
    float3 worldPos : POSITION;
    float4 Position : SV_Position;
};

PS_INPUT VS(VS_INPUT Input)
{
    PS_INPUT Output;

    Output.worldPos = Input.Position;
    float4x4 wvpMat = mul(World, View);
    wvpMat = mul(wvpMat, Projection);
    Output.Position = mul(float4(Input.Position, 1.0f), wvpMat);

    return Output;
}

float4 PS(PS_INPUT Input) : SV_Target
{
    
    float3 envVector = normalize(Input.worldPos);
    return enviroMap.SampleLevel(samLinear, envVector, 0);
}