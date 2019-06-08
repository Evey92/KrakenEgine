#pragma once
#include "kraPrerequisitesCore.h"


namespace kraEngineSDK {
  namespace kraTextureType {
    enum E
    {
      BASECOLOR,
      METALNESS,
      SPECULAR,
      ROUGHNESS,
      EMISSIVE,
      NORMAL,
      AMBIENT,

    };
  }

  class Texture;
  class Device;

  class KRA_CORE_EXPORT Material {
  public:
    Material(Device& pDevice);
    ~Material() = default;

    Texture*
    getTextureOfType(kraTextureType::E texType);

    void
    setTextureOfType(Device& pDevice, kraTextureType::E texType, std::string fileName);

  public:

    Texture* m_baseColor = nullptr;
    Texture* m_metalness = nullptr;
    Texture* m_specular = nullptr;
    Texture* m_roughness = nullptr;
    Texture* m_emissive = nullptr;
    Texture* m_Normal = nullptr;
    Texture* m_ambientO = nullptr;

  };
}