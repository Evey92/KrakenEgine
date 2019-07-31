#include "kraCamera.h"

namespace kraEngineSDK {

  CLASS_DEFINITION(Component, Camera)


  void 
  Camera::MoveForward(float defaz) 
  {
    m_pos += m_front * defaz;
    m_objective += m_front * defaz;
    
    m_dirty = true;
  }

  void
  Camera::MoveRight(float defaz) 
  {
    m_pos += m_right * defaz;
    m_objective += m_right * defaz;
    m_dirty = true;

  }

  void 
  Camera::MoveUP(float defaz)
  {
    m_pos += m_up * defaz;
    m_objective += m_up* defaz;
    m_dirty = true;

  }


  void 
  Camera::Rotate(Vector3& Axis, float angle)
  {
    
    m_dirty = true;

  }

  void
  Camera::RotateYAxis(float angle)
  {

  }

  void
  Camera::SetPosition(Vector3 Pos) {
    
    m_pos.x = Pos.x;
    m_pos.y = Pos.y;
    m_pos.z = Pos.z;
    m_dirty = true;
  }

  void
  Camera::SetPosition(float X, float Y, float Z) {
   
    m_pos.x = X;
    m_pos.y = Y;
    m_pos.z = Z;

    m_dirty = true;
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

    m_dirty = true;

  }

  void
  Camera::SetObjecive(float X, float Y, float Z) {
    m_objective.x = X;
    m_objective.y = Y;
    m_objective.z = Z;

    m_dirty = true;

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

  float& const
  Camera::getFarPlane() {
    return m_farZ;
  }

  void
  Camera::setUp(Vector3 UP) {
    m_up = UP;
    m_dirty = true;

  }

  void
  Camera::setUp(float X, float Y, float Z) {
    m_up.x = X;
    m_up.y = Y;
    m_up.z = Z;
    m_dirty = true;

  }

  void
  Camera::setFront(Vector3 Front) {
    m_front = Front;
    m_dirty = true;

  }

  void
  Camera::setFront(float X, float Y, float Z) {
    m_front.x = X;
    m_front.y = Y;
    m_front.z = Z;
    m_dirty = true;

  }

  Vector3& const
  Camera::getFront() {
    return m_front;
  }

  void
  Camera::setRight(Vector3 Right) {
    m_right = Right;
    m_dirty = true;

  }

  void
  Camera::setRight(float X, float Y, float Z) {
    m_right.x = X;
    m_right.y = Y;
    m_right.z = Z;
    m_dirty = true;

  }

  Matrix4 
  Camera::GetViewMatrix() 
  {
    
    if (m_dirty) {
      createViewMat();
    }

    return m_viewMat;
  }

  void
  Camera::createViewMat() {
    
    m_viewMat = Matrix4::MatrixLookAtLH(m_pos, m_objective, m_up);

    m_dirty = false;

  }

  void 
  Camera::Yaw(float angle)
  {
    m_front = m_front * kraMath::cos(angle * (kraMath::PI/180)) - (m_right * kraMath::sin(angle * kraMath::PI/180.0f));
    m_front.normalize();
    m_right = m_front ^ m_up;
    
    m_dirty = true;

  }

  void 
  Camera::Pitch(float angle)
  {
    Rotate(m_right, angle);
    m_dirty = true;

  }

  void Camera::Roll(float angle)
  {
    Rotate(m_front, angle);
    m_dirty = true;

  }
   


}