#pragma once

#include <cstdint>
#include <fstream>
#include <filesystem>

namespace fileread
{
    std::uint32_t read4ByteMsb(std::ifstream& is);
    std::uint32_t read4ByteLsb(std::ifstream& is);
    bool areFilesEqual(std::filesystem::path path1,
        std::filesystem::path path2);
}