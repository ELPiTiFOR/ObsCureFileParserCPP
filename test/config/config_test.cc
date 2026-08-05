#include "config/config_test.hh"

#include <filesystem>

#include "test.hh"

namespace configtest
{
    bool testSingle()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("simple.config");
        Config my_config(my_path);
        if (my_config.getValue("IT_DEFAULT_PATH") != "E:\\User\\Some folder")
        {
            return 1;
        }

        return 0;
    }

    bool testMulti()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("multi.config");
        Config my_config(my_path);
        if (my_config.getValue("IT_DEFAULT_PATH") != "E:\\User\\Some folder")
        {
            return 1;
        }

        if (my_config.getValue("SAV_DEFAULT_PATH") != "E:\\User\\Some other folder")
        {
            return 1;
        }

        return 0;
    }
}

bool configtest::test()
{
    RUN_TEST(configtest::testSingle)
    RUN_TEST(configtest::testMulti)

    return 0;
}