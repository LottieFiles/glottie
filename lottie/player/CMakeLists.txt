cmake_minimum_required(VERSION 3.10)

project(glottie VERSION 0.1)

set(CMAKE_SYSTEM_NAME WindowsStore)
set(CMAKE_SYSTEM_VERSION 10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_VS_WINRT_BY_DEFAULT True)
set(CMAKE_CXX_FLAGS "-g")
set(PROJECTNAME_ARCHITECTURE "x86")

#SET(CPPWINRT_REQUIRED_COMPILER_FLAGS "/std:c++latest /await")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPPWINRT_REQUIRED_COMPILER_FLAGS}")

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" YES)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

include_directories("${PROJECT_SOURCE_DIR}/winclude/sdl" "${PROJECT_SOURCE_DIR}/winclude")
link_directories("${PROJECT_SOURCE_DIR}/winlib/angle" "${PROJECT_SOURCE_DIR}/winlib/sdl/lib/x86")

add_library(libglottie SHARED main.cpp)
add_executable(glottie main.cpp)

#set_target_properties(libglottie PROPERTIES VS_WINRT_COMPONENT true)
#set_target_properties(glottie PROPERTIES VS_WINRT_COMPONENT true)
#set_target_properties(libglottie PROPERTIES VS_CPPWINRT true)
#set_target_properties(glottie PROPERTIES VS_CPPWINRT true)

target_link_libraries(libglottie libEGL libGLESv2 SDL2main SDL2)
target_link_libraries(glottie libEGL libGLESv2 SDL2main SDL2)

configure_file(configure.h.in configure.h)


