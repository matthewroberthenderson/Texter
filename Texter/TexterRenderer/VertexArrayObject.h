#pragma once
#include "VertexHelpers.h"
#include "VertexBufferDescription.h"

class VertexArrayObject {


private:

	unsigned int GL_Object_RenderID;


public:
	VertexArrayObject();
	~VertexArrayObject();


	void AddBuffer(const VertexBuffer &VertexBufferRef, const VertexBufferDescription &VertexBufferDescription);

	void SelectForRendering() const;
	void DeSelectForRendering() const;

};