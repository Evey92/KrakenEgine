#pragma once
#include "kraPrerequisitesCore.h"
#include "kraSceneNode.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT SceneGraph {

   public:
     SceneGraph() = default;
    ~SceneGraph() = default;

    /*
     * @brief Function to initialize the scenegraph
     */
    void
    initialize();

    /*
     * @brief Function to add a new SceneNode at the root node
     * @param the node to add
     */
    void 
    setNode(GameObject* newNode);

    /*
     * @brief Function to add a new SceneNode as a child of a specific node
     * @param the node to add
     * @param the name of the parent node
     */
    void
    setNodeAtChildren(GameObject* newNode, String parentName);

    /*
     * @brief Function to add a new SceneNode as a child of a specific node
     * @param the node to add
     * @param the id of the parent node
     */
    void
    setNodeAtChildren(GameObject* newNode, int parentID);

    /*
     * @brief Function to add a new SceneNode at the root node
     * @param the node to add
     */
    GameObject*
    getNode(String nodeName);

    /*
     * @brief Function to add a new SceneNode at the root node
     * @param the node to add
     */
    GameObject*
    getNode(int nodeId);

    /*
     * @brief Function to get the root node of the scene graph
     */
    GameObject*
    getRootNode();

    uint32
    getNodesSize();

    Vector<GameObject*>
    getSceneNodes();

   private:
     Vector<GameObject*> m_sceneNodes;
     GameObject* m_root = nullptr;
  };
}