#pragma once
#include "/dev/Texter/Texter/Renderer.h"

class TextureHelpers
{
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;

    public:
		TextureHelpers(const std::string& path);
        ~TextureHelpers();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
};
