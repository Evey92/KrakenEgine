#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Camera
  {
  public:
    Camera();
    Camera(Vector3 Pos, Vector3 objective, Vector3  UP);
    //Camera(Vector3 Pos, Vector3 dir, Vector3 UP);

    void MoveForward(float defaz);
    void MoveRight(float defaz);
    //void Rotate(vector Axis, float angle);
    //void Rotate(Vector3::UP, float angle);
    void SetPosition(Vector3 Pos);
    void SetObjecive(Vector3 Objective);
    Matrix4 GetViewMatrix(Vector3 objective, Vector3 UP);
    void Yaw(float angle);
    void Pitch(float angle);
    void Roll(float angle);

  private:
    float dirty;
    Matrix4 m_viewMat;
    Vector3 m_pos;
    Vector3 m_front;
    Vector3 m_right;
    Vector3 m_up;

  };

}