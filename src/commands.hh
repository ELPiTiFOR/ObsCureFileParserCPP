#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace commands
{
    void parseItFile(std::filesystem::path path);
    void correctCrc32(std::filesystem::path path);
    void extractCollisions(fs::path hoe_path, fs::path output_path);
    void modifyCollisions(fs::path hoe_path, fs::path ppm_path, size_t index,
        fs::path output_path);
    void parseHoe(fs::path hoe_path, fs::path output_path);
    void test();
}