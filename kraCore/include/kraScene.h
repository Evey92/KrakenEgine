#pragma once
#include "kraPrerequisitesCore.h"
#include "kraSceneGraph.h"

namespace kraEngineSDK {
  
  class GameObject;

  class KRA_CORE_EXPORT Scene
  {
   public:
     
     Scene(int buildIndex, String name = "SampleScene")
     : m_buildIndex(buildIndex), m_name(name) {}
     
     Scene(String name)
     : m_name(name) {}

    ~Scene() = default;

    
#pragma region PUBLIC_METHODS
    void
    initialize();

    void
    addNode(const ShrdPtr<GameObject>& node, int id);
    
    void
    addNewNode(const ShrdPtr<GameObject>& GO);


#pragma endregion PUBLIC_METHODS

#pragma region PRIVATE_MEMBERS
    
    ShrdPtr<SceneGraph> m_sceneGraph = nullptr;

#pragma endregion PRIVATE_MEMBERS

#pragma region PUBLIC_MEMBERS

    int m_buildIndex = 0;
    int m_nodes = 0;
    String m_name;
    String m_path;
    bool m_isDirty = true;
    bool m_isLoaded = false;
#pragma endregion PUBLIC_MEMBERS
  };
}
