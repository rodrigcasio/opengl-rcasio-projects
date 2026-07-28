// Textures CH
# version 330 core
out vec4 FragColor;

// in vec3 ourPosition;
in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texSampler0;
uniform sampler2D texSampler1;

void main () {
  // FragColor = texture(ourTexSampler, texCoord);

  /* mix resulting tex color with the vertex color */
  // FragColor = texture(texSampler0, texCoord) * vec4(ourColor, 1.0);   

  /* combination of two texture outputs */
  FragColor = mix(texture(texSampler0, texCoord), texture(texSampler1, texCoord), 0.2);  
}


