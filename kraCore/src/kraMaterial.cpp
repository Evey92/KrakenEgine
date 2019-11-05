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
  Material::getAlbedoTex()
  {
    return m_texColorMap;
  }

  ShrdPtr<Texture> 
  Material::getNormalTex()
  {
    return m_texNormalMap;

  }

  ShrdPtr<Texture> 
  Material::getMetalTex()
  {
    return m_texMetallicMap;

  }

  ShrdPtr<Texture> 
  Material::getRoughnessTex()
  {
    return m_texRoughnessMap;

  }

  Vector<ShrdPtr<Texture>> 
  Material::getTextureVector()
  {
    Vector<ShrdPtr<Texture>> retVec;

    retVec.push_back(m_texColorMap);
    retVec.push_back(m_texNormalMap);
    retVec.push_back(m_texMetallicMap);
    retVec.push_back(m_texRoughnessMap);      
      
    return retVec;
  }

  void
  Material::setAlbedoTex(Device& pDevice, ShrdPtr<Texture> tex)
  {
    m_texColorMap = tex;
  }

  void 
  Material::setNormalTex(Device& pDevice, ShrdPtr<Texture> tex)
  {
    m_texNormalMap = tex;

  }

  void 
  Material::setMetalTex(Device& pDevice, ShrdPtr<Texture> tex)
  {
    m_texMetallicMap = tex;
  }

  void 
  Material::setRoughnessTex(Device& pDevice, ShrdPtr<Texture> tex)
  {
    m_texRoughnessMap = tex;
  }

  bool
  Material::useBaseColor() {
    
    if (m_texColorMap != nullptr) {
     return true;
    }

    return false;

  }

}