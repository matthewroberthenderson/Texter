#pragma once


class IndicesBuffer
{

private:
	unsigned int OpenGL_ObjectType_ID;
	unsigned int OpenGL_IndicesCount;

public:

	IndicesBuffer(const unsigned int* data, unsigned int IndicesCount);
	~IndicesBuffer();


	void SelectForRendering() const;
	void UnSelectForRendering() const;

	inline unsigned int GetCount() const {
		return OpenGL_IndicesCount;
	}




};