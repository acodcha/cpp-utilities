# Copyright © 2023 Alexandre Coderre-Chabot
#
# This file is licensed under the MIT license. For more information, visit:
#     https://mit-license.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#   - The above copyright notice and this permission notice shall be included in
#     all copies or substantial portions of the Software.
#   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#     FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#     DEALINGS IN THE SOFTWARE.
#
# This file was originally obtained from:
#     https://github.com/acodcha/updatable-priority-queue

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

################################################################################
# Project
################################################################################

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -O3 -Wall -Wno-return-type")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(
  "updatable_priority_queue" VERSION 1.0.0 LANGUAGES CXX
  DESCRIPTION "C++ priority queue with update operation"
  HOMEPAGE_URL "https://github.com/acodcha/physical-quantities"
)

option(BUILD_TESTING "Build testing executable." OFF)

include(CMakePackageConfigHelpers)
include(CTest)
include(GNUInstallDirs)

set(PROJECT_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include/")
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

target_include_directories(
  ${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_INCLUDE_BUILD_DIR}>
  $<INSTALL_INTERFACE:include>
)

################################################################################
# Testing
################################################################################

if(BUILD_TESTING)
  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
  )

  # Do not override the parent project's compiler and linker settings on Windows.
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)

  include(GoogleTest)

  enable_testing()

  add_executable(updatable_priority_queue_test ${PROJECT_SOURCE_DIR}/test/updatable_priority_queue.cpp)
  target_link_libraries(updatable_priority_queue_test GTest::gtest_main)
  gtest_discover_tests(updatable_priority_queue_test)

  message(STATUS "Testing was configured. Build the testing executables with \"make --jobs=16\" and run them with \"make test\"")
else()
  message(STATUS "Testing was not configured. Run \"cmake .. -DBUILD_TESTING=ON\" to configure testing.")
endif()
