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
    else
    {
        std::cerr << "Unknown command \"" << std::string(argv[1]) << "\""
            << std::endl;
        return OCFP_UNKNOWN_COMMAND;
    }

    return OCFP_SUCCESS;
}