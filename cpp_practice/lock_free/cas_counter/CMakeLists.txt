cmake_minimum_required(VERSION 3.16)
project(cas_counter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(cas_counter main.cpp)
target_link_libraries(cas_counter PRIVATE Threads::Threads)
