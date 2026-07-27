#pragma once

#include <cstdint>
#include <string>

namespace utils
{
    std::uint32_t lsbOf(std::uint32_t n);
    std::uint32_t hexStringToUint(const std::string& str);
    std::string uintToHexString(std::uint32_t n);
    std::uint32_t stringToUint(const std::string& str);
    std::string uintToString(std::uint32_t n);
}