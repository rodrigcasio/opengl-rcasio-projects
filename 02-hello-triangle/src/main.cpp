// clangd format off
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ostream>
// chapter hello triangle

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string loadShaderSource(const std::string& filePath);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;


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
  
  // ------
  // Stored vertex data(vertices) within memory on the graphics card as 
  // managed by the vertex buffer object VBO.
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // --------
 
  //---------------------
  // -- creating vertexShader
  const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n "
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
    "}\0";

  unsigned int vertexShader; // shader object
  vertexShader = glCreateShader(GL_VERTEX_SHADER); // type of shader: GL_VERTEX_SHADER
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
 
  //- safe check if compilation was sucessfull when `glCompileShader()` called
  int success;  // can be used for each safe check in vertex, fragment or program shader
  char infoLogs[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLogs);
    std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogs << std::endl;
  }
  //-------------
 

  // ------------
  //-- creating fragmentShader object with function loadSharedSource
  std::string fragmentShaderStr = loadShaderSource("build/fragment-shader.glsl");
  const char* fragmentShaderSource = fragmentShaderStr.c_str();
  
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  
  //- safecheck if compilation was successful when glCompileShader() called for fragment shader
  int sucessFragmentShader;
  char infoLogs_fr[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucessFragmentShader);
  
  if (!sucessFragmentShader) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogs_fr);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogs_fr << std::endl;
  }
  // -------------

  //--------------
  //-- Shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // -- safe check if linking a shader program failed 
  // During linking step(each output is matched to each input of the shaders and whenever something is not right, linking fails) 
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogs);
  }
  
  glUseProgram(shaderProgram);
  
  // delete shader objects (vertex & fragment shader) after linked them into a program object (shaderProgram)
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  

  //--------------


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

std::string loadShaderSource(const std::string& filePath) {
  std::ifstream shaderFile(filePath);
  if (!shaderFile.is_open()) {
    std::cerr << "ERROR: Could not open shared file: " << filePath << std::endl;

    exit(EXIT_FAILURE); // stop the program so opengl does not try to compile empty strings
  }

  std::stringstream shaderStream;
  shaderStream << shaderFile.rdbuf(); // read file buffer into stream
  return shaderStream.str(); // convert stream to string
}

