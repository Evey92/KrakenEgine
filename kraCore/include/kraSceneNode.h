#pragma once
#include "kraPrerequisitesCore.h"
#include "kraGameObject.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT SceneNode
  {
   public:
     SceneNode();
     ~SceneNode() { /*Function to delete Node + all children*/ }

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
     getChild(int id);

    /*
    ** @brief Function to set the ID of this node
    **/
    void
    setID(int id);

    /*
    ** @brief Function to get the ID of this node
    **/
    int
    getID();

    /*
    ** @brief Function to set the name of this node
    **/
    void
    setName(String name);

    /*
    ** @brief Function to get the name of this node
    **/
    String
    getName();

   private:

     int m_id;
     String m_name = "gameObject";
     GameObject* m_gameObject;
     SceneNode* m_parent;
     Vector<SceneNode*> m_children;
  };
}