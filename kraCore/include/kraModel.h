#pragma once
#include <kraVertex.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>         
#include <assimp/postprocess.h> 

#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include "kraMesh.h"
#include "kraGameObject.h"


namespace kraEngineSDK {
  
  class Device;
  class Texture;
  class Vector2;
  class Vector3;
  
  class KRA_CORE_EXPORT Model 
  {


   public:

     Model(GameObject* owner) : m_meshOwner(owner) {}
     ~Model() = default;


    bool 
    loadModelFromFile(const String& fileName, Device& pDevice);
    
    bool
    loadMaterialTextures(Device& pDevice, Texture& texture, aiMaterial * mat, aiTextureType type, String typeName, const aiScene * scene);

    void
    Model::processNode(aiNode* rootNode, const aiScene* pScene,  Device& pDevice);
    
    Mesh*
    processMesh(aiMesh* pMesh, const aiScene* scene,  Device& pDevice);
    
    SIZE_T
    getMeshVecSize();
    
    const Vector<Mesh*>&
    getMeshVec() const;
    
    Mesh&
    getMeshVecObjbyIndex(uint32 index) const;
    
    void
    Draw(Device* pDevice);

    String
    getTextureType(const aiScene* scene, aiMaterial* mat);
    
    //This function is to apply a material to ALL meshes
    void
    setAllMeshMaterials(Device* pDevice, Material* mat);

   private:
    
     //TODO: Refactor Model and mesh so the model's index buffer is filled with 
    GameObject* m_meshOwner;
    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Vector<ShrdPtr<Mesh>> m_meshVec;
    Vector<aiMaterial*> m_materialsVec;
    uint32 m_currentMesh = 0;
    uint32 m_currentMat = 0;
    String textureType;
    String modelsPath = "resources/Models/";
    String texturesPath = "resources/Textures/";


  };

 

}