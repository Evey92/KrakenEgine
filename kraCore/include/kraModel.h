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
  class Vector2;
  class Vector3;
  class KRA_CORE_EXPORT Model
  {
   public:

     Model() = default;
     virtual
     ~Model() {}


    bool 
    loadModelFromFile(const std::string& fileName,  Device& pDevice);
    void
    Model::processNode(aiNode* rootNode, const aiScene* pScene,  Device& pDevice);
    Mesh
    processMesh(aiMesh* pMesh, const aiScene* scene,  Device& pDevice);
    uint32
    getMeshVecSize();
    std::vector<Mesh>
    getMeshVec();
    void
    Draw(Device* pDevice);

   private:
    std::vector<Mesh> meshVec;
  };

 

}