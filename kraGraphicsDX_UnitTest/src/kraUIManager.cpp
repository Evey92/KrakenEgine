#include "kraUIManager.h"

bool 
UIManager::initUI(void* hWnd, void* pDevice, void* pCtx)
{
  ID3D11Device* device = reinterpret_cast<ID3D11Device*>(pDevice);
  ID3D11DeviceContext* ctx = reinterpret_cast<ID3D11DeviceContext*>(pCtx);

  //IMGUI_CHECKVERSION();
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
UIManager::updateUI()
{
  
}

void 
UIManager::renderUI()
{
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
  showHelloWindow();
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
UIManager::showHelloWindow()
{
  static float f = 0.0f;
  static int counter = 0;

  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImVec2(250, 500));

  ImGui::Begin("Hello, world!");                
  ImGui::Text("This is some useful text.");

  ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
  
  if (ImGui::Button("Button")) {                      
    counter++;
  }

  ImGui::SameLine();
  ImGui::Text("counter = %d", counter);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::End();
}

