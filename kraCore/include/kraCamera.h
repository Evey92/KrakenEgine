#pragma once
#include <kraMatrix4.h>
#include <kraVector3.h>

#include "kraPrerequisitesCore.h"
#include "kraGameObject.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Camera 
  : public Component {
  
    CLASS_DECLARATION(Camera)

  public:

    Camera(const ShrdPtr<GameObject>& owner)
    : Component(owner) {}

    ~Camera() = default;


    void 
    MoveForward(float defaz);

    void 
    MoveRight(float defaz);
    
    void
    MoveUP(float defaz);
    
    void 
    Rotate(Vector3& Axis, float angle);
    
    void
    RotateYAxis(float angle);

    void 
    SetPosition(Vector3 Pos);

    void
    SetPosition(float X, float Y, float Z);

    Vector3
    getPosition();
    
    void
    SetObjecive(Vector3 Objective);

    void
    SetObjecive(float X, float Y, float Z);

    Vector3
    getObjective();

    void
    setFOV(float FOV);
    
    void
    setFOVfromDeg(float FOV);
    
    float
    getPitch();

    float
    getYaw();

    float
    getFOV();

    float
    getFOVAsDeg();

    void
    setNearPlane(float nearZ);
    
    float
    getNearPlane();

    void
    setFarPlane(float farZ);

    float& const
    getFarPlane();

    void
    setUp(Vector3 UP);

    void
    setUp(float X, float Y, float Z);

    void
    setFront(Vector3 Front);

    void
    setFront(float X, float Y, float Z);

    Vector3& const
    getFront();

    void
    setRight(Vector3 Right);

    void
    setRight(float X, float Y, float Z);

    Matrix4 
    GetViewMatrix();

    Matrix4
    GetProjedctionMatrix(float width, float height);
    
    void
    createViewMat();

    void
    updateProjectionMAtrix(float width, float height);

    void 
    Yaw(float angle);
    
    void 
    Pitch(float angle);
    
    void 
    Roll(float angle);

    

  private:
    uint32 m_id = 0;

    bool m_dirty = true;
    Matrix4 m_viewMat;
    Matrix4 m_projectionMat;
    Vector3 m_pos = Vector3::ZERO;
    Vector3 m_objective = Vector3::ZERO;
    Vector3 m_front = Vector3::ONEZ;
    Vector3 m_right = Vector3::ONEX;
    Vector3 m_up = Vector3::ONEY;
    
    float m_fov = kraMath::DEG2RAD(90.0f);
    float m_nearZ = 0.01f;
    float m_farZ = 1000.0f;
    
    //I should probably rework how this works...
    float pitch = 0;
    float yaw = 0;
  };

}