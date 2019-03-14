#include "kraCamera.h"

namespace kraEngineSDK {

  Camera::Camera() {
  
  }
  Camera::Camera(Vector3 Pos, 
                 Vector3 objective = Vector3::FRONT, 
                 Vector3  UP = Vector3::UP)
  {
    m_pos = Pos;
    m_objective = objective;
    m_up = UP;
  }

  void Camera::MoveForward(float defaz) 
  {
    m_pos += m_front * defaz;
  }

  void Camera::MoveRight(float defaz) 
  {

  }

  void Camera::Rotate(Vector3 Axis, float angle)
  {

  }

  void
  Camera::SetPosition(Vector3 Pos) {
    
    m_pos = Pos;
    dirty = true;
  }

  void
  Camera::SetPosition(float X, float Y, float Z) {
   
    m_pos.x = X;
    m_pos.y = Y;
    m_pos.z = Z;

    dirty = true;
  }

  void
  Camera::SetObjecive(Vector3 Objective) {

    m_objective = Objective;

    dirty = true;

  }

  void
  Camera::SetObjecive(float X, float Y, float Z) {
    m_objective.x = X;
    m_objective.y = Y;
    m_objective.z = Z;

    dirty = true;

  }

  Matrix4 Camera::GetViewMatrix(Vector4 objective, Vector4 UP) 
  {
      return m_viewMat.MatrixLookAtLH(Vector4(m_pos, 1.0f), objective, UP);
  }

  void Camera::Yaw(float angle)
  {
    //Rotate(m_up, angle);
  }

  void Camera::Pitch(float angle)
  {
    //Rotate(m_right, angle);
  }

  void Camera::Roll(float angle)
  {
    //Rotate(m_front, angle);
  }
   


}