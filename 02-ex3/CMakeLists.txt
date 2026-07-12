# ch:hello-triangle ex3

cmake_minimum_required(VERSION 3.15)

project(helloTriangleEx3 VERSION 1.0 LANGUAGES CXX C)

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
  ${CMAKE_CURRENT_SOURCE_DIR}/src/fragm-s-01.glsl
  ${CMAKE_CURRENT_BINARY_DIR}/fragm-s-01.glsl
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/fragm-s-02.glsl
  ${CMAKE_CURRENT_BINARY_DIR}/fragm-s-02.glsl
)

