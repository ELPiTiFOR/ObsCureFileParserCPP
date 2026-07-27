#include "filewrite.hh"

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