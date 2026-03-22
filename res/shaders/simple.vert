#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uOffset; // centar ćelije u NDC
uniform vec2 uScale;  // pola širine/visine ćelije u NDC

void main()
{
    vec2 p = aPos * uScale + uOffset;
    gl_Position = vec4(p, 0.0, 1.0);
}