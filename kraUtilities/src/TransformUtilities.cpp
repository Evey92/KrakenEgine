#include "TransformUtilities.h"

namespace kraEngineSDK {
 
  Matrix4
  Utility::eulerAngleXY(float angleX, float angleY)
  {
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float cosY = cos(angleY);
    float sinY = sin(angleY);

    Matrix4 rotMatrix;
    
    rotMatrix.m[0][0] = cosY; rotMatrix.m[0][1] = -sinX * -sinY; rotMatrix.m[0][2] = cosX * -sinY; rotMatrix.m[0][3] = 0;
    rotMatrix.m[1][0] = 0;    rotMatrix.m[1][1] = cosX;          rotMatrix.m[1][2] = sinX;         rotMatrix.m[1][3] = 0;
    rotMatrix.m[2][0] = sinY; rotMatrix.m[2][1] = -sinX * cosY;  rotMatrix.m[2][2] = cosX * cosY;  rotMatrix.m[2][3] = 0;
    rotMatrix.m[3][0] = 0;    rotMatrix.m[3][1] = 0;             rotMatrix.m[3][2] = 0;            rotMatrix.m[3][3] = 1;

    return rotMatrix;
  }
}