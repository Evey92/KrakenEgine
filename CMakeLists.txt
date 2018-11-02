cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(kraUtilityTest)
include(gtest.cmake)

#Prerequisites
set(CMAKE_CXX_FLAGS)

#This variables are for setting the minimum and maximun requires for unitTesting
set(UNITTESTING_VERSION_MAJOR 1)
set(UNITTESTING_VERSION_MINOR 0)
set(LEARN_CMAKE_VERSION_PATCH 0)

#sets cmake to debug build
set(CMAKE_BUILD_TYPE Debug)



#creates an executable which can be used to run in travis
add_executable(kraUtilityTest kraUtilities_UnitTest/main.cpp)

find_package (Threads)
target_link_libraries(kraUtilities_UnitTest gtest ${CMAKE_THREAD_LIBS_INIT})