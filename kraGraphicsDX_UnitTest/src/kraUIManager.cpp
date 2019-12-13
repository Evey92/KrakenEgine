#include "kraUIManager.h"
#include <kraCamera.h>
#include <kraDevice.h>
#include <kraTexture.h>
#include <kraMaterial.h>
#include "WinAppTest.h"

//TODO: Make GFXAPI a module so this manager can be initialized without parameters
  bool
  UIManager::initUI(void* hWnd, ShrdPtr<Device>& pDevice, void* pCtx)
  {
    pgfxDevice = pDevice;
    windowHandle = reinterpret_cast<HWND>(hWnd);

    ID3D11Device* device = reinterpret_cast<ID3D11Device*>(pDevice->getDevice());
    ID3D11DeviceContext* ctx = reinterpret_cast<ID3D11DeviceContext*>(pCtx);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    if (!ImGui_ImplWin32_Init(hWnd)) {
      return false;
    }


    if (!ImGui_ImplDX11_Init(device, ctx)) {
      return false;
    }

    sc = SceneManager::instance().getActiveScene()->m_sceneGraph;


    return true;
  }

  void
    UIManager::updateUI(Scene* scene)
  {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        if (ImGui::MenuItem("Load Model")) {
          BaseApplication::instance().loadModel();
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Edit"))
      {
        if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
        if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        if (ImGui::MenuItem("Paste", "CTRL+V")) {}
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
    showSceneGraph(scene);
    showInspector(*sc->getRootNode());
    showSceneWindow();
    showConsole();
    showProjectFiles();
    ImGui::EndFrame();

  }

  void
  UIManager::renderUI()
  {
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
    }

  }

  void
  UIManager::shutDown()
  {
    // Cleanup
    
  }

  //TODO: Maybe the handling of context menus should be done somewhere else, but since I just need context menus inside the scenegraph, at least for now, I'm putting it here.
  void
  UIManager::showSceneGraph(Scene* scene)
  {

    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(5, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);


    ImGui::Begin("Scene Graph");

    ImGui::Text(scene->m_name.c_str());

    
    for (auto& node : sc->getSceneNodes())
    {  
      drawSceneGraphNode(*node); 
    }


    

    ImGui::End();
  }

  void
  UIManager::drawSceneGraphNode(GameObject& node) {
    
    if (node.getName() == "Root")
    {
      return;
    }

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    if (&node == m_selectedNode) {
      node_flags |= ImGuiTreeNodeFlags_Selected;
      showInspector(node);
    }

    bool nodeOpen = ImGui::TreeNodeEx(&node, node_flags, node.getName().c_str(), m_selectedNode);
    
    if (ImGui::IsItemClicked())
    {
      m_selectedNode = &node;
    }
    
    if (ImGui::BeginPopupContextItem("Scenegrapgh context menu") && ImGui::IsItemClicked(1)) {
      if (ImGui::Selectable("Delete")) {
        sc->deleteNode(node.getID());
      }

      ImGui::EndPopup();
    }

    if (nodeOpen)
    {
      for (auto& nd : node.getChildren()) {
        drawSceneGraphNode(*nd);
      }
      ImGui::TreePop();
    }

   

  }

  void
  UIManager::showInspector(GameObject& gameObj)
  {
    ImGui::SetNextWindowPos(ImVec2(1280, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(320, 400), ImGuiCond_FirstUseEver);

    ImGui::Begin("Gameobject details");

    if (!gameObj.m_isRoot) {

      for (auto&& comp : gameObj.m_components)
      {
        
        if (comp->isOfType(Transform::Type)) {
          drawTransform(*gameObj.m_transform);
        }
        else if (comp->isOfType(Camera::Type)) {
          drawCamera(gameObj.getComponent<Camera>());
        }
        else if (comp->isOfType(Mesh::Type)) {
          drawMesh(gameObj.getComponent<Mesh>());
        }
        else if (comp->isOfType(Material::Type)) {
          Material GOMat = gameObj.getComponent<Material>();
          drawMaterial(GOMat);
        }
        
      }
    }
    ImGui::End();

  }

  void
  UIManager::showSceneWindow() {

    ImGui::SetNextWindowPos(ImVec2(310, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(965, 500), ImGuiCond_FirstUseEver);

    ImGui::Begin("Scene");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();

  }

  void 
  UIManager::showConsole()
  {
    ImGui::SetNextWindowPos(ImVec2(310, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(965, 500), ImGuiCond_FirstUseEver);

    ImGui::Begin("Console");

    ImGui::Text("Ïnitializing log");

    ImGui::End();
  }

  void UIManager::showProjectFiles()
  {
    ImGui::SetNextWindowPos(ImVec2(310, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(965, 500), ImGuiCond_FirstUseEver);

    ImGui::Begin("Project files");

    ImGui::Text("Initializing files");

    ImGui::End();
  }

  void
  UIManager::drawTransform(Transform& transform)
  {
    float oldPos[3]   = { transform.getPosition()[0], transform.getPosition()[1], transform.getPosition()[2] };
    float oldRot[3]   = { transform.getRotation()[0], transform.getRotation()[1], transform.getRotation()[2] };
    float oldScale[3] = { transform.getScale()[0],    transform.getScale()[1],    transform.getScale()[2] }; 

    static float pos[3];
    static float rot[3];
    static float scale[3];

    pos[0] = oldPos[0];
    pos[1] = oldPos[1];
    pos[2] = oldPos[2];
    ImGui::Text("Transform");
    ImGui::InputFloat3("Position", pos);
    if (pos[0] != oldPos[0] || pos[1] != oldPos[1] || pos[2] != oldPos[2]) {
      transform.setPosition(Vector3(pos[0], pos[1], pos[2]));

    }

    rot[1] = oldRot[1];
    rot[2] = oldRot[2];
    rot[0] = oldRot[0];
    ImGui::InputFloat3("Rotation", rot);
    if (rot[0] != oldRot[0] || rot[1] != oldRot[1] || rot[2] != oldRot[2]) {
      transform.setRotation(Vector3(rot[0], rot[1], rot[2]));

    }

    scale[0] = oldScale[0];
    scale[1] = oldScale[1];
    scale[2] = oldScale[2];
    ImGui::InputFloat3("Scale", scale);
    if (scale[0] != oldScale[0] || scale[1] != oldScale[1] || scale[2] != oldScale[2]) {
      transform.setScale(Vector3(scale[0], scale[1], scale[2]));
    }
    ImGui::Separator();
  }

  void
  UIManager::drawCamera(Camera& cam)
  {
    static float camFov = cam.getFOVAsDeg();
    static float camNear = cam.getNearPlane();
    static float camFar = cam.getFarPlane();

    float oldFov = camFov;
    float oldNear = camNear;
    float oldFar = camFar;
    ImGui::Text("Camera");
    ImGui::SliderFloat("Field of View", &camFov, 0.0f, 179.0f);
    if (camFov != oldFov)
    {
      CameraManager::instance().getActiveCamera()->setFOVfromDeg(camFov);
    }

    ImGui::InputFloat("Near Plane", &camNear, .05f, 0, "%.3f");
    if (camNear != oldNear)
    {
      CameraManager::instance().getActiveCamera()->setNearPlane(camNear);
    }

    ImGui::InputFloat("Far Plane", &camFar, .05f, 0, "%.3f");
    if (camFar != oldFar)
    {
      CameraManager::instance().getActiveCamera()->setFarPlane(camFar);
    }

    ImGui::Separator();

  }

  void 
  UIManager::drawMaterial(Material& mat)
  {
    ImGui::Text("Material");

    /* 
     TODO: Show material properties:
     -Show Emissive texture
     -Show AO Texture
     */

    static uint32 width = mat.getAlbedoTex()->getWidth();
    static uint32 height = mat.getAlbedoTex()->getHeight();

    static Vector4 baseColor = mat.m_baseColor;
    static float metallic = mat.m_metallic;
    static float rough = mat.m_roughness;

    ImGui::Text("Albedo Texture");
    if (ImGui::ImageButton(mat.getAlbedoTex()->getShaderResourceView(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1), 0)) {
     
      String filename = EngineUtility::loadFile("JPEG Files\0*.jpg\0Traga Files\0*.tga\0PNG Files\0*.png\0Any File\0*.*\0", windowHandle);
      mat.getAlbedoTex()->createTexture2DFromFile(*pgfxDevice,
                                                  filename,
                                                  GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM_SRGB,
                                                  GFX_USAGE::E::kUSAGE_DEFAULT,
                                                  CPU_USAGE::E::kCPU_ACCESS_WRITE);
    }


    ImGui::Text("Normal Texture");
    if (ImGui::ImageButton(mat.getNormalTex()->getShaderResourceView(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1), 0)) {
      String filename = EngineUtility::loadFile("JPEG Files\0*.jpg\0Traga Files\0*.tga\0PNG Files\0*.png\0Any File\0*.*\0", windowHandle);
      mat.getNormalTex()->createTexture2DFromFile(*pgfxDevice,
                                                  filename,
                                                  GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                                  GFX_USAGE::E::kUSAGE_DEFAULT,
                                                  CPU_USAGE::E::kCPU_ACCESS_WRITE);
    }

    ImGui::Text("Metalness Texture");
    if (ImGui::ImageButton(mat.getMetalTex()->getShaderResourceView(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1), 0)) {
      String filename = EngineUtility::loadFile("JPEG Files\0*.jpg\0Traga Files\0*.tga\0PNG Files\0*.png\0Any File\0*.*\0", windowHandle);
      mat.getMetalTex()->createTexture2DFromFile(*pgfxDevice,
                                                 filename,
                                                 GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                                 GFX_USAGE::E::kUSAGE_DEFAULT,
                                                 CPU_USAGE::E::kCPU_ACCESS_WRITE);
    }


    ImGui::Text("Roughness Texture");
    if (ImGui::ImageButton(mat.getRoughnessTex()->getShaderResourceView(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1), 0)) {
      
      String filename = EngineUtility::loadFile("JPEG Files\0*.jpg\0Traga Files\0*.tga\0PNG Files\0*.png\0Any File\0*.*\0", windowHandle);
      mat.getRoughnessTex()->createTexture2DFromFile(*pgfxDevice,
                                                     filename,
                                                     GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                                     GFX_USAGE::E::kUSAGE_DEFAULT,
                                                     CPU_USAGE::E::kCPU_ACCESS_WRITE);
    }

    //-Base color RGB
    ImGui::ColorEdit3("Base Color", (float*)&baseColor);

    //-Metalness float (range 0.0f - 1.0f)
    ImGui::SliderFloat("Metalness", &metallic, 0.0f, 1.0f);

     //-Roughness float (range 0.0f - 1.0f)
    ImGui::SliderFloat("Roughness", &rough, 0.0f, 1.0f);
    ImGui::Separator();
  }

  void 
  UIManager::drawModel(Model& model)
  {
    //TODO: Draw mesh/model
  }

  void UIManager::drawMesh(Mesh& mesh)
  {
    ImGui::Text("Mesh");

    ImGui::Text("Name: "); ImGui::SameLine();
    ImGui::Text(&mesh.getName()[0]);
    //TODO: Implement this button.
    if (ImGui::Button("Change Mesh")) {
      String filetypes("FBX Files\0*.fbx\0OBJ Files\0*.obj\0Any File\0*.*\0"); 
      String filename = EngineUtility::loadFile(filetypes, windowHandle);

      //Do the loading and model replacing
    } //ImGui::SameLine();

    ImGui::Separator();

  }

  void
  UIManager::onShutdown()
  {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
  }
