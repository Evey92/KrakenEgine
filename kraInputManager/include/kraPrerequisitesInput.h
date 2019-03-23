#pragma once
#include <kraPrerequisitesUtil.h>
#include <gainput/gainput.h>

/*****************************************************************************************************************************************************/
/**
  DLL export
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
# if KRA_COMPILER == KRA_COMPILER_MSVC
#   if defined ( KRA_STATIC_LIB )
#     define KRA_UTILINPUT_EXPORT
#   else
#     if defined( KRA_UTILINPUT_EXPORTS )
#       define KRA_UTILINPUT_EXPORT __declspec( dllexport )
#     else
#       define KRA_UTILINPUT_EXPORT __declspec( dllimport )
#     endif
#   endif
# else
#   if defined( KRA_STATIC_LIB )
#     defined KRA_UTILINPUT_EXPORT
#   else
#     if defined( KRA_UTILINPUT_EXPORTS )
#       define KRA_UTILINPUT_EXPORT __attribute__ ((dllexport))
#     else
#       define KRA_UTILINPUT_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define KRA_UTILINPUT_HIDDEN
#else
# define KRA_UTILINPUT_EXPORT __attribute__ ((visibility ("default")))
# define KRA_UTILINPUT_EXPORT __attribute__ ((visibility ("hidden")))
#endif