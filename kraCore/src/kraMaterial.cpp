#include "kraMaterial.h"
#include "kraTexture.h"

namespace kraEngineSDK {

  Texture*
  Material::getTextureOfType(kraTextureType::E texType)
  {

    switch (texType)
    {
    case kraTextureType::BASECOLOR:
      return m_baseColor;
      break;
    case kraTextureType::METALNESS:
      return m_metalness;
      break;
      case kraTextureType::SPECULAR:
        return m_specular;
      break;
      case kraTextureType::ROUGHNESS:
        return m_roughness;
      break;
    case kraTextureType::EMISSIVE:
      return m_emissive;
      break;
    case kraTextureType::NORMAL:
      return m_Normal;
      break;
    case kraTextureType::AMBIENT:
      return m_ambientO;
      break;
    }
  }

  void
  Material::setTextureOfType(kraTextureType::E texType, Texture* tex)
  {
    switch (texType)
    {
    case kraTextureType::BASECOLOR:
      m_baseColor = tex;
      break;
    case kraTextureType::METALNESS:
      m_metalness = tex;
      break;
    case kraTextureType::SPECULAR:
      m_specular = tex;
      break;
    case kraTextureType::ROUGHNESS:
      m_roughness = tex;
      break;
    case kraTextureType::EMISSIVE:
      m_emissive = tex;
      break;
    case kraTextureType::NORMAL:
      m_Normal = tex;
      break;
    case kraTextureType::AMBIENT:
      m_ambientO = tex;
      break;
    }
  }

}