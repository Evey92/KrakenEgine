#include "Commons.hlsl"

static const uint samples = 1024;
static const float invSamples = 1.0 / float(samples);

RWTexture2D<float2> LUT : register(u0);

// Single term for separable Schlick-GGX below.
float gaSchlickG1(float cosTheta, float k)
{
  return cosTheta / (cosTheta * (1.0 - k) + k);
}

// Schlick-GGX approximation of geometric attenuation function using Smith's method (IBL version).
float gaSchlickGGX_IBL(float cosLi, float cosLo, float roughness)
{
  float r = roughness;
  float k = (r * r) / 2.0; // Epic suggests using this roughness remapping for IBL lighting.
  return gaSchlickG1(cosLi, k) * gaSchlickG1(cosLo, k);
}

[numthreads(32, 32, 1)]
void main(uint2 ThreadID : SV_DispatchThreadID)
{
  // Get output LUT dimensions.
  float outputWidth, outputHeight;
  LUT.GetDimensions(outputWidth, outputHeight);

  // Get integration parameters.
  float cosLo = ThreadID.x / outputWidth;
  float roughness = ThreadID.y / outputHeight;

  // Make sure viewing angle is non-zero to avoid divisions by zero (and subsequently NaNs).
  cosLo = max(cosLo, Epsilon);

  // Derive tangent-space viewing vector from angle to normal (pointing towards +Z in this reference frame).
  float3 Lo = float3(sqrt(1.0 - cosLo * cosLo), 0.0, cosLo);

  // We will now pre-integrate Cook-Torrance BRDF for a solid white environment and save results into a 2D LUT.
  // DFG1 & DFG2 are terms of split-sum approximation of the reflectance integral.
  // For derivation see: "Moving Frostbite to Physically Based Rendering 3.0", SIGGRAPH 2014, section 4.9.2.
  float DFG1 = 0;
  float DFG2 = 0;

  for (uint i = 0; i < samples; ++i) {
    float2 u = sampleHammersley(i, invSamples);

    // Sample directly in tangent/shading space since we don't care about reference frame as long as it's consistent.
    float3 Lh = sampleGGX(u.x, u.y, roughness);

    // Compute incident direction (Li) by reflecting viewing direction (Lo) around half-vector (Lh).
    float3 Li = 2.0 * dot(Lo, Lh) * Lh - Lo;

    float cosLi = Li.z;
    float cosLh = Lh.z;
    float cosLoLh = max(dot(Lo, Lh), 0.0);

    if (cosLi > 0.0) {
      float G = gaSchlickGGX_IBL(cosLi, cosLo, roughness);
      float Gv = G * cosLoLh / (cosLh * cosLo);
      float Fc = pow(1.0 - cosLoLh, 5);

      DFG1 += (1 - Fc) * Gv;
      DFG2 += Fc * Gv;
    }
  }

  LUT[ThreadID] = float2(DFG1, DFG2) * invSamples;
}