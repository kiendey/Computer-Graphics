#version 460

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;

out vec4 fragment_color;

void main(void)
{	
	gl_Position = vertex_position;
		
	fragment_color = vertex_color;
}
