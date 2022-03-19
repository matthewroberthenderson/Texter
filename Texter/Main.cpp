#include <iostream>
#include <fstream>
#include <string>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Main.h"

#define String std::string


void open(std::ifstream &fp, String a)
{

	//char * n = (char*)alloca(sizeof(char)*a.length());

	//const char * b = (char*)alloca(sizeof(char)*a.length());
	//strcpy(n, a.c_str());
	//

	//while (fp.getline(n, sizeof(n))) {
	//	if (a.find("#shader") != std::string::npos) 
	//	{

	//		if (a.find("vertex") != std::string::npos) {
	//			//set mode to vertex
	//		}
	//		else if (a.find("fragment") != std::string::npos)
	//		{
	//			//set mode to fragment

	//		}
	//		
	//	
	//	}
	//}
		
}



static std::string parseShader(const std::string filePath) {
std::string code;
std::string line;
std::ifstream file(filePath);

while (getline(file, line)) {
	code += line;
	code += "\n";
}
file.close();
return code;
}



using namespace Texter;




static unsigned int CompileShader(const String &source, unsigned int type)
{
	   
	    unsigned int Ref = glCreateShader(type);
	    const char* src = source.c_str();
		glShaderSource(Ref, 1, &src, nullptr);


		glCompileShader(Ref);
		// get the types the shader needs
		
		int result;
		glGetShaderiv(Ref, GL_COMPILE_STATUS, &result);
		
		if (result == 0) 
		{
			//shader did not compile
			int length;
			glGetShaderiv(Ref, GL_COMPILE_STATUS, &length);
		   
			char * Message = (char*)alloca(sizeof(char)*length);
			glGetShaderInfoLog(Ref, length, &length, Message);
			
			//whenever i write to hMessage i need to feed in deref *hMessage
			std::cout << 
				"shader compile issue" << 
				" Type " 
				<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
				<< std::endl;

			std::cout << Message << std::endl;

			glDeleteShader(Ref);
			

		}
		
		return Ref;
	

}


static unsigned int CreateShader(const String &VertexShader, const String &FragmentShader)
{

	unsigned int FullShaderProg = glCreateProgram();

	unsigned int VS = CompileShader(VertexShader, GL_VERTEX_SHADER);
	unsigned int FS = CompileShader(FragmentShader, GL_FRAGMENT_SHADER);

	//attach to full compiled shader program
	glAttachShader(FullShaderProg, VS);
	glAttachShader(FullShaderProg, FS);

	//link & validate
	glLinkProgram(FullShaderProg);
	glValidateProgram(FullShaderProg);

	
	//get rid of the junk .obj files 
	//because we have fed this data into the FullShaderProg program now
    //that will take them from there
	
	glDeleteShader(VS);
	glDeleteShader(FS);
	
	
	return FullShaderProg;

}

struct MainStruct
{
	float A = 1.0;
	int Main = 1;
	bool b12 = false;

};




void Texter::DrawModernCanvasQuad()
{

	unsigned int buff;

	
	//create 1 buffer for our data and assign it a pointer to our ID
	glGenBuffers(1, &buff);
	
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData
	(
		GL_ARRAY_BUFFER, 
		8 * sizeof(float), 
		VertexPositions, 
		GL_STATIC_DRAW
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







int Texter::CreateWindowLegacy() {

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

	if (!glewInit()) {
		std::cout << "error" << std::endl;
	}
	
	if (!glfwInit()) {
		printf("glfwInit() failed!");
		return 0;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_FALSE;

	if (!glewInit() == GLEW_OK) {
		exit(-1);
	}


	unsigned int buff;

	//create 1 buffer for our data and assign it a pointer to our ID
	glGenBuffers(1, &buff);

	//select this buffer to be the one i'm using for the canvas
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData
	(
		GL_ARRAY_BUFFER,
		8 * sizeof(float),
		VertexPositions,
		GL_STATIC_DRAW
	);


	glEnableVertexAttribArray(0);
	//really bad but works for the plane
	glVertexAttribPointer
	(
		0, 
		8, 
		GL_FLOAT, 
		GL_FALSE, 
		//shift by float size and half our positions array (amount of verts)
		sizeof(float) * 4, 
		0
	);


	
	std::cout << "Shader Link Test  " << parseShader("res/shaders/VertShader.shader") << std::endl;
	
	unsigned int shader = CreateShader(parseShader("res/shaders/VertShader.shader"), parseShader("res/shaders/FragShader.shader"));
	glUseProgram(shader);
	//glDisableVertexAttribArray(0);
	

	while (!glfwWindowShouldClose(window))
	{
		//bit buggy right now
		//glDrawArrays(GL_QUADS, 0, 4);

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUAD_STRIP);


		glVertex2f(-size, -size);
		glVertex2f(-size, size);
		glVertex2f(size, -size);
		glVertex2f(size, size);
		glEnd();


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
	

}


