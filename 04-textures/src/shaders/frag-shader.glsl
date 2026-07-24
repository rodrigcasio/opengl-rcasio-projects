// Textures CH
# version 330 core
out vec4 FragColor;

// in vec3 ourPosition;
in vec3 ourColor;

void main () {
  FragColor = vec4(ourColor, 1.0);   // or FragColor = ourPosition if vec4
}


