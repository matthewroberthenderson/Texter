#pragma once
#include <GL/glew.h>
#include "Debug.h"
#include <thread>
#include "VertexArray.h"
#include "IndexBufferHelpers.h"
#include "ShaderBase.h"


class Renderer
{
    public:

        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderBase& shader) const;
		float Time;

};
