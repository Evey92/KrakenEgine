#pragma once
#include <kraVertex.h>

#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include "kraMesh.h"

namespace kraEngineSDK {
  
  class KRA_CORE_EXPORT Model
  {
   public:

     Model() = default;
     virtual
     ~Model() {}


    bool 
    loadModelFromFile(const std::string& fileName);
    bool
    Model::processNode(aiNode* rootNode, const aiScene* pScene);
    Mesh
    processMesh(aiMesh* pMesh, const aiScene* scene);
    uint32
    getMeshVecSize();
    std::vector<Mesh>
    getMeshVec();
   
   private:
    std::vector<Mesh> meshVec;
  };

 

}