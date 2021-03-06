#include "kraModel.h"

#include <kraVector2.h>
#include <kraVector3.h>

#include "kraPrerequisitesCore.h"
#include "kraDevice.h"
#include "kraTexture.h"
#include "kraSceneManager.h"
#include "kraGameObject.h"

namespace kraEngineSDK {


  bool
  Model::loadModelFromFile(const String& fileName, Device& pDevice, const ShrdPtr<SceneManager>& sceneM) {

    Assimp::Importer aImporter;

    const aiScene* scene = aImporter.ReadFile(fileName, 
                                              aiProcessPreset_TargetRealtime_MaxQuality |
                                              aiProcess_Triangulate |
                                              aiProcess_JoinIdenticalVertices |
                                              aiProcess_ConvertToLeftHanded);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::cout << "ERROR::ASSIMP:: " << aImporter.GetErrorString() << std::endl;
      return false;
    }
 
    for (uint32 i = 0; i < scene->mNumMeshes; ++i) {
      aiMesh& mesh = *scene->mMeshes[i];
      ShrdPtr<GameObject> meshGO = sceneM->createGameObject(mesh.mName.C_Str());
      ShrdPtr<Mesh> newMesh = std::make_shared<Mesh>(pDevice, meshGO);
      newMesh->initialize(pDevice);

      processMesh(&mesh, scene, pDevice, newMesh);

      meshGO->addComponent<Mesh>(*newMesh);

      m_meshVec.push_back(meshGO);
    
    }

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
          return false;
        }
        else
        {
          String filename = String(path.C_Str());

          uint32 firstPos = filename.find_last_of('\\');
          String name = filename.substr(firstPos + 1);
          
          filename = texturesPath + name;
          texture.createTexture2DFromFile(pDevice,
                                          filename,
                                          GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                          GFX_USAGE::E::kUSAGE_DEFAULT,
                                          CPU_USAGE::E::kCPU_ACCESS_WRITE, 
                                          4, 1);
          return true;
        }
      }
    }
    else
    {
      
      std::cout << "Texture not included in mesh. Loading default Texture\n";
      texture.createTexture2DFromFile(pDevice,
                                      "resources/Textures/default.png",
                                      GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                      GFX_USAGE::E::kUSAGE_DEFAULT,
                                      CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                      4, 1);
      return false;

    }

    std::cout << "Texture couldn't be loaded\n";
    
    return false;
  }

  //Deprecated
  /*void
  Model::processNode(aiNode* rootNode, const aiScene* pScene, Device& pDevice) {
    Mesh* newMesh = nullptr;

    for (uint32 i = 0; i < rootNode->mNumMeshes; ++i) {
      aiMesh* mesh = pScene->mMeshes[rootNode->mMeshes[i]];
      

      //newMesh = processMesh(mesh, pScene, pDevice);
      //newMesh->initialize(pDevice);
     // m_meshVec.push_back(newMesh);
    }

    for (uint32 i = 0; i < rootNode->mNumChildren; i++) {
      processNode(rootNode->mChildren[i], pScene, pDevice);
    }

  }*/

  bool
  Model::processMesh(aiMesh* pMesh, const aiScene* scene, Device& pDevice, ShrdPtr<Mesh>& outMesh) {

    outMesh->setName(pMesh->mName.C_Str());
    outMesh->setTotalVert(pMesh->mNumVertices);
    outMesh->setTotalIndex(pMesh->mNumFaces);

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
      outMesh->getVertexBuffer()->add(vert);
    }

    for (uint32 i = 0; i < pMesh->mNumFaces; ++i)
    {
      aiFace face = pMesh->mFaces[i];

      for (uint32 j = 0; j < face.mNumIndices; ++j) {
        outMesh->getIndexBuffer()->add(face.mIndices[j]);
      }
    }

    if (pMesh->mMaterialIndex >= 0)
    {
      aiMaterial* material = scene->mMaterials[pMesh->mMaterialIndex];

      if (textureType.empty())
      {
        textureType = getTextureType(scene, material);
      }

      ShrdPtr<Texture> diffuseTex = pDevice.createTextureInstance();
      if (loadMaterialTextures(pDevice,
                               *diffuseTex,
                               material,
                               aiTextureType_DIFFUSE,
                               "texture_diffuse",
                               scene))
      {
        outMesh->setTexture(pDevice, TEXTURE_TYPE::E::ALBEDO, diffuseTex);
      }

      ShrdPtr<Texture> normalTex = pDevice.createTextureInstance();
      if (loadMaterialTextures(pDevice,
                               *normalTex,
                               material,
                               aiTextureType_HEIGHT,
                               "texture_normal",
                               scene))
      {
        outMesh->setTexture(pDevice, TEXTURE_TYPE::E::NORMAL, normalTex);
      }

      ShrdPtr<Texture> specularTex = pDevice.createTextureInstance();
      if (loadMaterialTextures(pDevice,
                               *specularTex,
                               material,
                               aiTextureType_SPECULAR,
                               "texture_Specular",
                               scene))
      {
        outMesh->setTexture(pDevice, TEXTURE_TYPE::E::SPECULAR, specularTex);
      }

    }
    else {
      ShrdPtr<Texture> diffuseTex = pDevice.createTextureInstance();
      diffuseTex->createTexture2DFromFile(pDevice,
                                          "default.png",
                                          GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                          GFX_USAGE::E::kUSAGE_DEFAULT,
                                          CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                          4, 1);
    }
    outMesh->getVertexBuffer()->createHardwareBuffer(pDevice);
    outMesh->getIndexBuffer()->createIndexBuffer(pDevice);

    return true;
  }

  SIZE_T
    Model::getMeshVecSize() {
    return m_meshVec.size();
  }

  Vector<ShrdPtr<GameObject>>
  Model::getMeshVec() {
    return m_meshVec;
  }

  ShrdPtr<GameObject>
  Model::getMeshVecObjbyIndex(uint32 index) {
    return m_meshVec[index];
  }

  void
  Model::Draw(Device* pDevice) {

    for (uint32 i = 0; i < m_meshVec.size(); i++)
    {
      m_meshVec[i]->getComponent<Mesh>().DrawMesh(*pDevice);
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
      if (scene->mTextures[0]->mHeight == 0)
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

  void 
  Model::setAllMeshMaterials(Device* pDevice, Material* mat)
  {
    for (auto& mesh : m_meshVec) {
      mesh->getComponent<Mesh>().setMeshMaterial(*pDevice, mat);
    }
  }

}
