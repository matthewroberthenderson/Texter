#include <iostream>
#include <GLFW/glfw3.h>

bool GL_LibCheck() {

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


int main() 
{
	GL_LibCheck();
	std::cin.get();
}