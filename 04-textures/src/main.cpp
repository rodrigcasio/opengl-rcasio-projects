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
    // two triangles drawn (rectangle)

    /* Positions */         /* Colors */        /* texture coords */
    /* x     y    z */    /* R      G     B */  /*S    T */
    0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right  (0)
    0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right (1)
   -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left  (2)
   -0.5f,  0.5f, 0.0f,      1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left (3)
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
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

  /* EBO for indices [] */
  unsigned int EBO;
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO); /* ---- BIND VAO ---- */

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(VAO); /* ---- UNBIND VAO ---- */

  /* texture objects */
  unsigned int texture0, texture1; 

  /* texture0 config wrapping/filtering */
  glGenTextures(1, &texture0);
  glBindTexture(GL_TEXTURE_2D, texture0); /* no need to unbind */
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); /* x axis */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); /* y axis */
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
  
  /* texture1 config wrapping/filtering */
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);  

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  data = stbi_load("build/awesomeface.png", &widthT,  &heightT, &nrChannels, 0);
  if (data) {
    /* awesomeface.png has transparency and thus alpha channel so we use GL_RGBA */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthT, heightT, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  /* setting uniform samplers */
  myShader.use();
  glUniform1i(glGetUniformLocation(myShader.ID, "texSampler0"), 0);   // setting it manually texture unit 0
  myShader.setInt("texSampler1", 1);  // same thing but using .setInt() Shader method

  /* render loop */
  while (!glfwWindowShouldClose(window)) {
    /* input */
    processInput(window);

    /* render */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Start program */
    myShader.use();

    /* activating/binding textures */
    /* texture0 */
    glActiveTexture(GL_TEXTURE0);
    glBindBuffer(GL_TEXTURE_2D, texture0);
    /* texture0 */
    glActiveTexture(GL_TEXTURE1);
    glBindBuffer(GL_TEXTURE_2D, texture1);
     
    /* Draw rectangle (two triangles) */
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
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
