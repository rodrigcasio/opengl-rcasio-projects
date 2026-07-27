#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "stb_image.h"

// Textures CH
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int main () {
  
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif 
  
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Textures CH", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  
  /* Vertex data (vertices, color & texture coordinates)*/
  float vertices[] = {
    /* Positions */         /* Colors */  
    /* x     y      z       R      G     B   */
     0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,  // top middle
  };

  // float textCoords[] = {
  //   0.0f, 0.0f, // lower left corner
  //   1.0f, 0.0f, // lower right corner
  //   1.0f, 1.0f // top center corner
  // };

  Shader myShader("build/vertex-shader.glsl", "build/frag-shader.glsl");

  /* Buffers config (VBO & VAO) */
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO); /* ---- BIND VAO ---- */

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(VAO); /* ---- UNBIND VAO ---- */


  /* texture config wrapping/filtering */
  unsigned int texture; 
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture); /* --- TEXTURE BIND --- */
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); /* x axis */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); /* y axis */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  /* load & generate text */
  int widthT, heightT, nrChannels;
  unsigned char *data = stbi_load("build/container.jpg", &widthT, &heightT, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthT, heightT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }

  stbi_image_free(data);





  /* render loop */
  while(!glfwWindowShouldClose(window)) {
    /* input */
    processInput(window);

    /* render */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Start program */
    myShader.use();

    /* Draw triangle */
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);

  glfwTerminate(); 
  return 0;
}


void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}



// Textures CH
