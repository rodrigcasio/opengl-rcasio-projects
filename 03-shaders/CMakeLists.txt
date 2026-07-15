# CH: Shaders
cmake_minimum_required(VERSION 3.15)

project(shadersCh VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

add_executable(opengl-exe 
  src/main.cpp
  src/glad.c
  src/shaders.cpp
)

target_link_libraries(opengl-exe PRIVATE
  glfw
  Threads::Threads 
  dl
)

# modular way to load and place a copy of shaders to build/ dir
configure_file(
  # Start exactly where the CMakeLists.txt file is sitting, look inside the src/ dir, then look inside shaders/ dir and grab vertex-shader.glsl
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/vertex-shader.glsl
  ${CMAKE_CURRENT_BINARY_DIR}/vertex-shader.glsl
  COPYONLY
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/frag-shader.glsl
  
  # take that file you grabbed from my source code, and copy a fresh version of it straight  into the build/ dir
  ${CMAKE_CURRENT_BINARY_DIR}/frag-shader.glsl
  COPYONLY
)



