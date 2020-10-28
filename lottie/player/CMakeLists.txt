cmake_minimum_required(VERSION 3.10)

project(glottie VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${glfw3_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_executable(glottie main.cpp)

target_link_libraries(glottie ${glfw3_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARY} ${SDL2_LIBRARIES})

configure_file(configure.h.in configure.h)


