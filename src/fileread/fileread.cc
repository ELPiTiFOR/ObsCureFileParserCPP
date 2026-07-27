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