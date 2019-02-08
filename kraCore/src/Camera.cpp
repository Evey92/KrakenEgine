#include "Camera.h"

namespace kraEngineSDK {

  Camera::Camera() {
  
  }
  Camera::Camera(Vector3 Pos, Vector3 objective, Vector3  UP)
  {

  }

  /*Camera::Camera(Vector3 Pos, Vector3 dir, Vector3 UP)
  {

  }*/

  void Camera::MoveForward(float defaz) 
  {
    m_pos += m_front * defaz;
  }

  void Camera::MoveRight(float defaz) 
  {

  }

  /*void Camera::Rotate(vector Axis, float angle)
  {

  }*/

 /* void Camera::Rotate(Vector3::UP, float angle) 
  {

  }*/

  Matrix4 Camera::GetViewMatrix(Vector3 objective, Vector3 UP) 
  {
      return m_viewMat.MatrixLookAtLH(m_pos, objective, UP);
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