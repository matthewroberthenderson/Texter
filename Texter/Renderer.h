#pragma once
#include <glew.h>
#include "TexterRenderer/VertexHelpers/Debug.h"
#include <thread>
#include "TexterRenderer/VertexHelpers/VertexArray.h"
#include "TexterRenderer/VertexHelpers/IndexBufferHelpers.h"
#include "TexterRenderer/ShaderCore/ShaderBase.h"


class Renderer
{
    public:

        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderBase& shader) const;
		float Time;

};
