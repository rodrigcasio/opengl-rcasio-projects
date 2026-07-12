# ch:hello-traingle ex2
cmake_minimum_required(VERSION 3.15)

project(helloTriangleEx2 VERSION 1.0 LANGUAGES CXX C)

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

