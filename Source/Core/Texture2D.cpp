#include "HydroPCH.h"
#include "Texture2D.h"
#include "Platform/PlatformTexture2D.h"

#include "Log.h"
#include "LogVerbosity.h"

namespace Hydro
{
    Texture2D::Texture2D(std::string Name, uint32_t Slot) : m_Name(std::move(Name)), m_Slot(Slot)
    {
        HYDRO_LOG(Texture2D, Trace, "Creating texture \"{}\"", m_Name);
    }

    Texture2D::~Texture2D()
    {
        HYDRO_LOG(Texture2D, Trace, "Destroying texture \"{}\"", m_Name);
    }
    
    Ref<Texture2D> Texture2D::Create(const std::string& Name, uint32_t Slot)
    {
        HYDRO_RHI_PLATFORM_RETURN(Texture2D, Name, Slot);
    }

    Ref<Texture2D> Texture2D::CreateFromFile(const std::string& Name, uint32_t Slot, const Path& Filepath)
    {
        Ref<Texture2D> Texture = Create(Name, Slot);
        ScopedBuffer RawImageData = File::ReadToBuffer(Filepath);
        const Ref<Image> ImageData = CreateRef<Image>(RawImageData.AsBuffer(), RGBA8);
        Texture->SetImage(ImageData);
        return Texture;
    }
    
    uint32_t Texture2D::GetSlot() const
    {
        return m_Slot;
    }

    void Texture2D::SetSlot(uint32_t Slot)
    {
        m_Slot = Slot;
    }
    
}
