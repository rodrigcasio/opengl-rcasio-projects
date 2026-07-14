# version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

void main () {
  gl_Position = vec4(vec3, 1.0);  // directly give vec3 to vec4 contructor 3 arguments
  vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}
