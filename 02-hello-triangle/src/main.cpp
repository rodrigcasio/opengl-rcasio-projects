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

// settings
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
  
  // build and compile shader program
  // -- vertex Shader
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
 
  //-- fragment shader
  std::string fragmentShaderStr = loadShaderSource("build/fragment-shader.glsl");
  const char* fragmentShaderSource = fragmentShaderStr.c_str();
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  //- safecheck if compilation was successful when glCompileShader() called for fragment shader
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogs);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogs << std::endl;
  }

  // link shaders
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogs);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, // (-0.5, -0.5, 0.0) (x, y, z)
    0.5f, -0.5f, 0.0f,  // (0.5, -0.5, 0.0)
    0.0f, 0.5f, 0.0f  // (0.0, 0.5 0.0)
  };
  
  // Stored vertex data(vertices) within memory on the graphics card as 
  // managed by the vertex buffer object VBO.
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind vertex array first, then bind the set vertex buffer(s), and then configure vertex attribute(s)
  glBindVertexArray(VAO); 

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  // unbind the VAO afterwards so other VAOs calls won't accidentally modify this VAO
  glBindVertexArray(0);

  // reder loop
  while (!glfwWindowShouldClose(window)) {
    // input 
    processInput(window);
    
    // render
    glClearColor(0.2f, 0.3f, 0.3, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // draw first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // glfw: swap buffers to poll IO events (keys pressed/released, mouse moved etc)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once the've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);


  glfwTerminate();
  return 0;
}

// definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1); // true can be used.
  }
}

// f: load shader file placed in build/
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

