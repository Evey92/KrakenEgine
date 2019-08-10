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

    ShrdPtr<Texture> m_baseColor = nullptr;
    ShrdPtr<Texture> m_metalness = nullptr;
    ShrdPtr<Texture> m_specular = nullptr;
    ShrdPtr<Texture> m_roughness = nullptr;
    ShrdPtr<Texture> m_emissive = nullptr;
    ShrdPtr<Texture> m_Normal = nullptr;
    ShrdPtr<Texture> m_ambientO = nullptr;

  };
}