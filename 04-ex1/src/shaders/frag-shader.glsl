// exercise 1 CH Textures
# version 330 core
out vec4 FragColor;

// in vec3 ourPosition;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texSampler0;
uniform sampler2D texSampler1;

void main () {
  // FragColor = texture(ourTexSampler, TexCoord);

  /* mix resulting tex color with the vertex color */
  // FragColor = texture(texSampler0, TexCoord) * vec4(ourColor, 1.0);   

  /* combination of two texture outputs */
  FragColor = mix(texture(texSampler0, TexCoord), texture(texSampler1, vec2(1.0 - TexCoord.s, TexCoord.t)), 0.2);  
}


