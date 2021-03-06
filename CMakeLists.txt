cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(kraUtilityTest)

#Prerequisites
set(CMAKE_CXX_FLAGS)
SET(COVERAGE OFF CACHE BOOL "Coverage")

include_directories(UTIL_INCLUDE ./kraUtilities/include/)

set(UTIL_SOURCES
    ./kraUtilities/src/kraPlatformMath.cpp
    ./kraUtilities/src/kraAABB.cpp
    ./kraUtilities/src/kraBox2d.cpp
    ./kraUtilities/src/kraFrustrum.cpp
    ./kraUtilities/src/kraMatrix4.cpp
    ./kraUtilities/src/kraOOBB.cpp
    ./kraUtilities/src/kraPlane.cpp
    ./kraUtilities/src/kraQuaternion.cpp
    ./kraUtilities/src/kraRay.cpp
    ./kraUtilities/src/kraSphere.cpp
    ./kraUtilities/src/kraTriangle.cpp
    ./kraUtilities/src/kraVector2.cpp
    ./kraUtilities/src/kraVector3.cpp
    ./kraUtilities/src/kraVector4.cpp
    )

add_library(Utilities SHARED ${UTIL_SOURCES})


#######################################################################################
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(gtestUtil)

include(gtestUtilities.cmake)

set(CMAKE_CXX_FLAGS)
SET(COVERAGE OFF CACHE BOOL "Coverage")
find_package (Threads)

set(UNITTESTING_VERSION_MAJOR 1)
set(UNITTESTING_VERSION_MINOR 0)
set(LEARN_CMAKE_VERSION_PATCH 0)

set(CMAKE_BUILD_TYPE Debug)

enable_testing()

SET(TARGET_SRC ./kraUtilities_UnitTest/main.cpp)

add_executable(UtilitiesTest ${TARGET_SRC})

target_link_libraries(UtilitiesTest Utilities ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(UtilitiesTest gtestUtilities ${CMAKE_THREAD_LIBS_INIT})
