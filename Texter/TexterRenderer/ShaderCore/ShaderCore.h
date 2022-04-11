#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Renderer.h"

struct ShaderProgramLocations
{
	std::string VertexProgramLocation;
	std::string FragementProgramLocation;

};


class ShaderBase {

public:

	ShaderBase(std::string &VertShaderLocation, std::string &FragShaderLocation)
		:CurrentSetVertexShaderPath(VertShaderLocation), CurrentSetFragmentShaderPath(FragShaderLocation), RenderID(0)
	{
		std::cout << "Shader Link Test  " << parseShader("res/shaders/VertShader.shader") << std::endl;
		RenderID = CreateShader(parseShader(VertShaderLocation), parseShader(FragShaderLocation));
		//"res/shaders/VertShader.shader"
		//"res/shaders/FragShader.shader"
			
	}

	~ShaderBase() 
	{
		GLCHECKERROR(glDeleteProgram(RenderID);)

	}

	//bind
	void SelectForRendering() const 
	{
		GLCHECKERROR(glUseProgram(RenderID);)
	};

	//unbind
	void UnSelectForRendering() const 
	{
		GLCHECKERROR(glUseProgram(0);)
	};

	unsigned int GetParameterLocation(std::string &Location)
	{
		GLCHECKERROR(int CurrentProgramLocation = glGetUniformLocation(RenderID, Location.c_str()));
		if (CurrentProgramLocation == -1)
		{
			std::cout << "Hey, couldn't find the shader champ, Check ShaderCore.h";
			return 0;
		}
		return CurrentProgramLocation;
	}

	void SetParameter4(std::string &name, float Param_01, float Param_02, float Param_03, float Param_04)
	{
		
		GLCHECKERROR(glUniform4f(GetParameterLocation(name), Param_01, Param_02, Param_03, Param_04);)
	}




private:


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

	unsigned int CreateShader(const std::string &VertexShader, const std::string &FragmentShader)
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

	int CompileShader() 
	{

	}
	
	unsigned int RenderID;
	std::string CurrentSetVertexShaderPath;
	std::string CurrentSetFragmentShaderPath;

	
	//""u_Params"

};