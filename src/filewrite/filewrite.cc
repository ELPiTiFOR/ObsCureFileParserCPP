#include "filewrite.hh"

#include "fileread/fileread.hh"
#include "utils/utils.hh"

void filewrite::write4ByteMsb(std::ofstream& os, std::uint32_t n)
{
    n = utils::lsbOf(n);
    os.write(reinterpret_cast<char*>(&n), 4);
}

void filewrite::write4ByteLsb(std::ofstream& os, std::uint32_t n)
{
    os.write(reinterpret_cast<char*>(&n), 4);
}

void filewrite::write2ByteMsb(std::ofstream& os, std::uint16_t n)
{
    n = utils::lsbOf(n);
    os.write(reinterpret_cast<char*>(&n), 2);
}

void filewrite::write2ByteLsb(std::ofstream& os, std::uint16_t n)
{
    os.write(reinterpret_cast<char*>(&n), 2);
}

void filewrite::write1Byte(std::ofstream& os, std::uint8_t n)
{
    os.write(reinterpret_cast<char*>(&n), 1);
}

void filewrite::copyFile(std::filesystem::path src_path,
    std::filesystem::path dst_path)
{
    std::ifstream src(src_path);
    if (!src)
    {
        return;
    }

    std::ofstream dst(dst_path);
    if (!dst)
    {
        return;
    }

    while (src)
    {
        std::uint8_t c = fileread::read1Byte(src);
        if (!src)
        {
            break;
        }

        filewrite::write1Byte(dst, c);
    }

    src.close();
    dst.close();
}