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

  /* Buffer Objects (generate multiple VAOs or buffers at the same time with array) */
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


  glBindVertexArray(VAOs[1]); /* ---------------------------- second VAOs[1] BOUND ----------------------------*/

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); /* -------------------- UNBIND VAO[1] -------------------------------------*/

  /* Wireframe mode */
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


  while (!glfwWindowShouldClose(window)) {
    /* input */
    processInput(window);   
    
    /* render */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /* draw two triangles each with their own VAO */
    glUseProgram(shaderProgram);
    /* draw left triangle first using first VAOs[0] */
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* draw right triangle first second VAOs[1] */
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  /* Optional: deallocate all resources */
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgram);


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


  /* first approach (worked accordingly) for setting up two VAOs and two VBO */

  // unsigned int VBO, VBO_2, VAO, VAO_2;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  //
  // glGenVertexArrays(1, &VAO_2);
  // glGenBuffers(1, &VBO_2);
  //
  // /* first VBO & VAO for verticesA (first triangle) */
  // glBindVertexArray(VAO); /* ---------------------------- VAO BOUND ----------------------------*/
  //
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);
  //
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(0);
  //
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  //
  // glBindVertexArray(0); /* -------------------- UNBIND VAO -------------------------------------*/
  //
  //
  // /* second VBO_2 & VAO_2 binding for verticesB (second triangle) */
  // glBindVertexArray(VAO_2); /* ---------------------------- VAO_2 BOUND ----------------------------*/
  //
  // glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);
  //
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(0);
  //
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  //
  // glBindVertexArray(0); /* -------------------- UNBIND VAO_2 -------------------------------------*/
  //
  //  /* render loop */
  // while (!glfwWindowShouldClose(window)) {
  //   /* input */
  //   processInput(window);
  //
  //
  //   /* render */
  //   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //   glClear(GL_COLOR_BUFFER_BIT);
  //
  //   /* draw two triangles each with their own VAO */
  //   glUseProgram(shaderProgram);
  //   /* draw left triangle first using the data from the first VAO */
  //   glBindVertexArray(VAO);
  //   glDrawArrays(GL_TRIANGLES, 0, 3);
  //
  //   /* draw right triangle first using the data from the second VAO_2 */
  //   glBindVertexArray(VAO_2);
  //   glDrawArrays(GL_TRIANGLES, 0, 3);
  //
  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  // }
  //
  // /* Optional: deallocate all resources */
  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
  // glDeleteVertexArrays(2, &VAO_2);
  // glDeleteBuffers(2, &VBO_2);
  // glDeleteProgram(shaderProgram);








