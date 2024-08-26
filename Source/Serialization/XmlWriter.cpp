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

    template <typename ValueType>
    void XmlWriter::BeginElement(const String& Name, const Map<String, ValueType>& Attributes)
    {
        HYDRO_ASSERT(m_DocumentBegun, "Bad Xml: Did you call BeginDocument() ?");
        Array<String> FormattedAttributes;
        for(const Pair<String, ValueType>& Attribute : Attributes)
            FormattedAttributes.Add(Format("{}=\"{}\"", Attribute.Key, Attribute.Value));
            
        String Content;
        Content.Append(Name);
        for(const String& Attribute : FormattedAttributes)
            Content.Append(Format(" {}", Attribute));

        const String Tag = Format("{}<{}>\n", GetIndentation(), Content);
        m_Stream->WriteString(Tag);
        m_NumIndentation++;
        m_Elements.Add(Name);
    }

    template <typename ValueType>
    void XmlWriter::ElementInline(const String& Name, const Map<String, ValueType>& Attributes)
    {
        HYDRO_ASSERT(m_DocumentBegun, "Bad Xml: Did you call BeginDocument() ?");
        Array<String> FormattedAttributes;
        for(const Pair<String, ValueType>& Attribute : Attributes)
            FormattedAttributes.Add(Format("{}=\"{}\"", Attribute.Key, Attribute.Value));
            
        String Content;
        Content.Append(Name);
        for(const String& Attribute : FormattedAttributes)
            Content.Append(Format(" {}", Attribute));

        const String Tag = Format("{}<{}/>\n", GetIndentation(), Content);
        m_Stream->WriteString(Tag);
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
