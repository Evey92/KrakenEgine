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
      return m_texColorMap;
      break;
    case kraTextureType::METALNESS:
      return m_texMetallicMap;
      break;
      case kraTextureType::ROUGHNESS:
        return m_texRoughnessMap;
      break;
    case kraTextureType::EMISSIVE:
      return m_texEmissiveMap;
      break;
    case kraTextureType::NORMAL:
      return m_texNormalMap;
      break;
    case kraTextureType::AMBIENT:
      return m_texAOMap;
      break;
    }
  }

  void
  Material::setTextureOfType(Device& pDevice, kraTextureType::E texType, std::string fileName)
  {
    switch (texType)
    {
    case kraTextureType::BASECOLOR:
      m_texColorMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::METALNESS:
      m_texMetallicMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::ROUGHNESS:
      m_texRoughnessMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::EMISSIVE:
      m_texEmissiveMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::NORMAL:
      m_texNormalMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case kraTextureType::AMBIENT:
      m_texAOMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    }
  }

}