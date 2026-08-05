#include "utils.hh"

#include <cctype>
#include <sstream>
#include <string>
#include <stdexcept>

#include "fileread/fileread.hh"

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

std::uint16_t utils::lsbOf(std::uint16_t n)
{
    char buf[2] = {0};
    char* buf_c = buf;
    void* buf_v = buf_c;
    std::uint16_t* buf_u = reinterpret_cast<std::uint16_t*>(buf_v);
    *buf_u = n;
    char aux = buf[0];
    buf[0] = buf[1];
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

std::uint32_t utils::crc32(std::uint8_t* msg, int len)
{
    std::uint32_t res = 0xFFFFFFFF;

    for (int i = 0; i < len; i++)
    {
        res = res ^ msg[i];

        for (int j = 0; j < 8; j++)
        {
            std::uint32_t mask = -(res & 1);
            res = (res >> 1) ^ (0xEDB88320 & mask);
        }
    }

    return ~res;
}

std::uint32_t utils::crc32(std::ifstream& stream)
{
    std::uint32_t res = 0xFFFFFFFF;

    while (stream)
    {
        std::uint8_t next_char = fileread::read1Byte(stream);
        if (!stream)
        {
            break;
        }
        res = res ^ next_char;

        for (int j = 0; j < 8; j++)
        {
            std::uint32_t mask = -(res & 1);
            res = (res >> 1) ^ (0xEDB88320 & mask);
        }
    }

    return ~res;
}