// clangd format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <ostream>
// chapter hello triangle

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n "
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
  "}\0";

int main () {
  
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  

  GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Hello Triangle", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // glad:
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, // (-0.5, -0.5, 0.0) (x, y, z)
    0.5f, -0.5f, 0.0f,  // (0.5, -0.5, 0.0)
    0.0f, 0.5f, 0.0f  // (0.0, 0.5 0.0)
  };
  
  // --
  // Stored vertex data(vertices) within memory on the graphics card as 
  // managed by the vertex buffer object VBO.
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // --
  
  // -- creating vertexShader
  unsigned int vertexShader; // shader object
  vertexShader = glCreateShader(GL_VERTEX_SHADER); // type of shader: GL_VERTEX_SHADER
  glad_glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glad_glCompileShader(vertexShader);
  //---
  
  //---
  //-- safe check if compilation was sucessfull when `glad_glCompileShader()` called
  int success;
  char infoLogs[512];
  glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glad_glGetShaderInfoLog(vertexShader, 512, NULL, infoLogs);
    std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogs << std::endl;
  }
  //--
  
  // reder loop
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  
  return 0;
}

// ------ def

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1); // true can be used.
  }
}
