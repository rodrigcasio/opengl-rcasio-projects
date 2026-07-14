# version 330 core
layout (location = 0) in vec3 aPos; // this position variable has attribute position 0

out vec4 vertexColor; // specify a color output to the fragment shader

void main () {
  gl_Position = vec4(aPos, 1.0);            // directly give vec3 to vec4 contructor 3 arguments
  vertexColor = vec4(0.5, 0.0, 0.0, 1.0);   // setting output color to dark-red color

}


// letting the vertex shader decide the color for the fragment shader
