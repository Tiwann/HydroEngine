#pragma once
#include "Stream.h"
#include "Core/Containers/String.h"
#include "Core/Containers/Map.h"
#include "Core/Assertion.h"

namespace Hydro
{
    struct XmlSettings
    {
        int32_t Indentation = 4;
        char    IndentationCharacter = ' ';
    };

    
    class XmlWriter final
    {
    public:
        XmlWriter(Stream& Stream, const XmlSettings& Settings = {}) : m_Stream(&Stream), m_Settings(Settings) {}
        ~XmlWriter()
        {
            HYDRO_ASSERT(m_NumIndentation == 0, "Bad Xml: Begin/End mismatch!");
        }
        
        void BeginDocument(int32_t VersionMaj, int32_t VersionMin);

        template<typename ValueType>
        void BeginElement(const String& Name, const Map<String, ValueType>& Attributes)
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

        template<typename ValueType>
        void ElementInline(const String& Name, const Map<String, ValueType>& Attributes)
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
        
        void EndElement();

        

    private:
        Stream* m_Stream;
        XmlSettings m_Settings;
        Array<String> m_Elements;
        uint32_t m_NumIndentation = 0;
        bool m_DocumentBegun = false;

        String GetIndentation();
    };
}
