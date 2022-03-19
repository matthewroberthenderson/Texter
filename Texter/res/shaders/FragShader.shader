#version 330 core

layout(location = 0) out vec4 color;


void main()

{
	color = vec4(0.0, step(gl_FragCoord.x / 640.0f, 0.5), step(gl_FragCoord.y / 480.0f,0.5), 1.0);

};