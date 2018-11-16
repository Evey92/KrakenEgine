#pragma once
#include "kraPrerequisitesUtil.h"
#include "kraVertex.h"
#include <d3d11.h>
#include <vector>
#include <string>

#   define PLUGIN_EXPORT __declspec(dllexport);

/*****************************************************************************************************************************************************/
/**
  DLL export
*/
/*****************************************************************************************************************************************************/

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
# if KRA_COMPILER == KRA_COMPILER_MSVC
#   if defined ( KRA_STATIC_LIB )
#     define KRA_UTILGFX_EXPORT
#   else
#     if defined( KRA_UTILGFX_EXPORTS )
#       define KRA_UTILGFX_EXPORT __declspec( dllexport )
#     else
#       define KRA_UTILGFX_EXPORT __declspec( dllimport )
#     endif
#   endif
# else
#   if defined( KRA_STATIC_LIB )
#     defined KRA_UTILGFX_EXPORT
#   else
#     if defined( KRA_UTILGFX_EXPORTS )
#       define KRA_UTILGFX_EXPORT __attribute__ ((dllexport))
#     else
#       define KRA_UTILGFX_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define KRA_UTILGFX_HIDDEN
#else
# define KRA_UTILGFX_EXPORT __attribute__ ((visibility ("default")))
# define KRA_UTILGFX_EXPORT __attribute__ ((visibility ("hidden")))
#endif