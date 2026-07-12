#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ostream>
#include <cstdlib>

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* );
std::string loadshaderSource(const std::string&);

int main () {
 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT , "Hello Triangle (exercise 3)", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  
  /* vertex shader */
  
  
  /* fragment shader 01 (orange) */
  /* fragment shader 02 (yellow) */


  unsigned int VBOs[2], VAOs[2];
  
  
  /* render loop */
  while (!glfwWindowShouldClose(window)) {
    /* input */
    processInput(window);
  
    /* render */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1); // or true can be used
  }
}


std::string loadshaderSource(const std::string& filePath) {
  std::ifstream shaderFile(filePath);
  if (shaderFile.is_open()) {
    std::cerr << "ERROR: Could not open shared file: " << filePath << std::endl;
    
    exit(EXIT_FAILURE);
  }

  std::stringstream shStream;
  shStream << shaderFile.rdbuf();  /* read file buffer into stream */
  return shStream.str();  /* convert stream into a string */
}
