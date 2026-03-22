#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec3 uColor;

void main(){
    float alpha = texture(uTexture, TexCoord).r;
    FragColor = vec4(uColor, alpha);
}