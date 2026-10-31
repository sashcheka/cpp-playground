cmake_minimum_required(VERSION 3.16)
project(retry_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(retry_queue
    main.cpp
    src/retry_queue.cpp
)

target_include_directories(retry_queue PRIVATE include)
