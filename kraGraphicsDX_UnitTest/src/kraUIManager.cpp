#include "kraUIManager.h"
#include <kraCamera.h>
#include <kraDevice.h>
#include <kraTexture.h>
#include <kraMaterial.h>
#include "WinAppTest.h"

//TODO: Make GFXAPI a module so this manager can be initialized without parameters
  bool
  UIManager::initUI(void* hWnd, void* pDevice, void* pCtx)
  {
    //pgfxDevice = make_shared<Device>(pDevice);
    windowHandle = reinterpret_cast<HWND>(hWnd);

    ID3D11Device* device = reinterpret_cast<ID3D11Device*>(pDevice);
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
    showInspector(nullptr);
    showSceneWindow();

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

  void
  UIManager::showSceneGraph(Scene* scene)
  {

    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(5, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 700), ImGuiCond_FirstUseEver);

    kraEngineSDK::SceneGraph* sc = SceneManager::instance().getActiveScene()->m_sceneGraph;

    ImGui::Begin("Scene Graph");
    if (ImGui::OpenPopupOnItemClick("Scenegrapgh context menu", 1)) {
      ImGui::Text("Hi I'm Elfo");
    }

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
      showInspector(&node);
    }

    bool nodeOpen = ImGui::TreeNodeEx(&node, node_flags, node.getName().c_str(), m_selectedNode);
    if (ImGui::IsItemClicked())
    {
      m_selectedNode = &node;
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
  UIManager::showInspector(GameObject* gameObj)
  {
    ImGui::SetNextWindowPos(ImVec2(1280, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(320, 600), ImGuiCond_FirstUseEver);

    ImGui::Begin("Gameobject details");

    if (gameObj != nullptr) {

      for (auto&& comp : gameObj->m_components)
      {
        
        if (comp->isOfType(Transform::Type)) {
          drawTransform(*gameObj->m_transform);
        }
        else if (comp->isOfType(Camera::Type)) {
          drawCamera(gameObj->getComponent<Camera>());
        }
        else if (comp->isOfType(Mesh::Type)) {
          drawMesh(gameObj->getComponent<Mesh>());
        }
        else if (comp->isOfType(Material::Type)) {
          Material GOMat = gameObj->getComponent<Material>();
          drawMaterial(GOMat);
        }
        
      }
    }
    ImGui::End();

  }

  void
  UIManager::showSceneWindow() {

    ImGui::SetNextWindowPos(ImVec2(310, 20));
    ImGui::SetNextWindowSize(ImVec2(965, 800));

    ImGui::Begin("Scene");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

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
    static float scale[3] = {1.0, 1.0, 1.0};

    ImGui::Text("Transform");
    ImGui::InputFloat3("Position", pos);
    if (pos[0] != oldPos[0] && pos[1] != oldPos[1] && pos[2] != oldPos[2]) {
      transform.setPosition(Vector3(pos[0], pos[1], pos[2]));
    }

    ImGui::InputFloat3("Rotation", rot);
    if (rot[0] != oldRot[0] && rot[1] != oldRot[1] && rot[2] != oldRot[2]) {
      transform.setRotation(Vector3(pos[0], pos[1], pos[2]));
      
    }
    ImGui::InputFloat3("Scale", scale);
    if (scale[0] != oldScale[0] && scale[1] != oldScale[1] && scale[2] != oldScale[2]) {
      transform.setScale(Vector3(pos[0], pos[1], pos[2]));
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
     -Show Roughness Texture
     -Show Emissive texture
     -Show AO Texture
     */

    static uint32 width = mat.getAlbedoTex()->getWidth();
    static uint32 height = mat.getAlbedoTex()->getHeight();

    static Vector4 baseColor = mat.m_baseColor;
    static float metallic = mat.m_metallic;
    static float rough = mat.m_roughness;

    ImGui::Text("Albedo Texture");
    ImGui::Image(mat.getAlbedoTex()->getShaderResourceView(),
                 ImVec2(100, 100),
                 ImVec2(0, 0),
                 ImVec2(1, 1),
                 ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                 ImVec4(1.0f, 1.0f, 1.0f, 0.5f));

    ImGui::Text("Normal Texture");
    ImGui::Image(mat.getNormalTex()->getShaderResourceView(),
                 ImVec2(100, 100),
                 ImVec2(0, 0),
                 ImVec2(1, 1),
                 ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                 ImVec4(1.0f, 1.0f, 1.0f, 0.5f));

    ImGui::Text("Metalness Texture");
    ImGui::Image(mat.getMetalTex()->getShaderResourceView(),
                 ImVec2(100, 100),
                 ImVec2(0, 0),
                 ImVec2(1, 1),
                 ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                 ImVec4(1.0f, 1.0f, 1.0f, 0.5f));


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
