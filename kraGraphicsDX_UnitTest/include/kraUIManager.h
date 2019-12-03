#pragma once
#include <kraModule.h>
#include <windows.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <kraCamera.h>
#include <kraModel.h>
#include <kraMesh.h>
#include <kraScene.h>

using namespace kraEngineSDK;

  class UIManager : public Module<UIManager>{

  public:

    bool
    initUI(void* hWnd, void* device, void* ctx);

    void
    updateUI(Scene* scene);

    void
    renderUI();

    void
    shutDown();

    void
    showSceneGraph(Scene* sg);

    void
    drawSceneGraphNode(GameObject& node);

    void
    showInspector(GameObject& gameObj);
    
    void
    showSceneWindow();

#pragma region COMPONENT_UI

    void
    drawTransform(Transform& transform);

    void
    drawCamera(Camera& cam);

    void
    drawMaterial(Material& mat);

    void
    drawModel(Model& model);

    void
    drawMesh(Mesh& mesh);

#pragma endregion COMPONENT_UI

    //Ugly ass reference to the node selected in the hierarchy 
    GameObject* m_selectedNode;

  protected:

    void
    onShutdown() override;

    ShrdPtr<Device> pgfxDevice;
    HWND windowHandle;
    ShrdPtr<SceneGraph> sc;
    Vector2 m_sceneGraphSize = Vector2::ZERO;
    Vector2 m_sceneGraphPos = Vector2::ZERO;
    Vector2 m_mainViewSize = Vector2::ZERO;
    Vector2 m_mainViewPos = Vector2::ZERO;
    Vector2 m_detailsSize = Vector2::ZERO;
    Vector2 m_detailsPos = Vector2::ZERO;
    

  };