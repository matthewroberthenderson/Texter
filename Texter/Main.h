#pragma once


namespace Texter {

	GLFWwindow* TestingContext;

	int CreateWindow();
	bool GL_LibCheck();
	void DrawLegacyQuad(float size);
	void DrawModernCanvasQuad();
	
	
	float size = .5;
	//we would want to get this from the mesh read in data
	//in future but it's a plane so whateva
	int VertexCount = 8;

	float VertexPositions[8] =
	{
		-size,-size,
		- size, size,
		size, -size,
		size,  size
	};
}
