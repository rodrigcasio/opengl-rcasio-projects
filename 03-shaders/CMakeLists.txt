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
)

target_link_libraries(opengl-exe PRIVATE
  glfw
  Threads::Threads 
  dl
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vertex-shader.glsl
  ${CMAKE_CURRENT_BINARY_DIR}/vertex-shader.glsl
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/frag-shader.glsl
  ${CMAKE_CURRENT_BINARY_DIR}/frag-shader.glsl
)



