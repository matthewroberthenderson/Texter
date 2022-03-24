#include"Renderer.h"
#include "IndicesHelpers.h"


IndicesBuffer::IndicesBuffer(const unsigned int* data, unsigned int count)
	:OpenGL_IndicesCount(count)
{

	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	//unsigned int buff;
	glGenBuffers(1, &OpenGL_ObjectType_ID);

	//and we bind this buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGL_ObjectType_ID);

	//describe the data in the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);


}

IndicesBuffer::~IndicesBuffer()
{
	glDeleteBuffers(1, &OpenGL_ObjectType_ID);
}

void  IndicesBuffer::SelectForRendering() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGL_ObjectType_ID);
}

void  IndicesBuffer::UnSelectForRendering() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
