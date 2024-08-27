#include "XmlWriter.h"

namespace Hydro
{
    void XmlWriter::BeginDocument(int32_t VersionMaj, int32_t VersionMin)
    {
        const String Version = Format("{}.{}", VersionMaj, VersionMin);
        const String BeginDocument = Format("<?xml version=\"{}\"?>\n", Version);
        m_Stream->WriteString(BeginDocument);
        m_DocumentBegun = true;
    }
    
    void XmlWriter::EndElement()
    {
        m_NumIndentation--;
        const String Tag = Format("{}</{}>\n", GetIndentation(), m_Elements.Last());
        m_Stream->WriteString(Tag);
        m_Elements.Pop();
    }

    String XmlWriter::GetIndentation()
    {
        String Indentation = "";
        for(uint32_t i = 0; i < m_NumIndentation * m_Settings.Indentation; i++)
            Indentation.Append(m_Settings.IndentationCharacter);
        return Indentation;
    }
}
