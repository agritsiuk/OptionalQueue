cmake_minimum_required(VERSION 3.22)

project(optional_queue
  LANGUAGES CXX
  DESCRIPTION "C++ queue with optional element addition feature"
)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
