#version 460 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main() {
    vec4 t1 = texture(texture1, TexCoord);
    vec4 t2 = texture(texture2, TexCoord);
    vec4 t3 = texture(texture3, TexCoord);

    FragColor = t1 * 0.4 + t2 * 0.4 + t3 * 0.2;
}
