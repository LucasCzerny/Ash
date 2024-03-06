#version 450

layout(location = 0) in vec2 v_TexCoords;

layout(location = 0) out vec4 o_Color;

void main()
{
	o_Color = vec4(0.8, 0.2, 0.2, 1.0);
}
