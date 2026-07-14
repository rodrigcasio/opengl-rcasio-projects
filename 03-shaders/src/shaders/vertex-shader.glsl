# version 330 core
// letting the vertex shader decide the color for the fragment shader
layout (location = 0) in vec3 aPos;

// out vec4 vertexColor;

void main () {
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);  // directly give vec3 to vec4 contructor 3 arguments

}
