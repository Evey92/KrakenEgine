#pragma once
#include <kraVertex.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>         
#include <assimp/postprocess.h> 

#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include "kraMesh.h"


namespace kraEngineSDK {
  
  class Device;
  class Texture;
  class Vector2;
  class Vector3;
  class GameObject;
  class SceneManager;

  class KRA_CORE_EXPORT Model 
  {


   public:

     Model(const ShrdPtr<GameObject>& owner) : m_meshOwner(owner) {}
     ~Model() = default;


    bool 
    loadModelFromFile(const String& fileName, Device& pDevice, const ShrdPtr<SceneManager>&);
    
    bool
    loadMaterialTextures(Device& pDevice, Texture& texture, aiMaterial * mat, aiTextureType type, String typeName, const aiScene * scene);

    void
    Model::processNode(aiNode* rootNode, const aiScene* pScene,  Device& pDevice);
    
    bool
    processMesh(aiMesh* pMesh, const aiScene* scene,  Device& pDevice, ShrdPtr<Mesh>& outMesh);
    
    SIZE_T
    getMeshVecSize();
    
    Vector<ShrdPtr<GameObject>>
    getMeshVec();
    
    ShrdPtr<GameObject>
    getMeshVecObjbyIndex(uint32 index);
    
    void
    Draw(Device* pDevice);

    String
    getTextureType(const aiScene* scene, aiMaterial* mat);
    
    //This function is to apply a material to ALL meshes
    void
    setAllMeshMaterials(Device* pDevice, Material* mat);

   private:
    
    ShrdPtr<GameObject> m_meshOwner;
    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Vector<ShrdPtr<GameObject>> m_meshVec;
    Vector<aiMaterial*> m_materialsVec;
    uint32 m_currentMesh = 0;
    uint32 m_currentMat = 0;
    String textureType;
    String modelsPath = "resources/Models/";
    String texturesPath = "resources/Textures/";


  };

 

}