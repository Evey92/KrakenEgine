#pragma once
class kraQuaternion
{
public:
  kraQuaternion(float x, float y, float z, float w)
    : m_x(x), m_y(y), m_z(z), m_w(w) {}
  ~kraQuaternion() = default;

#pragma region PUBLIC_METHODS
  
  

#pragma endregion PUBLIC_METHODS

  /**
   * @brief Component X.
   */
  float m_x;
  /**
   * @brief Component Y.
   */
  float m_y;
  /**
   * @brief Component Z.
   */
  float m_z;
  /**
   * @brief Component W.
   */
  float m_w;
};

