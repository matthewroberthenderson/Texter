#include "VertexArrayObject.h"
#include "Renderer.h"





VertexArrayObject::VertexArrayObject()
{


	//on construction, create array
	GLCHECKERROR(glGenVertexArrays(1, &GL_Object_RenderID));

	

}




VertexArrayObject::~VertexArrayObject()
{

	//on destroy, delete the array
	glDeleteVertexArrays(1, &GL_Object_RenderID);
}



void VertexArrayObject::AddBuffer(const VertexBuffer & VertexBufferRef, const VertexBufferDescription& VertexBufferDescriptionRef)
{

	//slect vertex array we want to render with (bind array)
	SelectForRendering();
	//slect vertex buffer we want to render with (bind buffer)
	VertexBufferRef.SelectForRendering();
	
	//const auto &VertexBufferDescriptions = VertexBufferDescriptionRef.GetElementDescriptions();

	const auto& VertexBufferDescriptions = VertexBufferDescriptionRef.GetElementDescriptions();

	//std::vector<VertexBuffer_DescribeElement>

	//array offset in bytes
	unsigned int Offset = 0;
	//unsigned int i = 0; i < VertexBufferDescriptions.size; i++
	int i = 0;
	for (const auto& VertexBufferDescription : VertexBufferDescriptions)
	{ 
		const auto CURRENT_VertexBufferDescription = VertexBufferDescriptions[i];
		unsigned int datatype = CURRENT_VertexBufferDescription.dataType;

		//enable this description as our current attribute array
		GLCHECKERROR(glEnableVertexAttribArray(i);)
			
	    //fill out descriptions for the vertex buffer
		GLCHECKERROR
		(
				glVertexAttribPointer
				(
					i,
					CURRENT_VertexBufferDescription.dataCount,
					datatype,
					CURRENT_VertexBufferDescription.isNormalised,
					VertexBufferDescriptionRef.GetStride(),
					(const void*)Offset
				);
		)
		 
		//itter offset for each array
		Offset += CURRENT_VertexBufferDescription.dataCount * VertexBuffer_DescribeElement::SizeOfDataType(datatype);
		i++;
	}

	
}

void VertexArrayObject::SelectForRendering() const
{

	GLCHECKERROR(glBindVertexArray(GL_Object_RenderID));
}

void VertexArrayObject::DeSelectForRendering() const
{
	//just unvalue the currently selected in state
	GLCHECKERROR(glBindVertexArray(0));
}
