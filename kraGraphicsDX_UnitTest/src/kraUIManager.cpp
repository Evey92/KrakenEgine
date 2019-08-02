#include "kraUIManager.h"
#include "WinAppTest.h"


bool 
UIManager::initUI(void* hWnd, void* pDevice, void* pCtx)
{
  ID3D11Device* device = reinterpret_cast<ID3D11Device*>(pDevice);
  ID3D11DeviceContext* ctx = reinterpret_cast<ID3D11DeviceContext*>(pCtx);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  
  if (!ImGui_ImplWin32_Init(hWnd)) {
    return false;
  }

  ImGui::StyleColorsDark();

  if (!ImGui_ImplDX11_Init(device, ctx)) {
    return false;
  }

  return true;
}

void 
UIManager::updateUI(kraEngineSDK::Scene* scene)
{
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
 
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      ImGui::MenuItem("(dummy menu)", NULL, false, false);
      if (ImGui::MenuItem("New")) {
      
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
  showInspector();
  showSceneWindow();
}

void 
UIManager::renderUI()
{
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

void 
UIManager::shutDown()
{
  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void 
UIManager::showSceneGraph(kraEngineSDK::Scene* scene)
{

  ImGuiIO& io = ImGui::GetIO();
  
  ImGui::SetNextWindowPos(ImVec2(5, 20));
  ImGui::SetNextWindowSize(ImVec2(300, 700));

  kraEngineSDK::SceneGraph* sc = scene->m_sceneGraph;

  ImGui::Begin("Scene Graph");                
  if (ImGui::TreeNode(scene->m_name.c_str()))
  {
    for (auto* node : sc->getSceneNodes())
    {
      if (node->getGameObject() != nullptr)
      {
        ImGui::TreeNode(node->getGameObject()->m_name.c_str());
      }
    }
  }



  ImGui::End();
}

void 
UIManager::showInspector()
{
  ImGui::SetNextWindowPos(ImVec2(1280, 20));
  ImGui::SetNextWindowSize(ImVec2(300, 600));

  ImGui::Begin("Gameobject details");
  
  ImGui::Text("Camera");

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
UIManager::drawTransform(kraEngineSDK::Transform transform)
{

}
