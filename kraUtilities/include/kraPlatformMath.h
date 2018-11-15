#pragma once

#include "kraPlatformTypes.h"
#include <cmath>
#include <algorithm> 

namespace kraEngineSDK {
  struct KRA_UTILITY_EXPORT kraPlatformMath
  {
   public:
    static const float PI;
    static const float DEGREE;
    static const float RADIAN;
    static const float EULER;
    
    /**
    * @brief Trigonometric functions
    */
    template<typename T>
    static T 
    cos(T rads) {
      return std::cos(rads);
    }

    template<typename T>
     static T
    sin(T rads) {
      return std::sin(rads);
    }

    template<typename T>
    static T
    tan(T rads) {
      return std::tan(rads);
    }

    template<typename T>
    static T 
    acos(T rads) {
      return std::acos(rads);
    }

    template<typename T>
    static T
    asin(T rads) {
      return std::asin(rads);
    }

    template<typename T>
    static T 
    atan(T rads) {
      return std::atan(rads);
    }

    template<typename T>
    static T 
    atan2(T T1, T T2) {
      return std::atan2(T1, T2);
    }

    /**
    * @brief Hyperbolic functions
    */
    template<typename T>
    static T 
    cosh(T rads) {
      return std::cosh(rads);
    }

    template<typename T>
    static T 
    sinh(T rads) {
      return std::sinh(rads);
    }

    template<typename T>
    static T 
    tanh(T rads) {
      return std::tanh(rads);
    }

    template<typename T>
    static T 
    acosh(T rads) {
      return std::acosh(rads);
    }

    template<typename T>
    static T 
    asinh(T rads) {
      return std::asinh(rads);
    }

    template<typename T>
    static T 
    atanh(T rads) {
      return std::atanh(rads);
    }

    /**
    * @brief Exponential and logarithmic functions
    */
    template<typename T>
    static T 
    exp(T val) {
      return std::exp(val);
    }

    template<typename T>
    static T 
    fractional(T val) {
      return std::modf(val);
    }

    template<typename T>
    static T
    log(T val) {
      return std::log(val);
    }

    template<typename T>
    static T 
    log2(T val) {
      return std::log2(val);
    }

    template<typename T>
    static T 
    log10(T val) {
      return std::log10(val);
    }

    /**
    * @brief Power functions
    */
    template<typename T>
    static T 
    pow(T val, T pow) {
      return std::pow(val, pow);
    }

    template<typename T>
    static float 
    powf(T val, T pow) {
      return static_cast<float>(std::pow(val, pow));
    }

    template<typename T>
    static T 
    sqr(T val) {
      return val*val;
    }

    template<typename T>
    static T 
    sqrt(T val) {
      return std::sqrt(val);
    }

    template<typename T>
    static T 
    invSqrt(T val) {
      return 1.0f/std::sqrt(val);
    }
    
    template<typename T>
    static T 
    hypot(T val) {
      return std::hypot(val);
    }

    /**
    * @brief Rounding and remainder functions
    */
    
    template<typename T>
    static T 
    ceil(T val) {
      return std::ceil(val);
    }

    template<typename T>
    static T 
    floor(T val) {
      return std::floor(val);
    }

    //template<typename T>
    //static T 
    //ceil(T val) {
    //  return std::ceil(val);
    //}

    template<typename T>
    static T 
    round(T val) {
      return std::round(val);
    }

    /**
    * @brief Fast functions
    */
    template<typename T>
    static T 
    fastSin(T Ta, double precision) {
      T sine = Ta;
      bool isNeg;
      isNeg = true;
      for (double i = 3; i <= precision; i += 2)
      {
        if (isNeg) {
          sine -= pow(Ta, i) / factorial(i);
          isNeg = false;
        }
        else {
          sine += pow(Ta, i) / factorial(i);
          isNeg = true;
        }
      }
      return sine;
    }

    /**
    * @brief Minimum, maximum, difference functions
    */

    template<typename T>
    static T 
    fdim(T val) {
      return std::fdim(val);
    }

    template<typename T>
    static T 
    fmax(T val1, T val2) {
      return std::fmax(val1, val2);
    }

    template<typename T>
    static T 
    fmin(T val, T val2) {
      return std::fmin(val, val2);
    }

    template<typename T>
    static T 
    max3(T val, T val2, T val3) {
      return std::fmax(fmax(val, val2),val3);
    }

    template<typename T>
    static T 
    min3(T val, T val2, T val3) {
      return std::fmin(fmin(val, val2), val3);
    }

    /**
    * @brief Misc functions
    */

    template<class T>
    static T 
    abs(T val) {
      return std::abs(val);
    }

    template<class T>
    static T 
    lerp(T a, T b, float scale) {
      return (a + (b - a)* scale);
    }

    /**
    * @brief Spherical Lerp
    */

    /*template<class T>
    static T slerp(T val) {
      return std::(val);
    }*/
    
    template<class T>
    static T 
    clamp(T val) {
      return std::clamp(val);
    }

    template<class T>
    static T 
    factorial(T x) {
      double result = 1;
      for (int i = 1; i <= x; i++)
        result *= i;
      return result;
    }
  };
}