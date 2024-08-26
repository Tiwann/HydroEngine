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

Hydro::Stream::SizeType Hydro::Stream::ReadInt8(int8_t& OutInt)
{
    return Read(&OutInt, sizeof(int8_t));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt16(int16_t& OutInt)
{
    return Read(&OutInt, sizeof(int16_t));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt32(int32_t& OutInt)
{
    return Read(&OutInt, sizeof(int32_t));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt64(int64_t& OutInt)
{
    return Read(&OutInt, sizeof(int64_t));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt8(uint8_t& OutInt)
{
    return Read(&OutInt, sizeof(uint8_t));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt16(uint16_t& OutInt)
{
    return Read(&OutInt, sizeof(uint16_t));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt32(uint32_t& OutInt)
{
    return Read(&OutInt, sizeof(uint32_t));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt64(uint64_t& OutInt)
{
    return Read(&OutInt, sizeof(uint64_t));
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

Hydro::Stream::SizeType Hydro::Stream::WriteInt8(const int8_t& InInt)
{
    return Write(&InInt, sizeof(int8_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt16(const int16_t& InInt)
{
    return Write(&InInt, sizeof(int16_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt32(const int32_t& InInt)
{
    return Write(&InInt, sizeof(int32_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt64(const int64_t& InInt)
{
    return Write(&InInt, sizeof(int64_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt8(const uint8_t& InInt)
{
    return Write(&InInt, sizeof(uint8_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt16(const uint16_t& InInt)
{
    return Write(&InInt, sizeof(uint16_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt32(const uint32_t& InInt)
{
    return Write(&InInt, sizeof(uint32_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt64(const uint64_t& InInt)
{
    return Write(&InInt, sizeof(uint64_t));
}

Hydro::Stream::SizeType Hydro::Stream::WriteString(const String& Str)
{
    return Write(*Str, Str.Count());
}
