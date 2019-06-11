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
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices |
      aiProcess_ConvertToLeftHanded);

    if (!scene)
    {
      return false;
    }

    processNode(scene->mRootNode, scene, pDevice);
    m_currentMesh = 0;
    m_currentMat = 0;
    return true;
  }

  Vector<Texture*>
  Model::loadMaterialTextures(Device& pDevice,  aiMaterial* mat, aiTextureType type, String typeName, const aiScene* scene) {

    Vector<Texture*> textVec;

    for (uint32 i = 0; i < mat->GetTextureCount(type); ++i)
    {
      aiString path;
      mat->GetTexture(type, i, &path);
      String texType;

      Texture* newTex = pDevice.createTextureInstance();

      if (textureType == "embedded compressed texture")
      {
        // Do some stuff to extract embedded textures
      }
      else
      {
        String filename = String(path.C_Str());
        filename = texturesPath + filename;
        newTex->createTexture2DFromFile(pDevice, filename);
        textVec.push_back(newTex);
      }
    }

    return textVec;
  }

  void
    Model::processNode(aiNode* rootNode, const aiScene* pScene, Device& pDevice) {

    for (uint32 i = 0; i < rootNode->mNumMeshes; ++i) {
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

    if (pMesh->mMaterialIndex >= 0)
    {
      aiMaterial* mat = scene->mMaterials[pMesh->mMaterialIndex];

      if (textureType.empty())
      {
        textureType = getTextureType(scene, mat);
      }
    }

    for (uint32 i = 0; i < pMesh->mNumVertices; ++i)
    {
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
      newMesh->getVertexBuffer()->add(vert);
    }


    for (uint32 i = 0; i < pMesh->mNumFaces; ++i)
    {
      aiFace face = pMesh->mFaces[i];

      for (uint32 j = 0; j < face.mNumIndices; ++j) {
        newMesh->getIndexBuffer()->add(face.mIndices[j]);
      }
    }

    if (pMesh->mMaterialIndex >= 0)
    {
      aiMaterial* material = scene->mMaterials[pMesh->mMaterialIndex];

       Vector<Texture*> diffuseMaps = loadMaterialTextures(pDevice, 
                                                       material,
                                                       aiTextureType_DIFFUSE,
                                                       "texture_diffuse",
                                                       scene);
       for (uint32 i = 0; i < diffuseMaps.size(); ++i)
       {
         newMesh->getTextureVector().push_back(diffuseMaps[i]);
       }

    }

    newMesh->getVertexBuffer()->createHardwareBuffer(pDevice);
    newMesh->getIndexBuffer()->createIndexBuffer(pDevice);


    return newMesh;
  }

  SIZE_T
    Model::getMeshVecSize() {
    return m_meshVec.size();
  }

  const std::vector<Mesh*>&
    Model::getMeshVec() const {
    return m_meshVec;
  }

  Mesh&
    Model::getMeshVecObjbyIndex(uint32 index) const {
    return *m_meshVec[index];
  }

  void
    Model::Draw(Device* pDevice) {

    for (uint32 i = 0; i < m_meshVec.size(); i++)
    {
      m_meshVec[i]->DrawMesh(pDevice);
    }
  }

  String
    Model::getTextureType(const aiScene* scene, aiMaterial* mat) {

    aiString textypeStr;
    mat->GetTexture(aiTextureType_DIFFUSE, 0, &textypeStr);

    String textypeteststr = textypeStr.C_Str();

    if (textypeteststr == "*0" ||
      textypeteststr == "*1" ||
      textypeteststr == "*2" ||
      textypeteststr == "*3" ||
      textypeteststr == "*4" ||
      textypeteststr == "*5")
    {
      if (scene->mTextures[0]->mHeight = 0)
      {
        return "embedded compressed texture";
      }
      else
      {
        return "embedded non-compressed texture";
      }
    }
    if (textypeteststr.find('.') != String::npos)
    {
      return "textures are on disk";
    }

    return "No textures on model";

  }

}
