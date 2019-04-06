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

  class Material {
  public:
    Material() = default;
    ~Material() = default;

    Texture*
      getTextureOfType(kraTextureType::E texType);

    void
      setTextureOfType(kraTextureType::E texType, Texture* tex);

  private:

    Texture* m_baseColor;
    Texture* m_metalness;
    Texture* m_specular;
    Texture* m_roughness;
    Texture* m_emissive;
    Texture* m_Normal;
    Texture* m_ambientO;

  };
}