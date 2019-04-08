#include <kraVector2.h>
#include <kraVector3.h>

#include "kraModel.h"
#include "kraDevice.h"
#include "kraTexture.h"

namespace kraEngineSDK {

  bool
    Model::loadModelFromFile(const std::string& fileName, Device& pDevice, Texture* pTexture) {

    Assimp::Importer aImporter;

    const aiScene* scene = aImporter.ReadFile(fileName,
      aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded);

    if (!scene)
    {
      return false;
    }

    processNode(scene->mRootNode, scene, pDevice);
    return true;
  }

  void
  Model::processNode(aiNode* rootNode, const aiScene* pScene,  Device& pDevice) {
    for (uint32 i = 0; i < rootNode->mNumMeshes; i++) {
      aiMesh* mesh = pScene->mMeshes[rootNode->mMeshes[i]];
      m_meshVec.push_back(processMesh(mesh, pScene, pDevice));
    }

    for (uint32 i = 0; i < rootNode->mNumChildren; i++) {
      processNode(rootNode->mChildren[i], pScene, pDevice);
    }
  }

  Mesh*
  Model::processMesh(aiMesh* pMesh, const aiScene* scene, Device& pDevice) {
    
    Mesh* newMesh = new Mesh(pDevice);

    for (uint32 i = 0; i < pMesh->mNumVertices; i++) {
      Vertex vert;

      vert.Pos.x = pMesh->mVertices[i].x;
      vert.Pos.y = pMesh->mVertices[i].y;
      vert.Pos.z = pMesh->mVertices[i].z;

      if (pMesh->HasTextureCoords(0))
      {
        vert.Tex.x = static_cast<float>(pMesh->mTextureCoords[0][i].x);
        vert.Tex.y = static_cast<float>(pMesh->mTextureCoords[0][i].y);
      }
      if (pMesh->HasNormals())
      {
        vert.m_normal.x = pMesh->mNormals->x;
        vert.m_normal.y = pMesh->mNormals->y;
        vert.m_normal.z = pMesh->mNormals->z;
      }
      if (pMesh->HasTangentsAndBitangents())
      {
        vert.m_tangent.x = pMesh->mTangents->x;
        vert.m_tangent.y = pMesh->mTangents->y;
        vert.m_tangent.z = pMesh->mTangents->z;

        vert.m_binormal.x = pMesh->mBitangents->x;
        vert.m_binormal.y = pMesh->mBitangents->y;
        vert.m_binormal.z = pMesh->mBitangents->z;
      }
      newMesh->m_vertexBurffer->add(vert);
    }
    

    for (uint32 i = 0; i < pMesh->mNumFaces; ++i) {
      const aiFace& face = pMesh->mFaces[i];

      for (uint32 j = 0; j < face.mNumIndices; ++j) {
        newMesh->m_indexBuffer->add(face.mIndices[j]);
      }
    }
    
    if (scene->HasMaterials())
    {
      for (uint32 i = 0; i < scene->mNumMaterials; ++i) {
        aiMaterial* mat = scene->mMaterials[i];
        aiString matName = mat->GetName();

        //TODO: Make a function on mesh that loads textures onto that mesh'materials

      }
      
    }

    newMesh->m_vertexBurffer->createHardwareBuffer(pDevice);
    newMesh->m_indexBuffer->createIndexBuffer(pDevice);


    return newMesh;
  }

  SIZE_T
  Model::getMeshVecSize() {
    return m_meshVec.size();
  }
  
  const std::vector<Mesh*>&
    Model::getMeshVec() const{
    return m_meshVec;
  }
  
  void
  Model::Draw(Device* pDevice) {

    for (uint32 i = 0; i < m_meshVec.size(); i++)
    {
      m_meshVec[i]->DrawMesh(pDevice);
    }
  }

}