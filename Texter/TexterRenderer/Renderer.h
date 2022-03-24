#pragma once
#include <glew.h>

#define String std::string
#define ASSERT(x) if(!(x)){__debugbreak();}
#define GLCHECKERROR(x) GLClearError();\
x;\
ASSERT(GLLogCall( #x, __FILE__, __LINE__));

//error checking 
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);