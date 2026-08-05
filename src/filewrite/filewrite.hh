#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>

namespace filewrite
{
    void write4ByteMsb(std::ofstream& os, std::uint32_t n);
    void write4ByteLsb(std::ofstream& os, std::uint32_t n);
    void write2ByteMsb(std::ofstream& os, std::uint16_t n);
    void write2ByteLsb(std::ofstream& os, std::uint16_t n);
    void write1Byte(std::ofstream& os, std::uint8_t n);

    // Read & Write
    void copyFile(std::filesystem::path src_path,
        std::filesystem::path dst_path);
}