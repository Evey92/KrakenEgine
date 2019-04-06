#include "kraMaterial.h"
#include "kraTexture.h"
#include "kraDevice.h"

namespace kraEngineSDK {

  Material::Material(Device& pDevice) {
    m_baseColor = pDevice.createTextureInstance();
    m_metalness = pDevice.createTextureInstance();
    m_specular = pDevice.createTextureInstance();
    m_roughness = pDevice.createTextureInstance();
    m_emissive = pDevice.createTextureInstance();
    m_Normal = pDevice.createTextureInstance();
    m_ambientO = pDevice.createTextureInstance();
  }

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
  Material::setTextureOfType(Device& pDevice, kraTextureType::E texType, Texture* tex, std::string fileName)
  {
    switch (texType)
    {
    case kraTextureType::BASECOLOR:
      *this->m_baseColor = *tex;
      //m_baseColor->createTexture2DFromFile(pDevice, fileName);
      break;
    case kraTextureType::METALNESS:
      m_metalness->createTexture2DFromFile(pDevice, fileName);
      break;
    case kraTextureType::SPECULAR:
      m_specular->createTexture2DFromFile(pDevice, fileName);
      break;
    case kraTextureType::ROUGHNESS:
      m_roughness->createTexture2DFromFile(pDevice, fileName);
      break;
    case kraTextureType::EMISSIVE:
      m_emissive->createTexture2DFromFile(pDevice, fileName);
      break;
    case kraTextureType::NORMAL:
      m_Normal->createTexture2DFromFile(pDevice, fileName);
      break;
    case kraTextureType::AMBIENT:
      m_ambientO->createTexture2DFromFile(pDevice, fileName);
      break;
    }
  }

}