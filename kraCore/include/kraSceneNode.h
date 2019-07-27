#pragma once
#include "kraPrerequisitesCore.h"
#include "kraGameObject.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT SceneNode
  {
  public:
    SceneNode() = default;
     ~SceneNode() { /*Function to delete Node + all children*/ }

    /*
    ** @brief Function to initialize the node
    **/
     void
     initialize(GameObject* gameObject);

    /*
    ** @brief Function to add a node as a child of this node
    ** @param The node to add
    **/
     void
     addChild(SceneNode* );

    /*
    ** @brief Function to get the gameObject in this node
    **/
     GameObject*
     getGameObject();

   /*
   ** @brief Function to get the parent of the node
   **/
     void
     setParent(SceneNode* newNode);

     /*
    ** @brief Function to get the parent of the node
    **/
     SceneNode*
     getParent();

    /*
    ** @brief Function to get All the children of this node
    **/
     Vector<SceneNode*>
     getChildren();

   /*
   ** @brief Function to get a specific child in the children vector
   ** @param the ID of the node
   **/
     SceneNode*
     getChild(String name);

    /*
    ** @brief Function to get a specific child in the children vector
    ** @param the ID of the node
    **/
     SceneNode*
     getChild(uint32 id);

    /*
    ** @brief Function to set the ID of this node
    **/
    void
    setID(uint32 id);

    /*
    ** @brief Function to get the ID of this node
    **/
    int
    getID();


   private:

     uint32 m_id;
     GameObject* m_gameObject = nullptr;
     SceneNode* m_parent = nullptr;
     Vector<SceneNode*> m_children;
  };
}