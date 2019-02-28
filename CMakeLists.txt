cmake_minimum_required(VERSION 3.1.3)

project(string
        VERSION 0.1
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14) #Use C++14

add_executable(tp1 tp1.cpp)

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
  target_link_libraries(tp1 PUBLIC OpenMP::OpenMP_CXX)
endif()
