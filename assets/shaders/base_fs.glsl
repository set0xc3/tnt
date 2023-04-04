#version 460 core

out vec4 out_color; in vec4 our_color;

void main() {
    out_color = vec4(our_color.x, our_color.y, our_color.z, our_color.w);
});
