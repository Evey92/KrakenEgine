/*************************************************

Aquí irá mi cabecera

*/

#pragma once

#define KRA_PLATFORM_WIN32   1 //Windows Platform
#define KRA_PLATFORM_LINUX   2 //Linux Platform
#define KRA_PLATFORM_OSX     3 //Apple Platform
#define KRA_PLATFORM_IOS     4 //iPhone Platform
#define KRA_PLATFORM_ANDROID 5 //Android Platform
#define KRA_PLATFORM_PS4     6 //Playstation 4 Platform

#define KRA_COMPILER_MSVC    1 // Platform
#define KRA_COMPILER_GNUC    2 //Windows Platform
#define KRA_COMPILER_INTEL   3 //Windows Platform
#define KRA_COMPILER_CLANG   4 //Windows Platform

#define KRA_ARCHITECTURE_X86_32   1 //Windows Platform
#define KRA_ARCHITECTURE_X86_64   2 //Windows Platform

#define KRA_ENDIAN_LITTLE    1 //Windows Platform
#define KRA_ENDIAN_BIG       2 //Windows Platform


#define KRA_ENDIAN KRA_ENDIAN_LITTLE

#if defined (__clang__)
# define KRA_COMPILER KRA_COMPILER_CLANG
# define KRA_COMP_VER __clang_version__
# define KRA_THREADLOCAL __thread
# define KRA_STDCALL __attribute__((stdcall))
# define KRA_CDECL __attribute__((cdecl))
# define KRA_FALLTHROUGH [[clang::fallthrough]];

#elifif defined (__GNUC__)
# define KRA_COMPILER KRA_COMPILER_GNUC
# define KRA_COMP_VER (((__GNUC__)*100) + (__GNUC_MINOR__ *10) + __GNUC_PATCHLEVEL__)
# define KRA_THREADLOCAL __thread
# define KRA_STDCALL __attribute__((stdcall))
# define KRA_CDECL __attribute__((cdecl))
# define KRA_FALLTHROUGH [[clang::fallthrough]];

#elif defined (__INTEL_COMPILER)
# define KRA_COMPILER KRA_COMPILER_INTEL
# define KRA_COMP_VER __INTEL__COMPILER
# define KRA_THREADLOCAL __thread
# define KRA_STDCALL __stdcall
# define KRA_CDECL __cdecl
# define KRA_FALLTHROUGH 

#elif defined (_MSC_VER)
# define KRA_COMPILER KRA_COMPILER_MSVC
# define KRA_COMP_VER _MSVC_VER
# define KRA_THREADLOCAL __declspec(thread)
# define KRA_STDCALL __stdcall
# define KRA_CDECL __cdecl
# define KRA_FALLTHROUGH 
# undef __PRETTY_FUNCTION__
# define __PRETTY_FUNCTION__ __FUNCSIG__
#else

# pragma error "No known compiler. "
#endif

/*****************************************************************************************************************************************************/
#if KRA_COMPILER == KRA_COMPILER_MSVC
# if KRA_COMP_VER > 1200
#   define FORCEINLINE __forceinline
#   ifndef RESTRICT
#     define RESTRICT __restrict
#   endif
# endif
#elif defined(__MINGW32__)
# if !defined(FORCEINLINE)
#   define FORCELINE __inline
#   ifndef RESTRICT
#     define RESTRICT
#   endif
#endif
#else
# define FORCELINE __inline
# ifndef RESTRICT
#   define RESTRICT __restrict
#endif
#endif 

/*****************************************************************************************************************************************************/
/**
  Finds current platform
*/
/*****************************************************************************************************************************************************/

#if defined(__WIN32__) || defined(_WIN32)
# define KRA_PLATFORM KRA_PLATFORM_WIN32
#elif defined(__APPLE_CC__)
# define KRA_PLATFORM KRA_PLATFORM_OSX
#elif defined(__ORBIS__)
# define KRA_PLATFORM KRA_PLATFORM_PS4
#else
# define KRA_PLATFORM KRA_PLATFORM_LINUX
#endif

/*****************************************************************************************************************************************************/
/**
  Finds current architecture
*/
/*****************************************************************************************************************************************************/

#if defined(__x86_64__) || defined(_M_X64)
# define KRA_ARCH_TYPE KRA_ARCHITECTURE_x86_64
#else
# define KRA_ARCH_TYPE KRA_ARCHITECTURE_x86_32
#endif

/*****************************************************************************************************************************************************/
/**
  Memory Alignment macros
*/
/*****************************************************************************************************************************************************/

