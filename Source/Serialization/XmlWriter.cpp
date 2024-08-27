#include "XmlWriter.h"
#include "Core/Assertion.h"

namespace Hydro
{
    XmlWriter::XmlWriter(Stream& Stream, const XmlSettings& Settings): m_Stream(&Stream), m_Settings(Settings){}

    XmlWriter::~XmlWriter()
    {
        HYDRO_ASSERT(m_NumIndentation == 0, "Bad Xml: Begin/End mismatch!");
    }

    void XmlWriter::Comment(const String& Comment)
    {
        const String& FormattedComment = Format("{}# {}", GetIndentation(), Comment);
        m_Stream->WriteString(FormattedComment);
    }

    void XmlWriter::BeginDocument(int32_t VersionMaj, int32_t VersionMin)
    {
        const String Version = Format("{}.{}", VersionMaj, VersionMin);
        const String BeginDocument = Format("<?xml version=\"{}\"?>\n", Version);
        m_Stream->WriteString(BeginDocument);
        m_DocumentBegun = true;
    }

    void XmlWriter::BeginElement(const String& Name, const Map<String, String>& Attributes)
    {
        HYDRO_ASSERT(m_DocumentBegun, "Bad Xml: Did you call BeginDocument() ?");
        Array<String> FormattedAttributes;
        for(const Pair<String, String>& Attribute : Attributes)
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

    void XmlWriter::ElementInline(const String& Name, const Map<String, String>& Attributes)
    {
        HYDRO_ASSERT(m_DocumentBegun, "Bad Xml: Did you call BeginDocument() ?");
        Array<String> FormattedAttributes;
        for(const Pair<String, String>& Attribute : Attributes)
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

    void XmlWriter::Element(const String& Name, const AttributeType& Attributes, const std::function<void()>& Content)
    {
        if(!Content)
        {
            ElementInline(Name, Attributes);
            return;
        }

        BeginElement(Name, Attributes);
        Content();
        EndElement();
    }

    String XmlWriter::GetIndentation()
    {
        String Indentation = "";
        for(uint32_t i = 0; i < m_NumIndentation * m_Settings.Indentation; i++)
            Indentation.Append(m_Settings.IndentationCharacter);
        return Indentation;
    }
}
