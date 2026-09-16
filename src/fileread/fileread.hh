#pragma once

#include <cstdint>
#include <fstream>
#include <filesystem>

namespace fileread
{
    std::uint32_t read4ByteMsb(std::ifstream& is);
    std::uint32_t read4ByteLsb(std::ifstream& is);
    std::uint16_t read2ByteMsb(std::ifstream& is);
    std::uint16_t read2ByteLsb(std::ifstream& is);
    std::uint8_t read1Byte(std::ifstream& is);
    std::string readString(std::ifstream& is, int length);
    std::string readLString(std::ifstream& is);
    float readFloatMsb(std::ifstream& is);
    float readFloatLsb(std::ifstream& is);
    void skipBytes(std::ifstream& is, std::uint32_t count);
    bool areFilesEqual(std::filesystem::path path1,
        std::filesystem::path path2);
}