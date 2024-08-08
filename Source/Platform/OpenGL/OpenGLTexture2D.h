﻿#pragma once
#include "Core/Texture2D.h"

namespace Hydro
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& Name, uint32_t Width, uint32_t Height, uint32_t Slot);
        ~OpenGLTexture2D() override;

        void SetData(uint8_t* Data, uint32_t Width, uint32_t Height, ImageFormat Format) override;
        void SetData(const Ref<Image>& Image) override;
        Ref<Image> GetImage() const override;
        void Bind() const override;

        uintptr_t GetHandle() const override;
    private:
        uint32_t FormatToOpenGLFormat(ImageFormat Format) const;
        uint32_t FormatToType(ImageFormat Format) const;

    private:
        uint32_t m_Handle{UINT32_MAX};
    };
}
