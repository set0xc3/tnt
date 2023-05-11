#version 460 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec4 a_color; 

out vec4 our_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// projection * view * model *

void main()
{
  gl_Position = projection * view * model * vec4(a_position.xy, 0.0f, 1.0f);
	our_color = a_color;
}

