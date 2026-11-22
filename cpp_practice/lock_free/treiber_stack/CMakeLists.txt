cmake_minimum_required(VERSION 3.16)
project(treiber_stack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(treiber_stack main.cpp)
target_link_libraries(treiber_stack PRIVATE Threads::Threads)
