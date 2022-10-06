project(main)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_executable(main main.cpp)

