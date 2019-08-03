#pragma once
#include <windows.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <kraBaseApplication.h>

using namespace kraEngineSDK;

class UIManager {
 
 public:

  bool 
  initUI(void* hWnd, void* device, void* ctx);

  void
  updateUI(kraEngineSDK::Scene* scene);

  void
  renderUI();

  void
  shutDown();

  void
  showSceneGraph(kraEngineSDK::Scene* sg);

  void
  showInspector(GameObject* gameObj);

  void
  showSceneWindow();

  void
  drawTransform(kraEngineSDK::Transform transform);

#pragma region COMPONENT_UI

  void
  drawCamera(kraEngineSDK::Camera* cam);

#pragma endregion COMPONENT_UI

};