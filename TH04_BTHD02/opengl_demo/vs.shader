#version 460
layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;

uniform mat4 model_mat_shader,
projection_mat_shader;

out vec4 fragment_color;

void main(void)
{
	gl_Position = projection_mat_shader * model_mat_shader * vertex_position;
	fragment_color = vertex_color;
}