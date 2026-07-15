# version 330 core
out vec4 FragColor;
in vec3 ourColor;
// in vec4 vertexColor;      // input variable from the vertex shader (same name and same type (vec4))
// uniform vec4 ourColor;      // we set this variable in the OpenGL code

void main () {
  FragColor = vec4(ourColor, 1.0);
}

/* Important: if we declare a uniform that is not used anywhere in your GLSL code, the compiler
  will silently remove the variable from te compiled version which is the cause for serveral errors
  (keep this in mind!)*/
