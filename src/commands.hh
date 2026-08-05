#pragma once

#include <filesystem>

namespace commands
{
    void parseItFile(std::filesystem::path path);
    void correctCrc32(std::filesystem::path path);
}