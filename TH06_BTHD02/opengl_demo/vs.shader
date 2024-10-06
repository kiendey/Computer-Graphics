#version 460
layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;

out vec4 fragment_color;
uniform mat4 view_mat_shader;
uniform mat4 projection_mat_shader;

void main(void)
{
	gl_Position = projection_mat_shader*view_mat_shader *vertex_position;
	fragment_color = vertex_color;
}
