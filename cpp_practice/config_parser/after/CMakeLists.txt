cmake_minimum_required(VERSION 3.16)
project(config_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(config_parser
    main.cpp
    src/config.cpp
    src/config_parser.cpp
)

target_include_directories(config_parser PRIVATE include)
