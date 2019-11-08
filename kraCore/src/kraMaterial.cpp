#include "kraGraphicsAPI.h"
#include "kraMaterial.h"
#include "kraTexture.h"
#include "kraDevice.h"

namespace kraEngineSDK {

  CLASS_DEFINITION(Component, Material)

  void 
  Material::initialize(Device& pDevice)
  {
    m_texColorMap = pDevice.createTextureInstance();
    m_texNormalMap = pDevice.createTextureInstance();
    m_texMetallicMap = pDevice.createTextureInstance();
    m_texRoughnessMap = pDevice.createTextureInstance();
    m_texEmissiveMap = pDevice.createTextureInstance();
    m_texAOMap = pDevice.createTextureInstance();

    m_texColorMap->createTexture2DFromFile()

    /*m_texColorMap.createTexture2DFromFile(pDevice,
                                           "resources/Textures/default.png",
                                           GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT,
                                           GFX_USAGE::E::kUSAGE_DEFAULT,
                                           CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                           1);*/
  }

  ShrdPtr<Texture*> 
  Material::getAlbedoTex()
  {
    return m_texColorMap;
  }

  ShrdPtr<Texture*> 
  Material::getNormalTex()
  {
    return m_texNormalMap;

  }

  ShrdPtr<Texture*> 
  Material::getMetalTex()
  {
    return m_texMetallicMap;

  }

  ShrdPtr<Texture*> 
  Material::getRoughnessTex()
  {
    return m_texRoughnessMap;

  }

  Vector<ShrdPtr<Texture*>> 
  Material::getTextureVector()
  {
    Vector<ShrdPtr<Texture*>> retVec;

    retVec.push_back(m_texColorMap);
    retVec.push_back(m_texNormalMap);
    retVec.push_back(m_texMetallicMap);
    retVec.push_back(m_texRoughnessMap);      
      
    return retVec;
  }

  void
  Material::setAlbedoTex(Device& pDevice, const Texture& tex)
  {
    m_texColorMap = make_shared<Texture*>(tex);

  }

  void 
  Material::setNormalTex(Device& pDevice, const Texture& tex)
  {
    m_texNormalMap = make_shared<Texture*>(tex);

  }

  void 
  Material::setMetalTex(Device& pDevice, const Texture& tex)
  {
    m_texMetallicMap = make_shared<Texture*>(tex);
  }

  void 
  Material::setRoughnessTex(Device& pDevice, const Texture& tex)
  {
    m_texRoughnessMap = make_shared<Texture*>(tex);
  }

  bool
  Material::useBaseColor() {
    
    if (m_texColorMap != nullptr) {
     return true;
    }

    return false;

  }

}