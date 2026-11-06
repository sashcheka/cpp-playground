cmake_minimum_required(VERSION 3.16)
project(response_cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(response_cache
    main.cpp
    src/response_cache.cpp
)

target_include_directories(response_cache PRIVATE include)
