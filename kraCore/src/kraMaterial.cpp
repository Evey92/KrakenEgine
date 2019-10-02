#include "kraMaterial.h"
#include "kraTexture.h"
#include "kraDevice.h"

namespace kraEngineSDK {

  Material::Material(Device& pDevice) {

  }

  ShrdPtr<Texture>
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
  Material::setTextureOfType(Device& pDevice, kraTextureType::E texType, std::string fileName)
  {
    switch (texType)
    {
    case kraTextureType::BASECOLOR:
      m_baseColor->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::METALNESS:
      m_metalness->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::SPECULAR:
      m_specular->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::ROUGHNESS:
      m_roughness->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::EMISSIVE:
      m_emissive->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::NORMAL:
      m_Normal->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::AMBIENT:
      m_ambientO->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    }
  }

}