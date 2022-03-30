#pragma once
#include <vector>
#include <glew.h>
#include "Renderer.h"

struct VertexBuffer_DescribeElement
{
public:

	unsigned int dataType;
	unsigned int dataCount;

	//char cheaper then an int
	// ^^^scratch that i was wrong - memory alignment
	unsigned char isNormalised;

	static unsigned int SizeOfDataType(unsigned int type) {
		switch (type)
		{

		case GL_FLOAT:
			return 4;
			//return sizeof(GLfloat);
			break;

		case GL_UNSIGNED_INT:
			return 4;
			//return sizeof(GLuint);
			break;

		case GL_UNSIGNED_BYTE:
			return 1;
			//return sizeof(GLbyte);
			break;

		}

		//if no type recognised im not supporting it yet, silly me :  ^ O
		ASSERT(false);

		return 0;

	};

};

class VertexBufferDescription
{
private:
   //element description storage
	std::vector<VertexBuffer_DescribeElement> VertexBuffer_ElementDescriptions;
	unsigned int VertexBufferDescription_Stride;

public:
	//in constructor just set defaults for tracked data
	VertexBufferDescription() : VertexBufferDescription_Stride(0){}


	//template base
	template<typename T>
	void AddToDataDescription(unsigned int  count)
	{

		static_assert(false);

	}

	//handle all types - Template

	//FLOAT
	template<>
	void AddToDataDescription<float>(unsigned int count)
	{
		VertexBuffer_ElementDescriptions.push_back({GL_FLOAT, count, GL_FALSE });
		VertexBufferDescription_Stride += VertexBuffer_DescribeElement::SizeOfDataType(GL_FLOAT)*count;
	}

	//unsigned INT
	template<>
	void AddToDataDescription<unsigned int>(unsigned int  count)
	{
		VertexBuffer_ElementDescriptions.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		VertexBufferDescription_Stride += VertexBuffer_DescribeElement::SizeOfDataType(GL_UNSIGNED_INT)*count;
	}

	//unsigned char (bytes)
	template<>
	void AddToDataDescription<unsigned char>(unsigned int  count)
	{
		//normalise bytes
		VertexBuffer_ElementDescriptions.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		VertexBufferDescription_Stride += VertexBuffer_DescribeElement::SizeOfDataType(GL_UNSIGNED_BYTE)*count;

	}


	//return element descriptions
	inline const std::vector< VertexBuffer_DescribeElement> GetElementDescriptions() const { return VertexBuffer_ElementDescriptions;};
	
	//return VertexBuffer's Stride
	inline unsigned int GetStride() const { return VertexBufferDescription_Stride;  }


};