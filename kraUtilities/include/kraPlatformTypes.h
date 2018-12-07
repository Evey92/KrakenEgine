#pragma once

#include <cstdint>
#include "kraPlatformDefines.h"

#if KRA_PLATFORM == KRA_PLATFORM_PS4
#include <scebase.h>
#endif

namespace kraEngineSDK {

  using std::uint8_t;
  using std::uint16_t;
  using std::uint32_t;
  using std::uint64_t;
  using std::int8_t;
  using std::int16_t;
  using std::int32_t;
  using std::int64_t;

/*****************************************************************************/
/**
 * Basic unsigned types
 */
 /*****************************************************************************/

  using uint8 = uint8_t;
  using uint16 = uint16_t;
  using uint32 = uint32_t;
  using uint64 = uint64_t;

/*****************************************************************************/
/**
 * Basic unsigned types
 */
 /*****************************************************************************/

  using int8 = int8_t;
  using int16 = int16_t;
  using int32 = int32_t;
  using int64 = int64_t;

 /*****************************************************************************/
/**
 * @class  Qword
 * @brief
 */
 /*****************************************************************************/

  MS_ALIGN(16) class QWord
  {
    /**
    * Constructor
    */

   public:
     QWord() : m_lower(0), m_upper(0) {}
     explicit QWord(bool from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(uint8 from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(int8 from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(uint16 from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(int16 from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(uint32 from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(int32 from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(uint64 from) : m_lower(from), m_upper(0) {}
     explicit QWord(int64 from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(float from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}
     explicit QWord(double from) : m_lower(static_cast<uint64>(from)), m_upper(0) {}

     operator int64() const { return static_cast<uint64>(m_lower); }


   public:
     uint64 m_lower;
     int64 m_upper;
  }GCC_ALIGN(16);

/*****************************************************************************/
/**
 * Character types
 */
 /*****************************************************************************/
#if KRA_COMPILER == KRA_COMPILER_MSVC || KRA_PLATFORM == KRA_PLATFORM_PS4
  using WCHAR = wchar_t;
#else
  using WCHAR = unsigned short;
#endif
  using ANSICHAR = char;
  using UNICHAR = WCHAR;

/*****************************************************************************/
/**
 * NULL data type
 */
 /*****************************************************************************/

  using TYPE_OF_NULL = int32;

/*****************************************************************************/
/**
 * SIZE_T is architecture dependant data type
 */
 /*****************************************************************************/

  using SIZE_T = size_t;

}