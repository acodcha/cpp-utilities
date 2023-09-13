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

# Define the global settings.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -O3 -Wall -Wextra -Wno-return-type -Wpedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)

# Define the project and its options.
project(
  "updatable_priority_queue"
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "C++ priority queue with update operation"
  HOMEPAGE_URL "https://github.com/acodcha/updatable-priority-queue"
)
option(
  TEST_UPDATABLE_PRIORITY_QUEUE
  "Build testing executable."
  OFF
)

# Define the library.
add_library(
  ${PROJECT_NAME}
  INTERFACE
)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Configure the tests.
if(TEST_UPDATABLE_PRIORITY_QUEUE)
  # Search for the GoogleTest library.
  find_package(GTest QUIET)

  if(GTest_FOUND)
    message(STATUS "The GoogleTest library was found at: ${GTest_CONFIG}")
  else()
    # In this case, the GoogleTest library is not found, so fetch it instead.
    include(FetchContent)
    FetchContent_Declare(
      GoogleTest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG main
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(GoogleTest)
    message(STATUS "The GoogleTest library was fetched from: https://github.com/google/googletest.git")
  endif()

  # Include the GoogleTest library and enable testing.
  include(GoogleTest)
  enable_testing()

  # Define the test executables.
  add_executable(updatable_priority_queue_test ${PROJECT_SOURCE_DIR}/test/updatable_priority_queue.cpp)
  target_link_libraries(updatable_priority_queue_test GTest::gtest_main)
  gtest_discover_tests(updatable_priority_queue_test)

  message(STATUS "The library tests were configured. Build the tests with \"make --jobs=16\" and run them with \"make test\"")
else()
  message(STATUS "The library tests were not configured. Run \"cmake .. -DTEST_UPDATABLE_PRIORITY_QUEUE=ON\" to configure the tests.")
endif()
