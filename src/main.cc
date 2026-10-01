#include <iostream>

#include "it/it_file.hh"
#include "oci/diff_mode.hh"
#include "oci/item.hh"

#include "commands.hh"

#define OCFP_SUCCESS 0
#define OCFP_FAILURE 1
#define OCFP_MISSING_ARGUMENT 2
#define OCFP_UNKNOWN_COMMAND 3

void printHelp()
{
    std::cout << "usage: ObsCureFileParser --it-parse <path>" << std::endl;
    std::cout << "       ObsCureFileParser --sav-crc <path>" << std::endl;
    std::cout << "       ObsCureFileParser --hoe-parse-to-file <hoe_path>"
        << " <output_file_path>" << std::endl;
    std::cout << "       ObsCureFileParser --hoe-extract-maps <hoe_path>"
        << " <output_folder_path>" << std::endl;
    std::cout << "       ObsCureFileParser --hoe-modify-map <hoe_path>"
        << " <ppm_path> <index>" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printHelp();
        return OCFP_SUCCESS;
    }

    oci::initializeAllItems();
    oci::initializeAllItemUids();
    oci::initializeAllExtraInfos();

    if (std::string(argv[1]) == "--it-parse")
    {
        if (argc < 3)
        {
            std::cerr << "Please provide a path after \"--it-parse\""
                << std::endl;
            return OCFP_MISSING_ARGUMENT;
        }

        commands::parseItFile(std::string(argv[2]));
    }
    else if (std::string(argv[1]) == "--sav-crc")
    {
        if (argc < 3)
        {
            std::cerr << "Please provide a path after \"--sav-crc\""
                << std::endl;
            return OCFP_MISSING_ARGUMENT;
        }

        commands::correctCrc32(std::string(argv[2]));
    }
    else if (std::string(argv[1]) == "--hoe-parse-to-file")
    {
        if (argc < 4)
        {
            std::cerr << "Please provide a path to the HOE file and an output"
                << " file path after \"--hoe-parse-to-file\"" << std::endl;
            return OCFP_MISSING_ARGUMENT;
        }

        commands::parseHoe(std::string(argv[2]), std::string(argv[3]));
    }
    else if (std::string(argv[1]) == "--hoe-extract-maps")
    {
        if (argc < 4)
        {
            std::cerr << "Please provide a path to the HOE file and an output"
                << " folder path after \"--hoe-extract-maps\"" << std::endl;
            return OCFP_MISSING_ARGUMENT;
        }

        commands::extractCollisions(std::string(argv[2]), std::string(argv[3]));
    }
    else if (std::string(argv[1]) == "--hoe-modify-map")
    {
        if (argc < 5)
        {
            std::cerr << "Please provide a path to the HOE file,"
                << " an input file path and an index after \"--hoe-modify-map\""
                << std::endl;
            return OCFP_MISSING_ARGUMENT;
        }

        commands::modifyCollisions(std::string(argv[2]), std::string(argv[3]),
            std::stol(argv[4]), std::string(argv[2])
        );
    }
    else if (std::string(argv[1]) == "test")
    {
        commands::test();
    }
    else
    {
        std::cerr << "Unknown command \"" << std::string(argv[1]) << "\""
            << std::endl;
        return OCFP_UNKNOWN_COMMAND;
    }

    return OCFP_SUCCESS;
}