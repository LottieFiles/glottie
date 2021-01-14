#/////////////////////////////////////////////////////////
#/////////                                       /////////
#/////////  ******            *****************  /////////
#/////////   ****              ***************   /////////
#/////////    ***               ***         **   /////////
#/////////    ***               ***              /////////
#/////////    ***               ***     **       /////////
#/////////    ***               **********       /////////
#/////////    ***               **********       /////////
#/////////    ***               ***     **       /////////
#/////////    ***               ***              /////////
#/////////    ***       **      ***              /////////
#/////////   **************    *****             /////////
#/////////  ****************  *******            /////////
#/////////                                       /////////
#/////////////////////////////////////////////////////////
#///////  Created by: https://github.com/shaafiee  ///////
#///////      Copyright 2020, lottiefiles.com      ///////
#/////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.10)

project(glottie VERSION 0.1)

set(CMAKE_SYSTEM_NAME WindowsStore)
set(CMAKE_SYSTEM_VERSION 10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-g")
set(PROJECTNAME_ARCHITECTURE "x86")

OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" YES)
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

add_compile_definitions(FOR_WINDOWS)

#################################################################################################
# Edit the following line to point to alternative include paths
include_directories("${PROJECT_SOURCE_DIR}/winclude/sdl" "${PROJECT_SOURCE_DIR}/winclude")
#################################################################################################
# Edit the following line to point to SDL2 and ANGLE libraries
# Alternatively, remove the line if they are available in a global library path
link_directories("${PROJECT_SOURCE_DIR}/winlib/angle" "${PROJECT_SOURCE_DIR}/winlib/sdl/lib/x86")
#################################################################################################

#link_directories("${PROJECT_SOURCE_DIR}/winlib/glew" "${PROJECT_SOURCE_DIR}/winlib/glfw" "${PROJECT_SOURCE_DIR}/winlib/sdl/lib/x86" "${PROJECT_SOURCE_DIR}/winlib/freeglut")

add_library(libglottie SHARED main.cpp)
add_executable(glottie main.cpp)

target_link_libraries(libglottie libEGL libGLESv2 SDL2main SDL2)
target_link_libraries(glottie libEGL libGLESv2 SDL2main SDL2)

#target_link_libraries(libglottie glew32 glfw3 opengl32 freeglut SDL2main SDL2)
#target_link_libraries(glottie glew32 glfw3 opengl32 freeglut SDL2main SDL2)

configure_file(configure.h.in configure.h)
