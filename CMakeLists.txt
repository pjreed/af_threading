# Copyright (c) 2018, ArrayFire
# All rights reserved.
#
# This file is distributed under 3-clause BSD license.
# The complete license agreement can be obtained at:
# http://arrayfire.com/licenses/BSD-3-Clause

cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.5)
project(af_threads
  VERSION 3.7.2
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(ArrayFire REQUIRED)
find_package(Threads REQUIRED)

add_executable(af_threads src/test.cpp)
target_link_libraries(af_threads
  ArrayFire::afcuda
  Threads::Threads
)
