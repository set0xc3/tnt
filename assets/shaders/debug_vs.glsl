#version 460 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec4 a_color; 

out vec4 our_color;

uniform mat4 mpv;

void main() {
  gl_Position = vec4(a_position.x, a_position.y, 0.0f, 1.0f);
	our_color = a_color;
}
