#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform float u_Time;

void main()

{
	color = u_Color;

};