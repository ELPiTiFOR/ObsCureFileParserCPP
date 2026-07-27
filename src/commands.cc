#include "commands.hh"

#include <filesystem>

#include "it/it_file.hh"

namespace commands
{
    void parseItFile(std::filesystem::path path)
    {
        ItFile* it_file = ItFile::makeFile(path);
        std::cout << *it_file;
        delete it_file;
    }
}