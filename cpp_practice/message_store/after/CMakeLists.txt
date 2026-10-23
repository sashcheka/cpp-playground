cmake_minimum_required(VERSION 3.16)
project(message_store LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(message_store
    main.cpp
    src/message_store.cpp
)

target_include_directories(message_store PRIVATE include)
