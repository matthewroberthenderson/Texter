#pragma once
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBufferHelpers.h"
#include "ShaderBase.h"
#include "Renderer.h"
#include "TextureHelpers.h"

float Time;
int width = 1024, height = 768;

float QuadStripSize = 0.5;

void ThreadedTimeUpdate() {

	std::thread([&]
	{
		while (true)
		{

			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			(Time += 0.001f);


		}
	}).detach();


}