#include "utils.hh"

#include <cctype>
#include <sstream>
#include <string>
#include <stdexcept>

std::uint32_t utils::lsbOf(std::uint32_t n)
{
    char buf[4] = {0};
    char* buf_c = buf;
    void* buf_v = buf_c;
    std::uint32_t* buf_u = reinterpret_cast<std::uint32_t*>(buf_v);
    *buf_u = n;
    char aux = buf[0];
    buf[0] = buf[3];
    buf[3] = aux;
    aux = buf[2];
    buf[2] = buf[1];
    buf[1] = aux;

    return *buf_u;
}

std::uint32_t utils::hexStringToUint(const std::string& str)
{
    for (const char& c : str)
    {
        if (!std::isxdigit(c))
        {
            throw std::invalid_argument("Invalid Argument");
        }

    }
    unsigned long res = std::stoul(str, nullptr, 16);
    return static_cast<std::uint32_t>(res);
}

std::string utils::uintToHexString(std::uint32_t n)
{
    std::stringstream stream;
    stream << std::hex << n;
    std::string res(stream.str());
    return res;
}

std::uint32_t utils::stringToUint(const std::string& str)
{
    return std::stoul(str);
}

std::string utils::uintToString(std::uint32_t n)
{
    std::stringstream stream;
    stream << n;
    std::string res(stream.str());
    return res;
}