#include <cwchar>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ostream>
#include <cstdlib>

/* Ex 2 (ch:Hello Triangle) */

/* settings */
const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string loadShaderSource(const std::string& filePath);

int main () {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Hello Triangle (Exericise 2)", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  /* glad */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  /* vertex shader */
  std::string vertexShaderStr = loadShaderSource("build/vertex-shader.glsl");
  const char* vertexShaderSource = vertexShaderStr.c_str();
  unsigned int vertexShader;
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

  /* fragment shader */
  std::string fragmentShaderStr = loadShaderSource("build/fragment-shader.glsl");
  const char* fragmentShaderSource = fragmentShaderStr.c_str();
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogs);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogs << std::endl;
  }

  /* link shaders */
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  /* check for linking errors */
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogs);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogs << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);


  /* two triangles (in distinct VAO) */
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

  /* Buffer Objects */

  unsigned int VBO, VBO_2, VAO, VAO_2;
  glGenVertexArrays(1, &VAO);
  glGenVertexArrays(2, &VAO_2);
  glGenBuffers(1, &VBO);
  glGenBuffers(2, &VBO);

  /* first VBO & VAO for verticesA (first triangle) */
  glBindVertexArray(VAO); /* ---------------------------- VAO BOUND ----------------------------*/

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glBindVertexArray(0); /* -------------------- UNBIND VAO -------------------------------------*/



  /* second VBO_2 & VAO_2 binding for verticesB (second triangle) */
  glBindVertexArray(VAO_2); /* ---------------------------- VAO_2 BOUND ----------------------------*/
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0); /* -------------------- UNBIND VAO_2 -------------------------------------*/




  while (!glfwWindowShouldClose(window)) {
    /* input */
    processInput(window);
    
    
    /* render */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /* draw two triangles each with their own VAO */
    // glUseProgram(shaderProgram);

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
    glfwSetWindowShouldClose(window, 1); // or true
  }
}

std::string loadShaderSource(const std::string& filePath) {
  std::ifstream shaderFile(filePath);
  if (!shaderFile.is_open()) {
    std::cerr << "ERROR: Could not open shared file: " << filePath << std::endl;
    
    exit(EXIT_FAILURE);
  }
  std::stringstream shaderStream;
  shaderStream << shaderFile.rdbuf(); /* Read file buffer into stream */
  return shaderStream.str();  /* convert stream into a string */
}












