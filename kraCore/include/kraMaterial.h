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
    setTextureOfType(Device& pDevice, kraTextureType::E texType, Texture* tex, std::string fileName);

  public:

    Texture* m_baseColor;
    Texture* m_metalness;
    Texture* m_specular;
    Texture* m_roughness;
    Texture* m_emissive;
    Texture* m_Normal;
    Texture* m_ambientO;

  };
}