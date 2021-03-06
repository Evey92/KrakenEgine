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
  Camera::SetPosition(Vector3 _pos) {
    
    /*m_pos.x = Pos.x;
    m_pos.y = Pos.y;
    m_pos.z = Pos.z;*/
    m_pos = _pos;
    m_owner->getComponent<Transform>().setPosition(_pos);
    m_dirty = true;
  }

  void
  Camera::SetPosition(float X, float Y, float Z) {
   
    m_pos.x = X;
    m_pos.y = Y;
    m_pos.z = Z;
    m_owner->getComponent<Transform>().setPosition(m_pos);

    m_dirty = true;
  }

  Vector3
  Camera::getPosition() {
    return m_owner->getComponent<Transform>().getPosition();
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
    m_dirty = true;

  }

  void Camera::setFOVfromDeg(float FOV)
  {
    m_fov = kraMath::DEG2RAD(FOV);
    m_dirty = true;
  }

  float Camera::getPitch()
  {
    return m_pos.y - m_objective.y;
  }

  float Camera::getYaw()
  {
    return m_pos.x - m_objective.x;
  }

  float
  Camera::getFOV() {
    return m_fov;
  }

  float Camera::getFOVAsDeg()
  {
    return kraMath::RAD2DEG(m_fov);
  }

  void
  Camera::setNearPlane(float nearZ) {
    m_nearZ = nearZ;
    m_dirty = true;

  }

  float
  Camera::getNearPlane() {
    return m_nearZ;

  }

  void
  Camera::setFarPlane(float farZ) {
    m_farZ = farZ;
    m_dirty = true;

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
    //TODO: FIX THIS. SOON.
    Vector3 transPos = m_owner->getComponent<Transform>().getPosition();
    if (m_pos != transPos) {
      SetPosition(transPos);
    }
    
    float yAngle = m_owner->getComponent<Transform>().getRotation().y;
    //TODO: Fix this. Hear me out... I need a quick way to rotate... so this will have to do for now.
    if (yAngle != oldRotation.y) {
      m_objective = m_pos + Vector3(kraMath::cos(kraMath::DEG2RAD(yAngle)), 0, kraMath::sin(kraMath::DEG2RAD(yAngle)));
      oldRotation.y = yAngle;
      m_dirty = true;
    }

    if (m_dirty) {
      createViewMat();
    }

    return m_viewMat;
  }

  Matrix4 
  Camera::GetProjedctionMatrix(float width, float height)
  {
    if (m_dirty) {
      updateProjectionMAtrix(width, height);
    }

    return m_projectionMat;
  }

  void
  Camera::createViewMat() {
    
    /*
    TODO: Implement check for coordinate system
    if(rightHanded)
    m_viewMat = Matrix4::MatrixLookAtRH(m_pos, m_objective, m_up);
    else
    */
    m_viewMat = Matrix4::MatrixLookAtLH(m_pos, m_objective, m_up);

    m_dirty = false;

  }

  void 
  Camera::updateProjectionMAtrix(float width, float height)
  {

    m_projectionMat.MatrixPerspectiveFOVLH(m_fov,
                                           width,
                                           height,
                                           m_nearZ,
                                           m_farZ);
    m_dirty = false;
  }

  void
  Camera::Yaw(float angle)
  {
    m_front = m_front * kraMath::cos(angle * (kraMath::PI/180)) - (m_right * kraMath::sin(angle * kraMath::PI/180.0f));
    m_front.normalized();
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