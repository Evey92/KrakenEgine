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
    setNode(const ShrdPtr<GameObject>& newNode);

    /*
     * @brief Function to add a new SceneNode as a child of a specific node
     * @param the node to add
     * @param the name of the parent node
     */
    void
    setNodeAtChildren(const ShrdPtr<GameObject>& newNode, String parentName);

    /*
     * @brief Function to add a new SceneNode as a child of a specific node
     * @param the node to add
     * @param the id of the parent node
     */
    void
    setNodeAtChildren(const ShrdPtr<GameObject>& newNode, int parentID);

    /*
     * @brief Function to add a new SceneNode at the root node
     * @param the node to add
     */
    ShrdPtr<GameObject>
    getNode(String nodeName);

    /*
     * @brief Function to add a new SceneNode at the root node
     * @param the node to add
     */
    ShrdPtr<GameObject>
    getNode(int nodeId);

    /*
     * @brief Function to get the root node of the scene graph
     */
    ShrdPtr<GameObject>
    getRootNode();

    uint32
    getNodesSize();

    Vector<ShrdPtr<GameObject>>
    getSceneNodes();

    void 
    deleteNode(int nodeId);

    void
    deleteNode(String nodeName);

   private:
     Vector<ShrdPtr<GameObject>> m_sceneNodes;
     ShrdPtr<GameObject> m_root = nullptr;
  };
}