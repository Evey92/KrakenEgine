#include "kraMaterial.h"
#include "kraTexture.h"
#include "kraDevice.h"
#include "kraGraphicsAPI.h"

namespace kraEngineSDK {

  CLASS_DEFINITION(Component, Material)

  void 
  Material::initialize()
  {
    m_texColorMap = GraphicsAPI::instance().getDevice()->createTextureInstance();
    m_texNormalMap = GraphicsAPI::instance().getDevice()->createTextureInstance();
    m_texMetallicMap = GraphicsAPI::instance().getDevice()->createTextureInstance();
    m_texRoughnessMap = GraphicsAPI::instance().getDevice()->createTextureInstance();
    m_texEmissiveMap = GraphicsAPI::instance().getDevice()->createTextureInstance();
    m_texAOMap = GraphicsAPI::instance().getDevice()->createTextureInstance();
  }

  ShrdPtr<Texture>
  Material::getTextureOfType(TEXTURE_TYPE::E texType)
  {

    switch (texType)
    {
    case TEXTURE_TYPE::E::BASECOLOR:
      return m_texColorMap;
      break;
    case TEXTURE_TYPE::E::METALNESS:
      return m_texMetallicMap;
      break;
      case TEXTURE_TYPE::E::ROUGHNESS:
        return m_texRoughnessMap;
      break;
    case TEXTURE_TYPE::E::EMISSIVE:
      return m_texEmissiveMap;
      break;
    case TEXTURE_TYPE::E::NORMAL:
      return m_texNormalMap;
      break;
    case TEXTURE_TYPE::E::AMBIENT:
      return m_texAOMap;
      break;
    }
  }

  void
  Material::setTextureOfType(Device& pDevice, TEXTURE_TYPE::E texType, std::string fileName)
  {
    switch (texType)
    {
    case TEXTURE_TYPE::E::BASECOLOR:
      //m_texColorMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case TEXTURE_TYPE::E::METALNESS:
      //m_texMetallicMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case TEXTURE_TYPE::E::ROUGHNESS:
      //m_texRoughnessMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case TEXTURE_TYPE::E::EMISSIVE:
      //m_texEmissiveMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case TEXTURE_TYPE::E::NORMAL:
      //m_texNormalMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    case TEXTURE_TYPE::E::AMBIENT:
      //m_texAOMap->createTexture2DFromFile(pDevice, fileName, GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT);
      break;
    }
  }

  void Material::setAlbedoTex(Device& pDevice, ShrdPtr<Texture> tex)
  {
    m_texColorMap = tex;
  }

  void Material::setNormalTex(Device& pDevice, ShrdPtr<Texture> tex)
  {
    m_texNormalMap = tex;

  }

  void Material::setMetalTex(Device& pDevice, ShrdPtr<Texture> tex)
  {
    m_texMetallicMap = tex;
  }

}