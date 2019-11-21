#pragma once
#include "kraPrerequisitesCore.h"
#include "kraTransform.h"
#include "kraComponent.h"

namespace kraEngineSDK {

  class Scene;

  class KRA_CORE_EXPORT GameObject
  {
   public:

     GameObject(Scene* scene, String name = "GameObject")
     : m_scene(scene), m_name(name), m_transform(nullptr){}

    ~GameObject() = default;

    GameObject(const GameObject&) = delete;
    GameObject& operator =(const GameObject&) = delete;

   /**
    * @brief Function to initialize the Game Object
    */
    void
    initialize(const ShrdPtr<GameObject>& thisGO);

   /**
    * @brief Function to add a new GO to children vector 
    */
    void
    addChild(const ShrdPtr<GameObject>& newChild);

    /**
     * @brief Function that sets this GO's parent
     */
    void
    setParent(const ShrdPtr<GameObject>& parent);

    /**
     * @brief Function that returns this GO's parent
     */
    ShrdPtr<GameObject>
    getParent();

    /**
     * @brief Function that returns children vector
     */
    Vector<ShrdPtr<GameObject>>
    getChildren();

    /*
     * @brief Function to get a specific child in the children vector
     * @param the ID of the node
     */
    ShrdPtr<GameObject>
    getChild(String name);

    /*
     * @brief Function to get a specific child in the children vector
     * @param the ID of the node
     */
    ShrdPtr<GameObject>
    getChild(uint32 id);

    /*
     * @brief Function to set the ID of this node
     */
    void
    setID(uint32 id);

    /*
     * @brief Function to get the ID of this node
     */
    uint32
    getID();

    /*
     * @brief Function to get the name of this node
     */
    String
    getName();


#pragma region COMPONET_FUNCTIONS
    template<class ComponentType, typename... Args>
    void addComponent(Args&& ... params) {
      m_components.emplace_back(make_unique<ComponentType>(std::forward<Args>(params)...));
    }

    template<class ComponentType>
    ComponentType&
      getComponent() {
      for (auto&& component : m_components) {
        if (component->isOfType(ComponentType::Type))
          return *static_cast<ComponentType*>(component.get());
      }

      return *std::unique_ptr<ComponentType>(nullptr);
    }
#pragma endregion COMPONET_FUNCTIONS
    

    Transform* m_transform;
    Scene* m_scene;
    ShrdPtr<GameObject> m_parent = nullptr;
    Vector<ShrdPtr<GameObject>> m_children;
    Vector<UnqPtr<Component>> m_components;
    uint32 m_id = 0;
    String m_name;
    bool m_isActive = true;

  };

  
  

}
