#include "MemoryStream.h"

namespace Hydro
{
    Stream::SizeType MemoryStream::Read(void* OutBuffer, SizeType Count)
    {
        if(!m_Opened) return -1;
        memcpy(OutBuffer, &m_Buffer[m_Position], Count);
        m_Position += (OffsetType)Count;
        return Count;
    }

    Stream::SizeType MemoryStream::Write(const void* InBuffer, SizeType Count)
    {
        if(!m_Opened) return -1;
        if(m_Position + Count > m_Buffer.Count()) return -1;
        memcpy(&m_Buffer[m_Position], InBuffer, Count);
        m_Position += (OffsetType)Count;
        return Count;
    }

    bool MemoryStream::Seek(Hydro::Seek SeekMode, OffsetType Offset)
    {
        if(!m_Opened) return false;
        switch (SeekMode) {
        case Seek::Begin:
            if(Offset < 0) return false;
            m_Position = Offset;
            return true;
        case Seek::Current:
            if(m_Position + Offset < 0) return false;
            m_Position += Offset;
            return true;
        case Seek::End:
            if(Offset > 0) return false;
            m_Position = (OffsetType)m_Buffer.Count() + Offset;
            return true;
        }
        return false;
    }

    Stream::OffsetType MemoryStream::Tell() const
    {
        return m_Opened ? m_Position : -1;
    }

    void MemoryStream::Close()
    {
        Stream::Close();
    }
}
