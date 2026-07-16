#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main () {
 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shaders:CH Exercise 1", NULL, NULL);
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

  Shader ourShaders("build/vertex-shader.glsl", "build/frag-shader.glsl");

  float vertices[] = {
    /* centered triangle (upside down) */
    /* Positions */         /* Colors */  
    /* x     y      z       R      G     B   */
     0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  // top right
    -0.5f, 0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  // top left
     0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  // bottom middle
  };

  /* buffers */
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO); /* ---------------------------- VAO BOUND ----------------------------*/
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0); /* ---------------------------- VAO Unbound  ----------------------------*/

  /* wireframe mode */
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  /* render loop */
 while (!glfwWindowShouldClose(window)) {
   /* input */
   processInput(window);
    
   /* render */
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   
   /* start program */
   ourShaders.use();

   /* Draw Triangle */
   glBindVertexArray(VAO);
   glDrawArrays(GL_TRIANGLES, 0, 3);

   glfwSwapBuffers(window);
   glfwPollEvents();
 }
 
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
   
 glfwTerminate();
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
