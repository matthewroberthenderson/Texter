#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include "TexterRenderer/indicesHelpers.h"
#include "TexterRenderer/VertexHelpers.h"
#include <glew.h>
#include <GLFW/glfw3.h>
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
		 -size,-size, //0
		  size,-size, //1
		  size, size, //2
		 -size, size  //3
	};

	

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};


	//important note
	//vertex attribute pointer will bind a vertex buffer (something connected to the GL ARRAYBUFFER slot)
	//with the actual layout or specification for the draw
	//right now OpenGL is running in compat mode so it creates one for us ( index 0 above)
	//need to do this manually when suing Core profile



	
	unsigned int VertexAttributeObject;

	//we are just making one so put "1"
	GLCHECKERROR(glGenVertexArrays(1,&VertexAttributeObject));

	//when we bind this array
	GLCHECKERROR(glBindVertexArray(VertexAttributeObject));


	//REFACTOR ABSTRACTION
	VertexBuffer VertexBufferInstance(VertexPositions, 4 * 2 * sizeof(float));
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	//create index buffer for indicies
	//buffer  --------

	 IndicesBuffer IndicesBufferInstance(indices, 6);

	glBindVertexArray(VertexAttributeObject);
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
	unsigned int shader = CreateShader(parseShader("res/shaders/VertShader.shader"), parseShader("res/shaders/FragShader.shader"));

	


	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	


	ThreadedTimeUpdate(); 

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		GLCHECKERROR(glUseProgram(shader));
		GLClearError();
		//GL_UNSIGNED_INT

		//when we bind a vertex array
		IndicesBufferInstance.SelectForRendering();

		//and we bind a buffer
		glBindVertexArray(VertexAttributeObject);
		

	    //get location of the uniform i put in the shader
		int location = glGetUniformLocation(shader, "u_Params");

		//Uniform might have been removed from the shader or whatever so just assert. 
		ASSERT(location != -1);

		//set the uniforms with some data i can use
		GLCHECKERROR(glUniform4f(location, Time, width, height, 1.0));
		

		GLCHECKERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	

	glfwTerminate();
	return 0;
	
}


