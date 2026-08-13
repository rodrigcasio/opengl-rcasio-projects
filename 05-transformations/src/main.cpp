#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float4.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include "shader.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

// CH 5: Transformations

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float MIX_VALUE = 0.0f;

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow* window);

int main () {
  
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
#endif // __APPLE__
  
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CH:Transformations", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;

    glfwTerminate();
    return 1;
  }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return 1;
  }

  float vertices[] = {
    // two triangles drawn (rectangle)
    /* Positions */         /* Colors */        /* texture coords */
    /* x     y    z */    /* R      G     B */  /*S    T */
    0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right  (0)
    0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right (1)
   -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left  (2)
   -0.5f,  0.5f, 0.0f,      0.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // top left (3)
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3,
  };

  Shader myShader("build/vertex-shader.glsl", "build/frag-shader.glsl");
  
  // Buffers conf
  unsigned int VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  
  unsigned int EBO;
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO); // ---- bind VAO
  
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
  
  glBindVertexArray(0); // --- unbind VAO
  
  // textures conf
  unsigned int texture0, texture1;

  // texture0 conf
  glGenTextures(1, &texture0);
  glBindTexture(GL_TEXTURE_2D, texture0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int widthT, heightT, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("build/container.jpg", &widthT, &heightT, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthT, heightT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // texture1 conf
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  data = stbi_load("build/awesomeface.png", &widthT, &heightT, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthT, heightT, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // texture units 
  myShader.use();
  glUniform1i(glGetUniformLocation(myShader.ID, "texSampler0"), 0);  // manual version to assign unit tex
  myShader.setInt("texSampler1", 1);

  
  // glm ---
  // translating a vector
  // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  // glm::mat4 identityMatrix = glm::mat4(1.0f);
  //
  // glm::mat4 transMatrix;
  // transMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 1.0f, 0.0f));
  //
  // vec = transMatrix * vec;
  // std::cout << vec.x << vec.y << vec.z << std::endl;


  // scale and rotate the container
  // glm::mat4 trans = glm::mat4(1.0f);
  // // trans becomes a transformation matrix that combines all the transformations
  // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
  // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  //
  // // pass the transformation matrix to shader
  // unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
  // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

  // render
  while (!glfwWindowShouldClose(window)) {
    // input
    processInput(window);
    
    // render window
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // program 
    myShader.use();

    // textures 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    // set up uniform value 
    // glUniform1f(glGetUniformLocation(myShader.ID, "mixThirdArg"), MIX_VALUE);
    myShader.setFloat("mixThirdArg", MIX_VALUE);

    // draw
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // transformation matrix rotating container overtime
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    
    // pass the transformation matrix to shader
    unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

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
  
  // process input for texture mix() third arg
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    MIX_VALUE += 0.01f;
    if (MIX_VALUE >= 1.0f) MIX_VALUE = 1.0f;

  } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    MIX_VALUE -= 0.01f;
    if (MIX_VALUE <= 0.0f) MIX_VALUE = 0.0f;
  }

  
}
