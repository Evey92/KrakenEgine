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
  class KRA_CORE_EXPORT Model
  {
   public:

     Model() = default;
     virtual
     ~Model() {}


    bool 
    loadModelFromFile(const std::string& fileName,  Device& pDevice, Texture* pTexture);
    void
    Model::processNode(aiNode* rootNode, const aiScene* pScene,  Device& pDevice);
    Mesh*
    processMesh(aiMesh* pMesh, const aiScene* scene,  Device& pDevice);
    SIZE_T
    getMeshVecSize();
    
    const std::vector<Mesh*>&
    getMeshVec() const;

    Mesh&
    getMeshVecObjbyIndex(uint32 index) const;

    void
    Draw(Device* pDevice);

   private:
    std::vector<Mesh*> m_meshVec;
    Vector<aiMaterial*> m_materialsVec;
    uint32 m_currentMesh = 0;
    uint32 m_currentMat = 0;
  };

 

}