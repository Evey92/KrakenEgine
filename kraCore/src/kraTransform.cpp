#include "kraTransform.h"

namespace kraEngineSDK {

  CLASS_DEFINITION(Component, Transform)

  void 
  Transform::setPosition(Vector3 newPosition)
  {
    Position = newPosition;
    m_dirty = true;
    
  }

  Vector3 
  Transform::getPosition()
  {
    return Position;
  }

  void
  Transform::setRotation(Vector3 newRot)
  {
    Rotation = newRot;
    m_dirty = true;
  }

  Vector3
  Transform::getRotation()
  {
    return Rotation;
  }

  void
  Transform::setScale(Vector3 newScale)
  {
    Scale = newScale;
    m_dirty = true;
  }

  Vector3
  Transform::getScale()
  {
    return Scale;
  }

  Matrix4
    Transform::getTransformMatrix()
  {

    if (m_dirty) {
      createTransformMat();
      m_dirty = false;
    }

    return m_transformMatrix;
  }


  void
  Transform::createTransformMat()
  {

    //Translate matrix
    Matrix4 T = Matrix4::IDENTITY;

    T.m[3][0] = Position[0];
    T.m[3][1] = Position[1];
    T.m[3][2] = Position[2];
       
    //TODO: Rotate with Quaternions. This is kinda dirty. 

    //Rotation matrix
    Matrix4 Rx;
    Rx.MatrixRotX(kraMath::DEG2RAD(Rotation[0]));
    
    Matrix4 Ry;
    Ry.MatrixRotY(kraMath::DEG2RAD(Rotation[1]));

    Matrix4 Rz;
    Rz.MatrixRotZ(kraMath::DEG2RAD(Rotation[2]));

    Matrix4 R = Rz * Ry * Rx;

    //Scale matrix
    Matrix4 S;

    S.m[0][0] = Scale[0];
    S.m[1][1] = Scale[1];
    S.m[2][2] = Scale[2];

    m_transformMatrix = T * R * S;
    m_transformMatrix.m[3][3] = 1.0f;
  }

}
