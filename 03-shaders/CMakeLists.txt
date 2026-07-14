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

target_compile_definitions(opengl-exe PRIVATE
  SHADER_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}/shaders/"
)

add_custom_command(
  TARGET opengl-exe POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
  ${CMAKE_CURRENT_BINARY_DIR}/shaders
)


