#version 450

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;

layout(location = 0) out vec2 v_TexCoords;

layout(set=0, binding=0) uniform Camera
{
	mat4 Projection;
	mat4 View;
} u_Camera;

void main()
{
	v_TexCoords = a_TexCoords;

	gl_Position = u_Camera.Projection * u_Camera.View * a_Position;
}