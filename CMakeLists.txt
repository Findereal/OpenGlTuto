cmake_minimum_required(VERSION 3.19)
project(OpenGlTuto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(libraries)
include_directories(libraries/include)
include_directories(libraries/include/glad)
include_directories(libraries/include/KHR)

add_executable(OpenGlTuto
        libraries/include/glad/glad.h
        libraries/include/KHR/khrplatform.h
        glad.c
        main.cpp
        main.h)

