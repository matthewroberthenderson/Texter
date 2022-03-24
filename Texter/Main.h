#pragma once

//intrinsics are specific to the compiler
//we are using Microsoft Visual Studio so that is
//__debugbreak()
//if we were using clang or something we would need to use that


namespace Texter {



	int width = 640;
	int height = 480;

	
	const char * FileName = "something";

	GLFWwindow* TestingContext;
	int CreateWindowLegacy();


	float Time = 0;
	bool GL_LibCheck();
	void DrawLegacyQuad(float size);
	




	int CheckGlewInit() 
	{
		if (!glewInit()) {
			std::cout << "error" << std::endl;
		}

		if (!glfwInit()) {
			printf("glfwInit() failed!");
			return 0;
		}
	
	}


	int(*CheckGLInits)() = &CheckGlewInit;
	float size = .9;


}
