// Exericise 3 CH: Shaders
# version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 ourPosition;

uniform float xOffset;   // add more value (0.3f set up in main()) to aPos.x

void main () {
  gl_Position = vec4((aPos.x + xOffset), aPos.y, aPos.z, 1.0); 
  // ourColor = aColor;
  ourPosition = aPos;
}
