#pragma once
#include "Stream.h"
#include "Core/Containers/String.h"
#include "Core/Containers/Map.h"
#include "Core/Containers/Function.h"

namespace Hydro
{
    struct XmlSettings
    {
        i32 Indentation = 4;
        char    IndentationCharacter = ' ';

        static XmlSettings Default;
    };
    
    class XmlWriter
    {
    public:
        using AttributeType = Map<String, String>;
        XmlWriter(Stream& Stream, const XmlSettings& Settings = {});
        ~XmlWriter();

        void Comment(const String& Comment) const;
        void BeginDocument(i32 VersionMaj, i32 VersionMin);
        void BeginElement(const String& Name, const AttributeType& Attributes);
        void ElementInline(const String& Name, const AttributeType& Attributes) const;
        void EndElement();
        void Element(const String& Name, const AttributeType& Attributes, const Function<void()>& Content = nullptr);
        void Write(const String& Value) const;
    private:
        Stream* m_Stream;
        XmlSettings m_Settings;
        Array<String> m_Elements;
        u32 m_NumIndentation = 0;
        bool m_DocumentBegun = false;

        String GetIndentation() const;
    };
}
