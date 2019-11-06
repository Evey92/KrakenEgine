#pragma once
#include <kraVector4.h>

#include "kraPrerequisitesCore.h"
#include "kraGameObject.h"

namespace kraEngineSDK {
  class Texture;
  class Device;
  class Vector2;
  class Vector3;

  class KRA_CORE_EXPORT Material :
  public Component {

    CLASS_DECLARATION(Material)

   public:
    
     Material(GameObject* owner)
       : Component(owner) {}

    ~Material() = default;

    void
    initialize(Device& pDevice);

    ShrdPtr<Texture>
    getAlbedoTex();

    ShrdPtr<Texture>
    getNormalTex();

    ShrdPtr<Texture>
    getMetalTex();

    ShrdPtr<Texture>
    getRoughnessTex();
    
    Vector<ShrdPtr<Texture>>
    getTextureVector();

    void
    setAlbedoTex(Device& pDevice, ShrdPtr<Texture> tex);
    
    void
    setNormalTex(Device& pDevice, ShrdPtr<Texture> tex);

    void
    setMetalTex(Device& pDevice, ShrdPtr<Texture> tex);

    void
    setRoughnessTex(Device& pDevice, ShrdPtr<Texture> tex);

    void
    setEmmisiveTex(Device& pDevice, ShrdPtr<Texture> tex);

    void
    setAmbientTex(Device& pDevice, ShrdPtr<Texture> tex);

    bool
    useBaseColor();

    ShrdPtr<Texture> m_texColorMap = nullptr;
    ShrdPtr<Texture> m_texNormalMap = nullptr;
    ShrdPtr<Texture> m_texMetallicMap = nullptr;
    ShrdPtr<Texture> m_texRoughnessMap = nullptr;
    ShrdPtr<Texture> m_texEmissiveMap = nullptr;
    ShrdPtr<Texture> m_texAOMap = nullptr;
    Vector4 m_baseColor = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
    Vector4 m_emissive = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    Vector2 m_UVOffset = Vector2(0.0f, 0.0f);
    Vector2 m_UVScale = Vector2(1.0f, 1.0f);
    float m_emissiveIntensity = 0.0f;
    float m_metallic = 0.0f;
    float m_roughness = 0.330f;
    bool m_useBaseColor = false;
    bool m_useNormalMap = false;
    bool m_useMetallicMap = false;
    bool m_useRoughnessMap = false;
    bool m_useEmissiveMap = false;
    bool m_useAOMap = false;
  };
}
