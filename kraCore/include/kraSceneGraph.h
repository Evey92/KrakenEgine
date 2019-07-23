#pragma once
#include "kraPrerequisitesCore.h"
#include "kraSceneNode.h"

namespace kraEngineSDK {
  class SceneGraph {

   public:
     SceneGraph() = default;
    ~SceneGraph() = default;

    /*
    ** @brief Function to initialize the scenegraph
    **/
    void
    initialize();

    /*
    ** @brief Function to add a new SceneNode at the root node
    ** @param the node to add
    **/
    void 
    setNode(SceneNode* newNode);

    /*
    ** @brief Function to add a new SceneNode as a child of a specífic node
    ** @param the node to add
    ** @param the name of the parent node
    **/
    /*void
    setNodeAtChildren(SceneNode* newNode, String parentName);
*/
    /*
    ** @brief Function to add a new SceneNode as a child of a specífic node
    ** @param the node to add
    ** @param the id of the parent node
    **/
    void
    setNodeAtChildren(SceneNode* newNode, int parentID);

    /*
    ** @brief Function to add a new SceneNode at the root node
    ** @param the node to add
    **/
    /*SceneNode*
    getNode(String nodeName);*/

    /*
    ** @brief Function to add a new SceneNode at the root node
    ** @param the node to add
    **/
    SceneNode*
    getNode(int nodeId);

    /*
    ** @brief Function to get the root node of the scene graph
    **/
    SceneNode*
    getRootNode();

    uint32
    getNodesSize();

   private:
     
     Vector<SceneNode*> m_sceneNodes;
     SceneNode* m_root;
  };
}