#include "kraUIManager.h"
#include <kraCamera.h>
#include "WinAppTest.h"

//TODO: Make GFXAPI a module so this manager can be initialized without parameters
  bool
  UIManager::initUI(void* hWnd, void* pDevice, void* pCtx)
  {
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

    kraEngineSDK::SceneGraph* sc = scene->m_sceneGraph;

    ImGui::Begin("Scene Graph");
    
    ImGui::Text(scene->m_name.c_str());

    for (auto& node : sc->getSceneNodes())
    {
      drawSceneGraphNode(node);
    }

    ImGui::End();
  }

  void
  UIManager::drawSceneGraphNode(GameObject* node) {
    
    if (node == nullptr)
    {
      return;
    }

    if (ImGui::TreeNode(node->getName().c_str()))
    {
      showInspector(node);

      for (auto* nd : node->getChildren()) {
        drawSceneGraphNode(nd);
      }
      ImGui::TreePop();
    }
  }

  void
  UIManager::showInspector(GameObject* gameObj)
  {
    ImGui::SetNextWindowPos(ImVec2(1280, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_FirstUseEver);

    ImGui::Begin("Gameobject details");

    if (gameObj != nullptr) {

      for (auto&& comp : gameObj->m_components)
      {
        if (comp->isOfType(Transform::Type)) {
          drawTransform(gameObj->m_transform);
        }
        else if (comp->isOfType(Camera::Type)) {
          Camera objCam = gameObj->getComponent<Camera>();
          drawCamera(&objCam);
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
  UIManager::drawTransform(Transform transform)
  {
    static float pos[3] = { transform.Position.x, transform.Position.y, transform.Position.z };
    static float rot[3] = { transform.Rotation.x, transform.Rotation.y, transform.Rotation.z };
    static float scale[3] = { transform.Scale.x, transform.Scale.y, transform.Scale.z };
    
    ImGui::Text("Transform");
    ImGui::InputFloat3("Position", pos);
    ImGui::InputFloat3("Rotation", rot);
    ImGui::InputFloat3("Scale", scale);
    ImGui::Separator();
  }

  void
  UIManager::drawCamera(Camera* cam)
  {
    static float camFov = cam->getFOVAsDeg();
    static float camNear = cam->getNearPlane();
    static float camFar = cam->getFarPlane();

    ImGui::Text("Camera");
    ImGui::SliderFloat("Field of View", &camFov, 0.0f, 179.0f);
    cam->setFOVfromDeg(camFov);
    ImGui::InputFloat("Near Plane", &camNear, .05f, 0, "%.3f");
    ImGui::InputFloat("Far Plane", &camFar, .05f, 0, "%.3f");
    ImGui::Separator();

  }

 

  void UIManager::onShutdown()
  {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
  }
