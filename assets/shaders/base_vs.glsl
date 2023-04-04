#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color; 
layout(location = 2) in vec3 a_uv;

out vec4 our_color;

void main() {
    gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
    our_color = a_color;
}
