#pragma once
#include "Core/Texture2D.h"

typedef int32 GLint;

namespace Hydro
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& Name, uint32 Width, uint32 Height, const TextureParams& Params, uint32 Slot);
        ~OpenGLTexture2D() override;

        void SetTextureParameters(const TextureParams& Params) override;
        void SetData(uint8* Data, uint32 Width, uint32 Height, ImageFormat Format) override;
        void SetData(const Ref<Image>& Image) override;
        Ref<Image> GetImage() const override;
        void Bind() const override;
        void Unbind() const override;

        uintptr_t GetHandle() const override;
    private:
        uint32 FormatToOpenGLFormat(ImageFormat Format) const;
        uint32 FormatToType(ImageFormat Format) const;

    private:
        uint32 m_Handle{UINT32_MAX};
        GLint GetTextureWrap(TextureWrap Wrap);
        GLint GetTextureFilter(TextureFilter Filter);
    };
}
