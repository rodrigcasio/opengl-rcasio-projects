# Protect against bugs by locking a modern CMake standard
cmake_minimum_required(VERSION 3.15)

# 2. Declare the name of this project module and the language used (c++)
project(CreatingAWindow Version 1.0 LANGUAGES CXX)

# 3. Mandate C++17 rules for compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Export database paths so LazyVim (clang LSP) can automate my graphics libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 5 Ask CMake to scan my Arch Linux System for packages paths
find_package(OpenGL REQUIRED)
find_package(glfw 3.3 REQUIRED)

# 6 Define our binary executable app target name and point to its source files
add_executable(opengl_window src/main.cpp)

# 7 Use the target linker to glue GLFW and OpenGL code objects directly into my binary
get_link_libraries(opengl_window
  PRIVATE
      glfw
      OpenGL::GL
)





