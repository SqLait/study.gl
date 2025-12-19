#version 460 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;

void main() {
    vec4 t1 = texture(tex1, TexCoord);
    vec4 t2 = texture(tex2, TexCoord);
    vec4 t3 = texture(tex3, TexCoord);

    FragColor = t1 * 0.4 + t2 * 0.4 + t3 * 0.2;
}
