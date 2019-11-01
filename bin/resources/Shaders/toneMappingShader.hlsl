#include "Commons.hlsl"

Texture2D texAlbedo : register(t0);
SamplerState samLinear : register(s0);

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

PS_INPUT VS(uint vertID : SV_VertexID)
{
    PS_INPUT Output;

    if (vertID == 0) {
        Output.Position = float4(1.0f, 3.0f, 0.0f, 1.0f);
        Output.TexCoord = float2(1.0f, -1.0f);

    }
    else if (vertID == 1) {
        Output.Position = float4(-3.0f, -1.0f, 0.0f, 1.0f);
        Output.TexCoord = float2(-1.0f, 1.0f);
    }
    else {
        Output.Position = float4(1.0f, -1.0f, 0.0f, 1.0f);
        Output.TexCoord = float2(1.0f, 1.0f);
    }

    return Output;
}

float4 PS(PS_INPUT Input) : SV_Target
{
    float3 albedo = texAlbedo.Sample(samLinear, Input.TexCoord).rgb * exposure;

    // Reinhard tonemapping operator.
    float luminance = dot(albedo, float3(0.2126, 0.7152, 0.0722));
    float mappedLuminance = (luminance * (1.0 + luminance / (pureWhite * pureWhite))) / (1.0 + luminance);

    float3 mappedColor = (mappedLuminance / luminance) * albedo;

    return float4(pow(abs(mappedColor), 1.0 / gamma), 1.0);

}