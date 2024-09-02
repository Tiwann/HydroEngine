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

Hydro::Stream::SizeType Hydro::Stream::ReadInt8(i8& OutInt)
{
    return Read(&OutInt, sizeof(i8));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt16(i16& OutInt)
{
    return Read(&OutInt, sizeof(i16));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt32(i32& OutInt)
{
    return Read(&OutInt, sizeof(i32));
}

Hydro::Stream::SizeType Hydro::Stream::ReadInt64(i64& OutInt)
{
    return Read(&OutInt, sizeof(i64));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt8(u8& OutInt)
{
    return Read(&OutInt, sizeof(u8));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt16(u16& OutInt)
{
    return Read(&OutInt, sizeof(u16));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt32(u32& OutInt)
{
    return Read(&OutInt, sizeof(u32));
}

Hydro::Stream::SizeType Hydro::Stream::ReadUInt64(u64& OutInt)
{
    return Read(&OutInt, sizeof(u64));
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

Hydro::Stream::SizeType Hydro::Stream::WriteInt8(const i8& InInt)
{
    return Write(&InInt, sizeof(i8));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt16(const i16& InInt)
{
    return Write(&InInt, sizeof(i16));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt32(const i32& InInt)
{
    return Write(&InInt, sizeof(i32));
}

Hydro::Stream::SizeType Hydro::Stream::WriteInt64(const i64& InInt)
{
    return Write(&InInt, sizeof(i64));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt8(const u8& InInt)
{
    return Write(&InInt, sizeof(u8));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt16(const u16& InInt)
{
    return Write(&InInt, sizeof(u16));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt32(const u32& InInt)
{
    return Write(&InInt, sizeof(u32));
}

Hydro::Stream::SizeType Hydro::Stream::WriteUInt64(const u64& InInt)
{
    return Write(&InInt, sizeof(u64));
}

Hydro::Stream::SizeType Hydro::Stream::WriteString(const String& Str)
{
    return Write(*Str, Str.Count());
}
