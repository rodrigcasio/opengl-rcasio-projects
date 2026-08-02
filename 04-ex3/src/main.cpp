#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "stb_image.h"
// exercise 3

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main () {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
  
#endif // __APPLE__

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exercise 3 CH:Textures", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;

    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize Glad" << std::endl;
    return 1;
  }

  float vertices[] = {
    // two triangles drawn (rectangle)
    /* Positions */         /* Colors */        /* texture coords */
    /* x     y    z */    /* R      G     B */  /*S    T */
    0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right  (0)
    0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right (1)
   -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left  (2)
   -0.5f,  0.5f, 0.0f,      0.0f, 0.0f, 0.0f,   0.0f, 2.0f,   // top left (3)
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3,
  };

  Shader myShader("build/vertex-shader.glsl", "build/frag-shader.glsl");

  while (!glfwWindowShouldClose(window)) {
    /* input */
    processInput(window);

      
    /* window */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  

  glfwTerminate();

  return 0;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}
