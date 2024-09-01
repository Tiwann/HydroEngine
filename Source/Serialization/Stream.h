#pragma once
#include "OpenMode.h"
#include "Seek.h"
#include "Core/Filesystem.h"
#include "Core/Flags.h"
#include "Core/Containers/StringView.h"

namespace Hydro
{
    class Stream
    {
    public:
        using SizeType = size_t;
        using OffsetType = off_t;
        
        Stream(OpenModeFlags OpenMode) : m_OpenMode(OpenMode){}
        virtual ~Stream() = default;
        
        bool IsOpened() const;

        virtual SizeType Read(void* OutBuffer, SizeType Count) = 0;
        virtual SizeType Write(const void* InBuffer, SizeType Count) = 0;
        virtual bool Seek(Seek SeekMode, OffsetType Offset) = 0;
        virtual OffsetType Tell() const = 0;
        virtual void Close();

        SizeType ReadChar(char& OutChar);
        SizeType ReadInt8(int8& OutInt);
        SizeType ReadInt16(int16& OutInt);
        SizeType ReadInt32(int32& OutInt);
        SizeType ReadInt64(int64& OutInt);
        SizeType ReadUInt8(uint8& OutInt);
        SizeType ReadUInt16(uint16& OutInt);
        SizeType ReadUInt32(uint32& OutInt);
        SizeType ReadUInt64(uint64& OutInt);

        template<typename Type>
        SizeType ReadBuffer(Buffer<Type>& OutBuffer, SizeType Count)
        {
            OutBuffer = Buffer<Type>(Count);
            return Read(OutBuffer.GetData(), Count);
        }

        SizeType ReadString(String& Str, SizeType Count);

        SizeType WriteChar(const char InChar);
        SizeType WriteInt8(const int8& InInt);
        SizeType WriteInt16(const int16& InInt);
        SizeType WriteInt32(const int32& InInt);
        SizeType WriteInt64(const int64& InInt);
        SizeType WriteUInt8(const uint8& InInt);
        SizeType WriteUInt16(const uint16& InInt);
        SizeType WriteUInt32(const uint32& InInt);
        SizeType WriteUInt64(const uint64& InInt);
        SizeType WriteString(const String& Str);

    protected:
        bool m_Opened = false;
        OpenModeFlags m_OpenMode = OpenModeFlagBits::None;
    };
}

