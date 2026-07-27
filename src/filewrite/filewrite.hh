#pragma once

#include <cstdint>
#include <fstream>

namespace filewrite
{
    void write4ByteMsb(std::ofstream& os, std::uint32_t n);
    void write4ByteLsb(std::ofstream& os, std::uint32_t n);
}