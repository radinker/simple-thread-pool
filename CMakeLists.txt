#
# CMakeLists.txt
#
# Copyright (c) 2023 Jose Arboleda
# MIT License
#

cmake_minimum_required(VERSION 3.18)

# Project name and version
project(SimpleThreadPool VERSION 1.3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(threadPoolExample ThreadPool/SPThreadPool.cpp Job/SPJob.cpp ThreadReport/SPThreadReport.cpp main.cpp)

configure_file(SPConfig.hpp.in SPConfig.hpp)

# Includes
target_include_directories(threadPoolExample PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(threadPoolExample PUBLIC ThreadPool ThreadReport Job FunctionCall Example)

# Link libraries
find_package(Threads REQUIRED)
target_link_libraries(threadPoolExample Threads::Threads)
