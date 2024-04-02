#pragma once
#include "Macros.h"
#include "Buffer.h"
#include "Filesystem.h"
#include "Image.h"
#include "SharedPointer.h"


#include "LogCategory.h"


HYDRO_DECLARE_LOG_CATEGORY_STATIC(Texture2D, "TEXTURE2D");

namespace Hydro
{
    class Image;

    class Texture2D
    {
    public:
        Texture2D(std::string Name, uint32_t Slot);
        virtual ~Texture2D();

        static Ref<Texture2D> Create(const std::string& Name, uint32_t Slot);
        static Ref<Texture2D> CreateFromFile(const std::string& Name, uint32_t Slot, const Path& Filepath);

        
        virtual void SetImage(const Ref<Image>& Image) = 0;
        virtual Ref<Image> GetImage() const = 0;
        virtual void Bind() const = 0;

        uint32_t GetSlot() const;
        void SetSlot(uint32_t Slot);

    protected:
        std::string m_Name;
        uint32_t m_Width{0}, m_Height{0};
        uint32_t m_Slot{0};
        ImageFormat m_Format{RGBA8};
    };
}
