#include"Renderer.h"
#include"VertexHelpers.h"


VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{

	//unsigned int buff;
	glGenBuffers(1, &OpenGL_ObjectType_ID);

	//and we bind this buffer
	glBindBuffer(GL_ARRAY_BUFFER, OpenGL_ObjectType_ID);

	//describe the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);



	//unsigned int buff;
	//glGenBuffers(1, &buff);

	////and we bind this buffer
 //   glBindBuffer(GL_ARRAY_BUFFER, buff);

	//glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), VertexPositions, GL_STATIC_DRAW);

	////!!!! nothing actually links the two..



}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &OpenGL_ObjectType_ID);
}

void VertexBuffer::SelectForRendering() const
{
	glBindBuffer(GL_ARRAY_BUFFER, OpenGL_ObjectType_ID);
}

void VertexBuffer::UnSelectForRendering() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
