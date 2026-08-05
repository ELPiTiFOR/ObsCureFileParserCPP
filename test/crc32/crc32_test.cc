#include "crc32/crc32_test.hh"

#include <cstdint>
#include <filesystem>
#include <fstream>

#include "test.hh"

namespace crc32test
{
    bool testHelloWorld()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("helloWorld.txt");

        std::ifstream file(my_path, std::ios::binary);
        std::uint32_t crc = utils::crc32(file);

        if (crc != 0x1C291CA3)
        {
            return 1;
        }

        return 0;
    }
}

bool crc32test::test()
{
    RUN_TEST(crc32test::testHelloWorld)

    return 0;
}