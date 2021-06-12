cmake_minimum_required(VERSION 3.19)
project(ClayEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(spdlog/include/)

add_executable(ClayEngine
        src/ClayEngine/main.cpp
        src/ClayEngine/Application.cpp
        src/ClayEngine/Application.h
        src/ClayEngine/Log.cpp
        src/ClayEngine/Log.h)