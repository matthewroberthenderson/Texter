#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Main.h"

using namespace Texter;


struct MainStruct
{
	float A = 1.0;
	int Main = 1;
	bool b12 = false;

};




void Texter::DrawModernCanvasQuad() 
{
	unsigned int NewObjectVertexBufferID;
	glGenBuffers(1, &NewObjectVertexBufferID);
	
	glBindBuffer(GL_ARRAY_BUFFER, NewObjectVertexBufferID);
	glBufferData
	(
		GL_ARRAY_BUFFER, 
		8 * sizeof(float), 
		VertexPositions, 
		GL_DYNAMIC_DRAW
	);
}






void Texter::DrawLegacyQuad(float size)
{
	//if no GLEW
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUAD_STRIP);

	
	glVertex2f(-size,-size);
	glVertex2f(-size, size);
	glVertex2f(size, -size);
	glVertex2f(size,  size);
	glEnd();

}


bool Texter::GL_LibCheck() {
	int a = glfwInit(); 
	if (&a)
	{
		int * hInitValue = new int;
		*hInitValue = a;
		std::cout
			<< "GL Value init as "
			<< a
			<< " Pointer: "
			<< hInitValue<< 
		std::endl;

		return true;
	}
	
	else 
	{
		return false;
	}
}



int Texter::CreateWindow() {

	if (&TestingContext) 
	{

		/* Create a windowed mode window and its OpenGL context */
		TestingContext = glfwCreateWindow(1024, 512, "Hello World", NULL, NULL);
		if (!TestingContext)
		{
			glfwTerminate();
			return -1;
		}

		
		/* Make the window's context current */
		glfwMakeContextCurrent(TestingContext);

		while (!glfwWindowShouldClose(TestingContext))
		{
			DrawLegacyQuad(.5);
			glfwSwapBuffers(TestingContext);
			glfwPollEvents();
		}
	}
	else {
		return 0;

	}



}


int main(void)
{

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	
	

	/*for (int i = 0; i < 4; i++) {
		StructValues[i]->A = i;

		StructValues[i]->b12 = false;
		StructValues[i]->Main = 1.1;

	}
*/
	
	CreateWindow();
	glfwTerminate();
	return 0;

}