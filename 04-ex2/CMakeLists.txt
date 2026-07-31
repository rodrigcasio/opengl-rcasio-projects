# exercise 2 ch: textures
cmake_minimum_required(VERSION 3.15)

project(textureEx2 VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

add_executable(
  opengl-exe 
    src/main.cpp
    src/glad.c
    src/shader.cpp
    src/stb_image.cpp
)

if (APPLE)
  find_package(OpenGL REQUIRED)

  target_link_libraries(
    opengl-exe
    PRIVATE
      glfw::OpenGL
      Threads::Threads
      OpenGL::
  )
else()
  target_link_libraries(
    opengl-exe
      PRIVATE
        glfw
        Threads::Threads
        dl
  )
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/vertex-shader.glsl
  ${CMAKE_CURRENT_BINARY_DIR}/vertex-shader.glsl
  COPYONLY
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/frag-shader.glsl
  ${CMAKE_CURRENT_BINARY_DIR}/frag-shader.glsl
  COPYONLY
)

# loading images individually:
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/images/container.jpg
  ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
  COPYONLY
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/images/awesomeface.png
  ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png
  COPYONLY
)

# # automatic way to grab everything in images/ dir automatically
# # grab a list of all images inside the src/images dir
# file(GLOB TEXTURE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/images/*")
#
# # # automatically loop through each image and copy it to the build/ dir
# foreach(IMAGE_PATH ${TEXTURE_FILES})
#   get_filename_component(IMAGE_NAME ${IMAGE_PATH} NAME)
#   configure_file(
#     ${IMAGE_PATH}
#     ${CMAKE_CURRENT_BINARY_DIR}/${IMAGE_NAME} COPYONLY
#   )
# endforeach()

