#include "HydroPCH.h"
#include "IniParser.h"

#include <fstream>

#include "Assertion.h"
#include "spdlog/fmt/fmt.h"

IniParser::IniParser(std::fstream& Stream) : m_Stream(Stream)
{
    HYDRO_ASSERT(m_Stream.is_open(), "IniParser: Stream is not opened or is eof!");
}

void IniParser::WriteCategory(const std::string& Category)
{
    m_Stream << fmt::format("[{}]\n", Category);
}

void IniParser::WriteElement(const std::string& Key, const std::string& Value)
{
    m_Stream << fmt::format("{} = {}\n", Key, Value);
}

void IniParser::Write(const std::string& Category, const std::vector<std::pair<std::string, std::string>>& Data)
{
    WriteCategory(Category);
    for(const auto& pair : Data)
    {
        WriteElement(pair.first, pair.second);
    }
}
