#include <kraVector2.h>
#include <kraVector3.h>

#include "kraPrerequisitesCore.h"
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

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::cout << "ERROR::ASSIMP:: " << aImporter.GetErrorString() << std::endl;
      return false;
    }

    processNode(scene->mRootNode, scene, pDevice);
 
    return true;
  }

  bool
  Model::loadMaterialTextures(Device& pDevice,  Texture& texture, aiMaterial* mat, aiTextureType type, String typeName, const aiScene* scene) {

    
    uint32 totalTextures = mat->GetTextureCount(type);
    
    if (totalTextures > 0)
    {
      for (uint32 i = 0; i < totalTextures; ++i)
      {
        aiString path;
        mat->GetTexture(type, i, &path);
        String texType;
        
        if (textureType == "embedded compressed texture")
        {
          // Do some stuff to extract embedded textures
        }
        else
        {
          String filename = String(path.C_Str());
          filename = texturesPath + filename;
          texture.createTexture2DFromFile(pDevice, filename);
          return true;
        }
      }
    }
    else
    {
      std::cout << "Texture not included in mesh\n";
      return false;

    }

    std::cout << "Texture couldn't be loaded\n";
    
    return false;
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

      ShrdPtr<Texture> diffuseTex = pDevice.createTextureInstance();
      if (loadMaterialTextures(pDevice,
        *diffuseTex,
        material,
        aiTextureType_DIFFUSE,
        "texture_diffuse",
        scene))
      {
        newMesh->setTexture(kraTextureType::BASECOLOR, diffuseTex);
      }

      ShrdPtr<Texture> normalTex = pDevice.createTextureInstance();
      if (loadMaterialTextures(pDevice,
        *normalTex,
        material,
        aiTextureType_HEIGHT,
        "texture_normal",
        scene))
      {
        newMesh->setTexture(kraTextureType::NORMAL, normalTex);
      }


      ShrdPtr<Texture> specularTex = pDevice.createTextureInstance();

      if (loadMaterialTextures(pDevice,
        *specularTex,
        material,
        aiTextureType_SPECULAR,
        "texture_Specular",
        scene))
      {
        newMesh->setTexture(kraTextureType::SPECULAR, specularTex);
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
