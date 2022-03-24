#pragma once


class VertexBuffer 
{

private:
	unsigned int OpenGL_ObjectType_ID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	// const as these dont modify anything
	void SelectForRendering() const;

	void UnSelectForRendering() const;


};