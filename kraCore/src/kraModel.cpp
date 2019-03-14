#include <assimp/Importer.hpp>
#include <assimp/scene.h>         
#include <assimp/postprocess.h> 

#include "kraPrerequisitesCore.h"
#include "kraModel.h"

namespace kraEngineSDK {
  
  bool
  Model::loadModelFromFile(const std::string& fileName) {
    std::vector<Vertex> tmpVerts;
    std::vector<unsigned short> tmpIndex;
    
    Assimp::Importer aImporter;

    const aiScene* scene = aImporter.ReadFile(fileName,
                                              aiProcess_CalcTangentSpace |
                                              aiProcess_Triangulate |
                                              aiProcess_JoinIdenticalVertices |
                                              aiProcess_SortByPType |
                                              aiProcess_MakeLeftHanded);

    if (!scene)
    {
      //Log error

      return false;
    }

    processNode(scene->mRootNode, scene);

    /*m_vertexBurffer->add(tmpVerts);
    m_indexBuffer->add(tmpIndex);*/
  }

  bool
  Model::processNode(aiNode* rootNode, const aiScene* pScene) {
    for (uint32 i = 0; i < rootNode->mNumMeshes; i++) {
      aiMesh* mesh = pScene->mMeshes[rootNode->mMeshes[i]];
      meshVec.push_back(processMesh(mesh, pScene));
    }

    for (uint32 i = 0; i < rootNode->mNumChildren; i++) {
      processNode(rootNode->mChildren[i], pScene);
    }
  }

  Mesh
  Model::processMesh(aiMesh* pMesh, const aiScene* scene) {
    for (uint32 i = 0; i < pMesh->mNumVertices; i++) {
      Vertex vert;

      vert.Pos.x = pMesh->mVertices[i].x;
      vert.Pos.y = pMesh->mVertices[i].y;
      vert.Pos.z = pMesh->mVertices[i].z;

      if (pMesh->mTextureCoords[0])
      {
        vert.Tex.x = static_cast<float>(pMesh->mTextureCoords[0][i].x);
        vert.Tex.y = static_cast<float>(pMesh->mTextureCoords[0][i].y);
      }

    }
  
  
  }

  

}