# Protect against bugs by locking a modern CMake standard
cmake_minimum_required(VERSION 3.15)

# 2. Declare the name of this project module and the language used (c++)
project(CreatingAWindow VERSION 1.0 LANGUAGES CXX C)

# Mandate C++17 rules for compiler
set(CMAKE_CXX_STANDARD 17)
# Export database paths so LazyVim (clang LSP) can automate my graphics libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 1. Tell CMake where to look for our local glad.h file
include_directories(include)

# 2 Find GLFW and system threads
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

# 3 Add BOTH main.cpp AND glad.c to our executable build list
add_executable(opengl-exe 
  src/main.cpp
  src/glad.c
)

# 4 link out system graphics/thread libraries
target_link_libraries(opengl-exe PRIVATE 
  glfw
  Threads::Threads
  dl
)

# Updated for adding GLAD for first project
