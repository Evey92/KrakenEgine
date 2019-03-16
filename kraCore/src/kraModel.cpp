#include <kraVector2.h>
#include <kraVector3.h>

#include "kraModel.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  
  bool
  Model::loadModelFromFile(const std::string& fileName, Device& pDevice) {
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
      

      return false;
    }

    processNode(scene->mRootNode, scene, pDevice);

  }

  void
  Model::processNode(aiNode* rootNode, const aiScene* pScene,  Device& pDevice) {
    for (uint32 i = 0; i < rootNode->mNumMeshes; i++) {
      aiMesh* mesh = pScene->mMeshes[rootNode->mMeshes[i]];
      meshVec.push_back(processMesh(mesh, pScene, pDevice));
    }

    for (uint32 i = 0; i < rootNode->mNumChildren; i++) {
      processNode(rootNode->mChildren[i], pScene, pDevice);
    }
  }

  Mesh
  Model::processMesh(aiMesh* pMesh, const aiScene* scene, Device& pDevice) {
    
    Mesh newMesh(pDevice);

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
      if (pMesh->mNormals)
      {
        vert.m_normal.x = pMesh->mNormals->x;
        vert.m_normal.y = pMesh->mNormals->y;
        vert.m_normal.z = pMesh->mNormals->z;
      }
      if (pMesh->mTangents)
      {
        vert.m_tangent.x = pMesh->mTangents->x;
        vert.m_tangent.y = pMesh->mTangents->y;
        vert.m_tangent.z = pMesh->mTangents->z;

        
      }
      if (pMesh->mBitangents)
      {
        vert.m_binormal.x = pMesh->mBitangents->x;
        vert.m_binormal.y = pMesh->mBitangents->y;
        vert.m_binormal.z = pMesh->mBitangents->z;
      }
      newMesh.m_vertexBurffer->add(vert);
    }
    

    for (uint32 i = 0; i < pMesh->mNumFaces; i++) {
      const aiFace& face = pMesh->mFaces[i];

      for (uint32 j = 0; j < face.mNumIndices; j++) {
        newMesh.m_indexBuffer->add(face.mIndices[j]);
      }
    }
    
    newMesh.m_vertexBurffer->createHardwareBuffer(pDevice);
    newMesh.m_indexBuffer->createIndexBuffer(pDevice);
    newMesh.m_vertexBurffer->setVertexBuffer(pDevice);
    newMesh.m_indexBuffer->setIndexBuffer(pDevice);
      
    return newMesh;
  }

  uint32
  Model::getMeshVecSize() {
    return meshVec.size();
  }
  std::vector<Mesh>
  Model::getMeshVec() {
    return meshVec;
  }
  
  void
  Model::Draw(Device* pDevice) {

    for (uint32 i = 0; i < meshVec.size(); i++)
    {
      meshVec[i].DrawMesh(pDevice);
    }
  }

}