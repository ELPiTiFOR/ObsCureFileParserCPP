#pragma once

#include <cstdint>
#include <string>

namespace utils
{
    std::uint32_t lsbOf(std::uint32_t n);
    std::uint16_t lsbOf(std::uint16_t n);
    std::uint32_t hexStringToUint(const std::string& str);
    std::string uintToHexString(std::uint32_t n);
    std::uint32_t stringToUint(const std::string& str);
    std::string uintToString(std::uint32_t n);
    std::uint32_t crc32(std::uint8_t* msg, int len);
    std::uint32_t crc32(std::ifstream& stream);
}