#pragma once
#include "kraPrerequisitesCore.h"


namespace kraEngineSDK {
  

  class Texture;
  class Device;

  class KRA_CORE_EXPORT Material {
  public:
    Material(Device& pDevice);
    ~Material() = default;

    ShrdPtr<Texture>
    getTextureOfType(kraTextureType::E texType);

    void
    setTextureOfType(Device& pDevice, kraTextureType::E texType, std::string fileName);

  public:

    ShrdPtr<Texture> m_texColorMap = nullptr;
    ShrdPtr<Texture> m_texNormalMap = nullptr;
    ShrdPtr<Texture> m_texMetallicMap = nullptr;
    ShrdPtr<Texture> m_texRoughnessMap = nullptr;
    ShrdPtr<Texture> m_texEmissiveMap = nullptr;
    ShrdPtr<Texture> m_texAOMap = nullptr;
    Vector4 m_baseColor;
    Vector4 m_emissive;
    Vector2 m_UVOffset;
    Vector2 m_UVScale;
    float m_emissiveIntensity;
    float m_metallic;
    float m_roughness;
    bool m_useBaseColor;
    bool m_useNormalMap;
    bool m_useMetallicMap;
    bool m_useRoughnessMap;
    bool m_useEmissiveMap;
    bool m_useAOMap;
  };
}