// Textures CH
# version 330 core
out vec4 FragColor;

// in vec3 ourPosition;
in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexSampler;

void main () {
  // FragColor = texture(ourTexSampler, texCoord);
  FragColor = texture(ourTexSampler, texCoord) * vec4(ourColor, 1.0); /* mix resulting tex color with the vertex color */
}


