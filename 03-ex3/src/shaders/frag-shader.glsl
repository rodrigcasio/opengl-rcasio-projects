// Exercise 3 CH: Shaders 
# version 330 core
out vec4 FragColor;

in vec4 ourPosition;
// in vec3 ourColor;

void main () {
  FragColor = ourPosition;
}


