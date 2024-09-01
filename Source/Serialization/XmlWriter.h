#pragma once
#include "Stream.h"
#include "Core/Containers/String.h"
#include "Core/Containers/Map.h"
#include <functional>

namespace Hydro
{
    struct XmlSettings
    {
        int32 Indentation = 4;
        char    IndentationCharacter = ' ';

        static XmlSettings Default;
    };
    
    class XmlWriter final
    {
    public:
        using AttributeType = Map<String, String>;
        XmlWriter(Stream& Stream, const XmlSettings& Settings = {});
        ~XmlWriter();

        void Comment(const String& Comment);
        void BeginDocument(int32 VersionMaj, int32 VersionMin);
        void BeginElement(const String& Name, const AttributeType& Attributes);
        void ElementInline(const String& Name, const AttributeType& Attributes);
        void EndElement();
        void Element(const String& Name, const AttributeType& Attributes, const std::function<void()>& Content = nullptr);
        void Write(const String& Value);
    private:
        Stream* m_Stream;
        XmlSettings m_Settings;
        Array<String> m_Elements;
        uint32 m_NumIndentation = 0;
        bool m_DocumentBegun = false;

        String GetIndentation();
    };
}
