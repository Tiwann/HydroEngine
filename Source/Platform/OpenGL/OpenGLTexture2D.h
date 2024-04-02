#pragma once
#include "Core/Texture2D.h"

namespace Hydro
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& Name, uint32_t Slot);
        ~OpenGLTexture2D() override;
        
        void SetImage(const Ref<Image>& Image) override;
        Ref<Image> GetImage() const override;
        void Bind() const override;
    private:
        uint32_t FormatToOpenGLFormat(ImageFormat Format) const;
        uint32_t FormatToType(ImageFormat Format) const;

    private:
        uint32_t m_Handle{UINT32_MAX};
    };
}
