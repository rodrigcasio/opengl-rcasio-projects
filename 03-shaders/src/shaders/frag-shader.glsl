# version 330 core
out vec4 FragColor;
// in vec4 vertexColor;      // input variable from the vertex shader (same name and same type (vec4))
uniform vec4 ourColor;      // we set this variable in the OpenGL code

void main () {
  FragColor = ourColor;
}
