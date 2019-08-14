#pragma once

#include <kraPrerequisitesUtil.h>
#include <kraPrerequisitesCore.h>



/*****************************************************************************************************************************************************/
/**
  DLL export
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
# if KRA_COMPILER == KRA_COMPILER_MSVC
#   if defined ( KRA_STATIC_LIB )
#     define KRA_RENDERER_EXPORT
#   else
#     if defined( KRA_RENDERER_EXPORTS )
#       define KRA_RENDERER_EXPORT __declspec( dllexport )
#     else
#       define KRA_RENDERER_EXPORT __declspec( dllimport )
#     endif
#   endif
# else
#   if defined( KRA_STATIC_LIB )
#     defined KRA_RENDERER_EXPORT
#   else
#     if defined( KRA_RENDERER_EXPORTS )
#       define KRA_RENDERER_EXPORT __attribute__ ((dllexport))
#     else
#       define KRA_RENDERER_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define KRA_RENDERER_HIDDEN
#else
# define KRA_RENDERER_EXPORT __attribute__ ((visibility ("default")))
# define KRA_RENDERER_HIDDEN __attribute__ ((visibility ("hidden")))
#endif