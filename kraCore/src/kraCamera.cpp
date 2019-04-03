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
    dirty = true;
  }

  void Camera::MoveRight(float defaz) 
  {
    m_pos += m_right * defaz;
    dirty = true;

  }

  void Camera::Rotate(Vector3 Axis, float angle)
  {
    if (Axis == Vector3(1.0f, 0.0f, 0.0f))
    {
      //Do something
    }
    if (Axis == Vector3(0.0f, 1.0f, 0.0f))
    {
      //Do something
    }
    if (Axis == Vector3(0.0f, 0.0f, 1.0f))
    {
      //Do something
    }
    dirty = true;

  }

  void
  Camera::SetPosition(Vector3 Pos) {
    
    m_pos.x = Pos.x;
    m_pos.y = Pos.y;
    m_pos.z = Pos.z;
    dirty = true;
  }

  void
  Camera::SetPosition(float X, float Y, float Z) {
   
    m_pos.x = X;
    m_pos.y = Y;
    m_pos.z = Z;

    dirty = true;
  }

  Vector3
  Camera::getPosition() {
    return m_pos;
  }


  void
  Camera::SetObjecive(Vector3 Objective) {

    m_objective.x = Objective.x;
    m_objective.y = Objective.y;
    m_objective.z = Objective.z;

    dirty = true;

  }

  void
  Camera::SetObjecive(float X, float Y, float Z) {
    m_objective.x = X;
    m_objective.y = Y;
    m_objective.z = Z;

    dirty = true;

  }

  Vector3
  Camera::getObjective() {
    return m_objective;
  }

  void
  Camera::setFOV(float FOV) {
    m_fov = FOV;
  }

  float
  Camera::getFOV() {
    return m_fov;
  }

  void
  Camera::setNearPlane(float nearZ) {
    m_nearZ = nearZ;
  }

  float
  Camera::getNearPlane() {
    return m_nearZ;
  }

  void
  Camera::setFarPlane(float farZ) {
    m_farZ = farZ;
  }

  float
  Camera::getFarPlane() {
    return m_farZ;
  }

  void
  Camera::setUp(Vector3 UP) {
    m_up = UP;
    dirty = true;

  }

  void
  Camera::setUp(float X, float Y, float Z) {
    m_up.x = X;
    m_up.y = Y;
    m_up.z = Z;
    dirty = true;

  }

  void
  Camera::setFront(Vector3 Front) {
    m_front = Front;
    dirty = true;

  }

  void
  Camera::setFront(float X, float Y, float Z) {
    m_front.x = X;
    m_front.y = Y;
    m_front.z = Z;
    dirty = true;

  }

  void
  Camera::setRight(Vector3 Right) {
    m_right = Right;
    dirty = true;

  }

  void
  Camera::setRight(float X, float Y, float Z) {
    m_right.x = X;
    m_right.y = Y;
    m_right.z = Z;
    dirty = true;

  }

  Matrix4 
  Camera::GetViewMatrix() 
  {
    
    if (dirty) {
      createViewMat();
    }

    return m_viewMat;
  }

  void
  Camera::createViewMat() {
    
    m_viewMat = Matrix4::MatrixLookAtLH(m_pos, m_objective, m_up);

    dirty = false;

  }

  void Camera::Yaw(float angle)
  {
    Rotate(m_up, angle);
    dirty = true;

  }

  void Camera::Pitch(float angle)
  {
    Rotate(m_right, angle);
    dirty = true;

  }

  void Camera::Roll(float angle)
  {
    Rotate(m_front, angle);
    dirty = true;

  }
   


}