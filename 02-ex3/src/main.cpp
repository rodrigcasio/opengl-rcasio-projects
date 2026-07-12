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
std::string loadShaderSource(const std::string&);

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
  std::string vertexShaderStr = loadShaderSource("build/vertex-shader.glsl");
  const char* vertexShaderSource = vertexShaderStr.c_str();
  unsigned vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLogs[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLogs);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogs << std::endl;
  }

  /* fragment shader placed within an array*/
  std::string fragmentShaderStr[2];
  const char* fragmentShaderSource[2];
  unsigned int fragmentShader[2];

  /* fragm-s-01.glsl (orange) */
  fragmentShaderStr[0] = loadShaderSource("build/fragm-s-01.glsl");
  fragmentShaderSource[0] = fragmentShaderStr[0].c_str();
  fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader[0], 1, &fragmentShaderSource[0], NULL);
  glCompileShader(fragmentShader[0]);
  glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLogs);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogs << std::endl;
  }
  
  /* fragm-s-02.glsl (yellow) */
  fragmentShaderStr[1] = loadShaderSource("build/fragm-s-02.glsl");
  fragmentShaderSource[1] = fragmentShaderStr[1].c_str();
  fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader[1], 1, &fragmentShaderSource[1], NULL);
  glCompileShader(fragmentShader[1]);
  glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLogs);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogs << std::endl;
  }

  /* link shaders */ 
  /* Setting up 2 shader programs */ 
  unsigned int shaderProgram[2];
  shaderProgram[0] = glCreateProgram();
  glAttachShader(shaderProgram[0], vertexShader);
  glAttachShader(shaderProgram[0], fragmentShader[0]);
  glLinkProgram(shaderProgram[0]);
  glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLogs);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogs << std::endl;
  }
  glDeleteShader(fragmentShader[0]);
  
  /* Second shader program */
  shaderProgram[1] = glCreateProgram();
  glAttachShader(shaderProgram[1], vertexShader);
  glAttachShader(shaderProgram[1], fragmentShader[1]);
  glLinkProgram(shaderProgram[1]);
  glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLogs);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogs << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader[1]);

 
  /* data */
  float verticesA[] = {
    /* left triangle */
    -0.5f, 0.5f, 0.0f,
    -0.8f, -0.3f, 0.0f,
    -0.2f, -0.3f, 0.0f,
  };

  float verticesB[] = {
    /* right triangle */
    0.5f, 0.5f, 0.0f,
    0.2f, -0.3f, 0.0f,
    0.8f, -0.3f, 0.0f
  };

  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);
  
  glBindVertexArray(VAOs[0]); /* ---------------------------- first VAOs[0] BOUND ----------------------------*/
  
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  /* no necessary since we are going to bind directly the next VAO, doing it to keep it modular */
  glBindVertexArray(0); /* -------------------- UNBIND VAO[0] -------------------------------------*/
  

  glBindVertexArray(VAOs[1]); /* ---------------------------- first VAOs[1] BOUND ----------------------------*/
  
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); /* -------------------- UNBIND VAO[1] -------------------------------------*/

  /* Wireframe mode */
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  /* render loop */
  while (!glfwWindowShouldClose(window)) {
    /* input */
    processInput(window);
  
    /* render */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
       
    /* first program */
    glUseProgram(shaderProgram[0]);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    /* second program */
    glUseProgram(shaderProgram[1]);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  /* Optional: Deallocate all resources, VBOs VAOs and shader programs */
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgram[0]);
  glDeleteProgram(shaderProgram[1]);
  
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


std::string loadShaderSource(const std::string& filePath) {
  std::ifstream shaderFile(filePath);
  if (shaderFile.is_open()) {
    std::cerr << "ERROR: Could not open shared file: " << filePath << std::endl;
    
    exit(EXIT_FAILURE);
  }

  std::stringstream shStream;
  shStream << shaderFile.rdbuf();  /* read file buffer into stream */
  return shStream.str();  /* convert stream into a string */
}
