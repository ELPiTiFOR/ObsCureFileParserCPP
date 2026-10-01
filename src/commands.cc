#include "commands.hh"

#include <filesystem>

#include "it/it_file.hh"
#include "hoe/hoe_file.hh"
#include "oci/room.hh"
#include "sav/sav_file.hh"

namespace commands
{
    void parseItFile(fs::path path)
    {
        ItFile* it_file = ItFile::makeFile(path);
        std::cout << *it_file;
        delete it_file;
    }

    void correctCrc32(fs::path path)
    {
        SavFile::correctCrc32(path);
    }

    void extractCollisions(fs::path hoe_path, fs::path output_path)
    {
        HoeFile* hoe_file = HoeFile::makeFile(hoe_path);
        if (!hoe_file) return;

        if (hoe_file->extractCollisionsMaps(output_path))
        {
            std::cerr << "ERROR: hoe_file.extractCollisionsMap()" << std::endl;
        }

        delete hoe_file;
    }

    void modifyCollisions(fs::path hoe_path, fs::path ppm_path, size_t index,
        fs::path output_path)
    {
        HoeFile* hoe_file = HoeFile::makeFile(hoe_path);
        if (!hoe_file) return;

        if (hoe_file->modifyCollisionsMap(ppm_path, index))
        {
            std::cerr << "ERROR: hoe_file.modifyCollisionsMap()" << std::endl;
        }

        hoe_file->serialize(output_path);
        delete hoe_file;
    }

    void test()
    {
    }
}