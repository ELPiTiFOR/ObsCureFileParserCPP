#include "fileread.hh"

#include "utils/utils.hh"

std::uint32_t fileread::read4ByteMsb(std::ifstream& is)
{
    std::uint32_t item_type = 0;
    is.read(reinterpret_cast<char*>(&item_type), 4);
    item_type = utils::lsbOf(item_type);
    return item_type;
}

std::uint32_t fileread::read4ByteLsb(std::ifstream& is)
{
    std::uint32_t item_type = 0;
    is.read(reinterpret_cast<char*>(&item_type), 4);
    return item_type;
}

std::uint16_t fileread::read2ByteMsb(std::ifstream& is)
{
    std::uint16_t res = 0;
    is.read(reinterpret_cast<char*>(&res), 2);
    res = utils::lsbOf(res);
    return res;
}

std::uint16_t fileread::read2ByteLsb(std::ifstream& is)
{
    std::uint16_t res = 0;
    is.read(reinterpret_cast<char*>(&res), 2);
    return res;
}

std::uint8_t fileread::read1Byte(std::ifstream& is)
{
    std::uint8_t res = 0;
    is.read(reinterpret_cast<char*>(&res), 1);
    return res;
}

std::string fileread::readString(std::ifstream& is, int length)
{
    char buf[length + 1] = { 0 };
    is.read(reinterpret_cast<char*>(&buf[0]), length);
    std::string res(reinterpret_cast<char*>(&buf[0]));
    return res;
}

std::string fileread::readLString(std::ifstream& is)
{
    std::uint32_t length = fileread::read4ByteMsb(is);
    return fileread::readString(is, length);
}

float fileread::readFloatMsb(std::ifstream& is)
{
    float res = 0;
    void* res_v = &res;
    is.read(static_cast<char*>(res_v), 4);
    res = utils::lsbOfFloat(res);
    return res;
}

float fileread::readFloatLsb(std::ifstream& is)
{
    float res = 0;
    void* res_v = &res;
    is.read(reinterpret_cast<char*>(res_v), 4);
    return res;
}

void fileread::skipBytes(std::ifstream& is, std::uint32_t count)
{
    for (std::uint32_t i = 0; i < count / 4; i++)
    {
        fileread::read4ByteMsb(is);
    }

    for (std::uint32_t i = 0; i < count % 4; i++)
    {
        fileread::read1Byte(is);
    }
}

bool fileread::areFilesEqual(std::filesystem::path path1,
    std::filesystem::path path2)
{
    if (path1 == path2)
    {
        return true;
    }

    std::ifstream file1(path1);
    std::ifstream file2(path2);

    if (!file1 || !file2)
    {
        return false;
    }

    char c1;
    char c2;
    bool eof1;
    bool eof2;

    do
    {
        file1.read(&c1, 1);
        file2.read(&c2, 1);
    } while (!(eof1 = file1.eof()) && !(eof2 = file2.eof()) && c1 == c2);

    return file1.eof() && file2.eof() && c1 == c2;
}