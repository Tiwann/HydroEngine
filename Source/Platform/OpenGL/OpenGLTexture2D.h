﻿#pragma once
#include "Core/Texture2D.h"

typedef i32 GLint;

namespace Hydro
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& Name, u32 Width, u32 Height, const TextureParams& Params, u32 Slot);
        ~OpenGLTexture2D() override;

        void SetTextureParameters(const TextureParams& Params) override;
        void SetData(u8* Data, u32 Width, u32 Height, ImageFormat Format) override;
        void SetData(const Ref<Image>& Image) override;
        Ref<Image> GetImage() const override;
        void Bind() const override;
        void Unbind() const override;

        uintptr_t GetHandle() const override;
    private:
        u32 FormatToOpenGLFormat(ImageFormat Format) const;
        u32 FormatToType(ImageFormat Format) const;

    private:
        u32 m_Handle{UINT32_MAX};
        GLint GetTextureWrap(TextureWrap Wrap);
        GLint GetTextureFilter(TextureFilter Filter);
    };
}
