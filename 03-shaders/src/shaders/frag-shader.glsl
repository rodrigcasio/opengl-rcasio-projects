# version 330 core
out vec4 FragColor;

in vec4 vertexColor;      // input variable from the vertex shader (same name and same type (vec4))

void main () {
  FragColor = vertexColor;
}
