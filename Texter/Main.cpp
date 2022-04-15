#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include "TexterRenderer/indicesHelpers.h"
#include "TexterRenderer/VertexHelpers.h"
#include <glew.h>
#include "TexterRenderer/VertexArrayObject.h"
#include <GLFW/glfw3.h>
#include "./TexterRenderer/TextureClass/TextureBase.h"
#include "./TexterRenderer/ShaderCore/ShaderCore.h"
#include "Main.h"

#include "TexterRenderer/Renderer.h"


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

			glDeleteProgram(Ref);

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

 
void ThreadedTimeUpdate() {

	std::thread([&]
	{
		while (true)
		{
			// Wait 5 minutes
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			(Time += 0.001f);

			// Call our method
			//std::cout << Time << std::endl;

	
		}
	}).detach();


}


int main(void)
{


	//check everything for GL to present is ready
	//exit if not
	CheckGLInits();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	//open a new rendering context "window"
	GLFWwindow* window = glfwCreateWindow(width, height, "TEXTER", NULL, NULL);


	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	

	//set fps to just the native screen refresh rate (think ming is just 60fps)
	glfwSwapInterval(1);


	glewExperimental = GL_FALSE;


	if (!glewInit() == GLEW_OK) {
		exit(-1);
	}


	float VertexPositions[] = 
	{
		 -size,-size, 0,0, //0
		  size,-size, 0,1, //1
		  size, size, 1,0,//2
		 -size, size ,1,1//3
	};

	

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};



	
	unsigned int VertexAttributeObject;

	VertexArrayObject VertexArray;
	VertexBuffer VertexBufferInstance(VertexPositions, 4 * 4 * sizeof(float));
	VertexBufferDescription VertexBufferDescription;
	VertexBufferDescription.AddToDataDescription<float>(2);
	VertexBufferDescription.AddToDataDescription<float>(2);
	VertexArray.AddBuffer(VertexBufferInstance, VertexBufferDescription);



	 IndicesBuffer IndicesBufferInstance(indices, 6);

	//glBindVertexArray(VertexAttributeObject);
	//but when we enable

	glEnableVertexAttribArray(0);

	glBufferData
	(
		GL_ELEMENT_ARRAY_BUFFER,
		6 * sizeof(unsigned int),
		indices,
		GL_STATIC_DRAW
	);

	
	std::cout << "Shader Link Test  " << parseShader("res/shaders/VertShader.shader") << std::endl;
	//unsigned int shader = CreateShader(parseShader("res/shaders/VertShader.shader"), parseShader("res/shaders/FragShader.shader"));
	std::string V = "res/shaders/VertShader.shader";
	std::string F = "res/shaders/FragShader.shader";


	ShaderBase Shader(V, F);
	Shader.SelectForRendering();

	TextureBase Tex("\res\textures\IconMain.png");
	

	//Shader.SetParameter4("u_Params", Time, width, height, 1.0);

	//glUseProgram(0);



	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	


	ThreadedTimeUpdate(); 

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//GLCHECKERROR(glUseProgram(shader));
		Shader.SelectForRendering();

		GLClearError();
		//GL_UNSIGNED_INT

		//when we bind a vertex array
		IndicesBufferInstance.SelectForRendering();

		VertexArray.SelectForRendering();



		std::string n = "u_Params";
		Shader.SetParameter4(n, Time, width, height, 1.0);

		Tex.SelectForRendering();
		std::string b = "u_Texture";
		Shader.SetParameterTexture(b,1);



		GLCHECKERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		
	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	

	glfwTerminate();
	return 0;
	
}


