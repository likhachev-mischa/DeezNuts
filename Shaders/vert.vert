#version 400
layout(location = 0) in vec3 in_position;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//in vec3 in_color;
out vec3 color;
void main() {
gl_Position = projection * view * model * vec4(in_position, 1.0);
color = vec3(1.0,0.0,0.0);
}
