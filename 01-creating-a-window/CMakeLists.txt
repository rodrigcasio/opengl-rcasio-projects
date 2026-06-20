# Protect against bugs by locking a modern CMake standard
cmake_minimum_required(VERSION 3.15)

# 2. Declare the name of this project module and the language used (c++)
project(CreatingAWindow VERSION 1.0 LANGUAGES CXX)

# 3. Mandate C++17 rules for compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Export database paths so LazyVim (clang LSP) can automate my graphics libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 5 Find GLFW and system treathing libraries
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

# 6 Define our binary executable app target name and point to its source files
add_executable(opengl-exe src/main.cpp)

# 7 Direct CMake to link GLFW system math/thread lirbaries, and GLAD's C file
target_link_libraries(opengl-exe PRIVATE 
  glfw
  Threads::Threads
  dl
)

# Updated for adding GLAD for first project
