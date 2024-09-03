#pragma once
#include "Stream.h"
#include "Core/Containers/DynamicArray.h"

namespace Hydro
{
    class MemoryStream : public Stream
    {
    public:
        explicit MemoryStream(const Array<u8>& InBuffer, OpenModeFlags OpenMode)
        : Stream(OpenMode), m_Buffer(InBuffer) { m_Opened = true; }
        
        SizeType    Read(void* OutBuffer, SizeType Count) override;
        SizeType    Write(const void* InBuffer, SizeType Count) override;
        bool        Seek(Hydro::Seek SeekMode, OffsetType Offset) override;
        OffsetType  Tell() const override;
        void        Close() override;
    private:
        Array<u8> m_Buffer;
        OffsetType m_Position = 0;
    };
}