#if KRA_COMPILER == KRA_COMPILER_MSVC
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#   define GCC_PACK(n)
# endif
# ifndef GCC_ALIGN
#   define GCC_ALIGN(n)
# endif
#elif ( KRA_COMPILER == KRA_COMPILER_GNUC && KRA_PLATFORM == KRA_PLATFORM_PS4 )
# define MS_ALIGN(n)
# define GCC_PACK(n)
# define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#else
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__( (packed, __aligned__(n)) )
# define GCC_ALIGN(n) __attribute__( (aligned(n)) )
#endif

/*****************************************************************************************************************************************************/
/**
  Trhow
*/
/*****************************************************************************************************************************************************/

#if KRA_COMPILER == KRA_COMPILER_MSVC
# define _NOEXCEPT noexcept
#elif KRA_COMPILER == KRA_KOPILER_INTEL
# define _NOEXCEPT noexcept
#elif KRA_COMPILER == KRA_KOPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif

/*****************************************************************************************************************************************************/
/**
  Library export specifics
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
# if KRA_COMPILER == KRA_COMPILER_MSVC
#   if defined ( KRA_STATIC_LIB )
#     define KRA_UTILITY_EXPORT
#   else
#     if defined( KRA_UTILITY_EXPORTS )
#       define KRA_UTILITY_EXPORT __declspec( dllexport )
#     else
#       define KRA_UTILITY_EXPORT __declspec( dllimport )
#     endif
#   endif
# else
#   if defined( KRA_STATIC_LIB )
#     defined KRA_UTILITY_EXPORT
#   else
#     if defined( KRA_UTILITY_EXPORTS )
#       define KRA_UTILITY_EXPORT __attribute__ ((dllexport))
#     else
#       define KRA_UTILITY_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define KRA_UTILITY_HIDDEN
#else
# define KRA_UTILITY_EXPORT __attribute__ ((visibility ("default")))
# define KRA_UTILITY_EXPORT __attribute__ ((visibility ("hidden")))
#endif

/*****************************************************************************************************************************************************/
/**
  DLL export for plugins
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
# if KRA_COMPILER == KRA_COMPILER_MSVC
#   define KRA_PLUGIN_EXPORT __declspec(dllexport)
# else
#   define KRA_PLUGIN_EXPORT __attribute__((dllexport))
# endif
# define KRA_UYILITY_HIDDEN
#else
# define KRA_PLUGIN_EXPORT __attribute__ ((visibility ("default")))
#endif

/*****************************************************************************************************************************************************/
/**
  Windows specific Settings
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
# if defined(_DEBUG) || defined(DEBUG)
#   define KRA_DEBUG_MODE 1
# else
#   define KRA_DEBUG_MODE 0
# endif
# if KRA_COMPILER == KRA_COMPILER_INTEL
#   define KRA_THREADLOCAL __delspec(thread)
# endif
#endif

/*****************************************************************************************************************************************************/
/**
  LINUX specific Settings
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_LINUX || KRA_PLATFORM == KRA_PLATFORM_OSX
# define stricmp strcasecmp

//If we are on debug build

# if defined(_DEBUG) || defined(DEBUG)
#   define KRA_DEBUG_MODE 1
# else
#   define KRA_DEBUG_MODE 0
# endif
# if KRA_COMPILER == KRA_COMPILER_INTEL
#   define KRA_THREADLOCAL __thread
# endif
#endif

/*****************************************************************************************************************************************************/
/**
  PS4 specific Settings
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_PS4

# if defined(_DEBUG) || defined(DEBUG)
#   define KRA_DEBUG_MODE 1
# else
#   define KRA_DEBUG_MODE 0
# endif
#endif

/*****************************************************************************************************************************************************/
/**
  Definition debug macros
*/
/*****************************************************************************************************************************************************/

#if KRA_DEBUG_MODE
# define KRA_DEBUG_ONLY(x) x
# define KRA_ASSERT(x) assert(x)
#else
# define KRA_DEBUG_ONLY(x)
# define KRA_ASSERT(x)
#endif

/*****************************************************************************************************************************************************/
/**
  Disable some compiler warnings
*/
/*****************************************************************************************************************************************************/

#if KRA_COMPILER == KRA_COMPILER_MSVC
/*
*       
*
*/
# define _CRT_SECURE_NO_WARNINGS

# pragma warning (disabled: 4251)

# pragma warning (disabled: 4996)

# pragma warning (disabled: 4503)

#endif
