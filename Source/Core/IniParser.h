#pragma once
#include "Macros.h"
#include <map>


class HYDRO_API IniParser
{
public:
    explicit IniParser(std::fstream& Stream);

    void WriteCategory(const std::string& Category);
    void WriteElement(const std::string& Key, const std::string& Value);
    void Write(const std::string& Category, const std::vector<std::pair<std::string, std::string>>& Data);

private:
    std::string m_CurrentCategory;
    std::fstream& m_Stream;
};
