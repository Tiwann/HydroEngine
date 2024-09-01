#include "Stream.h"

bool Hydro::Stream::IsOpened() const
{
    return m_Opened;
}

void Hydro::Stream::Close()
{
    m_Opened = false;
}

Hydro::Stream::SizeType Hydro::Stream::ReadChar(char& OutChar)
{
    return Read(&OutChar, sizeof(char));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt8(int8& OutInt)
{
    return Read(&OutInt, sizeof(int8));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt16(int16& OutInt)
{
    return Read(&OutInt, sizeof(int16));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt32(int32& OutInt)
{
    return Read(&OutInt, sizeof(int32));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt64(int64& OutInt)
{
    return Read(&OutInt, sizeof(int64));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt8(uint8& OutInt)
{
    return Read(&OutInt, sizeof(uint8));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt16(uint16& OutInt)
{
    return Read(&OutInt, sizeof(uint16));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt32(uint32& OutInt)
{
    return Read(&OutInt, sizeof(uint32));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt64(uint64& OutInt)
{
    return Read(&OutInt, sizeof(uint64));
}

Hydro::Stream::SizeType Hydro::Stream::ReadString(String& Str, SizeType Count)
{
    HYDRO_ASSERT(Count <= Str.Count(), "String is not big enough!");
    return Read(*Str, Count);
}

Hydro::Stream::SizeType Hydro::Stream::WriteChar(const char InChar)
{
    return Write(&InChar, sizeof(char));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt8(const int8& InInt)
{
    return Write(&InInt, sizeof(int8));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt16(const int16& InInt)
{
    return Write(&InInt, sizeof(int16));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt32(const int32& InInt)
{
    return Write(&InInt, sizeof(int32));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt64(const int64& InInt)
{
    return Write(&InInt, sizeof(int64));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt8(const uint8& InInt)
{
    return Write(&InInt, sizeof(uint8));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt16(const uint16& InInt)
{
    return Write(&InInt, sizeof(uint16));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt32(const uint32& InInt)
{
    return Write(&InInt, sizeof(uint32));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt64(const uint64& InInt)
{
    return Write(&InInt, sizeof(uint64));
}

Hydro::Stream::SizeType Hydro::Stream::WriteString(const String& Str)
{
    return Write(*Str, Str.Count());
}
