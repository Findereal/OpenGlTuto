cmake_minimum_required(VERSION 3.19)
project(OpenGlTuto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(libraries)
include_directories(libraries/include)
include_directories(libraries/include/glad)
include_directories(libraries/include/KHR)
include_directories(libraries/include/stb)
include_directories(resources)
include_directories(resources/Shader)
include_directories(resources/Textures)
include_directories(source)
include_directories(headers)


add_executable(OpenGlTuto)

target_sources(OpenGlTuto
        PUBLIC
        source/glad.c
        source/shadersClass.cpp
        source/EBO.cpp
        source/VAO.cpp
        source/VBO.cpp
        source/stb.cpp

        main.cpp)

target_link_libraries(OpenGlTuto glfw3 X11 pthread dl)