
## Exercise 4 CH: Textures

- ` Use a uniform variable as the mix function's third parameter to vary the amount the two textures are visible. Use the up and down arrow keys to change how much the container or the smiley face is visible`

- Implemeting logic within the `processInput()` for handling the value of the global variable `MIX_VALUE` 

```cpp
void processInput(GLFWwindow *window) {
    
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
  
  // process input for 
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    MIX_VALUE += 0.01f;
    if (MIX_VALUE >= 1.0f) MIX_VALUE = 1.0f;

  } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    MIX_VALUE -= 0.01f;
    if (MIX_VALUE <= 0.0f) MIX_VALUE = 0.0f;
  }
}

```

- Setting the uniform value within the shader
```cpp

    while (!glfwSetWindowShouldClose) {
        // ...

        myShader.SetFloat("mixThirdArg", MIX_VALUE);

        // ...
    }

```

- Pressing Up and Down arrow keys

=
![result0](./result/ex4.gif)



