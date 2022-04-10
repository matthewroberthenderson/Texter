#pragma once
#include <iostream>
#include "../Renderer.h"
#include "../Texture/stb_image/stb_image.h"

class TextureBase
{

public:

	inline int GetWidth() 
	const { 
		return TextureWidth;

	}

	inline int GetHeight()
		const {
		return TextureHeight;

	}



	TextureBase(const std::string &path)
		:
		TextureRenderID(0),
		TextureFilePath(path), 
		TextureWidth(0), 
		TextureHeight(0),
		LocalTextureBuffer(0),
		TextureBitsPerPixel(0)
	{
		//flip texture because opengl reads the pixels from bottom left.
		//bottom left = 0,0
		//not like scan lines
		//depends on the texture format
		stbi_set_flip_vertically_on_load(1);

		LocalTextureBuffer = stbi_load
		(
			path.c_str(),
			&TextureWidth,
			&TextureHeight,
			&TextureBitsPerPixel,
			4
		);

		    GLCHECKERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);)
			GLCHECKERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);)

			//_S and _T specifiec X or Y of the texture, clamp or tile will do what oyu expect on that axis
			GLCHECKERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);)
			GLCHECKERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);)

			GLCHECKERROR(glGenTextures(1, &TextureRenderID);)
			GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, TextureRenderID);)

			GLCHECKERROR(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalTextureBuffer);)
			//unbind it
			GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, 0);)

			if(LocalTextureBuffer)
			{

				stbi_image_free(LocalTextureBuffer);
			
			}
	}

	~TextureBase() 
	{
		//remove texture from texture memory
		//free up that slot m8
		GLCHECKERROR(glDeleteTextures(1, &TextureRenderID);)

	}


	void Bind( unsigned int Slot = 0) const 
	{
		//pick a slot
		GLCHECKERROR(glActiveTexture(GL_TEXTURE0 + Slot);)

		
		GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, TextureRenderID);)
	}

	void unBind() 
	{
		GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, 0);)
	}


	std::string GetName() 
	{

		std::string NullWarning;
		NullWarning = "No Name Found. Was Null";

		if (&Name) {
			return *Name;
		}
		else 
		{
			return NullWarning;
		}
	}

private:

	unsigned int TextureRenderID;
	std::string TextureFilePath;
	unsigned char* LocalTextureBuffer;
	int TextureWidth, TextureHeight, TextureBitsPerPixel;

	std::string * Name;


};