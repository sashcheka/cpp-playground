cmake_minimum_required(VERSION 3.16)
project(inference_service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(inference_service
    main.cpp
    src/inference.cpp
)

target_include_directories(inference_service PRIVATE include)
