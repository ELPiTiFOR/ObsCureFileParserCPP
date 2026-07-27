#include "fileread_test.hh"

#include <cstdint>

#include "test.hh"

// Every test returns 0 if it passed and 1 if it failed

namespace filereadtest
{
    bool testEqualFiles(const std::string& filename1,
        const std::string& filename2)
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        std::filesystem::path my_path2 = my_path;
        my_path.append(filename1);
        my_path2.append(filename2);

        return !fileread::areFilesEqual(my_path, my_path2);
    }

    bool testEqualText()
    {
        return filereadtest::testEqualFiles("helloWorld.txt", "helloWorld2.txt");
    }

    bool testEqualEmpty()
    {
        return filereadtest::testEqualFiles("empty.txt", "empty2.txt");
    }

    bool testEqualBinary()
    {
        return filereadtest::testEqualFiles("single.it", "single2.it");
    }

    bool testUnequal()
    {
        // testEqualFiles returns 0 if both files are equal
        // we want it to return 1, in which case this test passes (returns 0)
        return !filereadtest::testEqualFiles("helloWorld.txt", "single.it");
    }

    bool testNonExistent()
    {
        return !filereadtest::testEqualFiles("doesnotexist.txt",
            "doesnotexisteither.txt");
    }

    bool test()
    {
        RUN_TEST(filereadtest::testEqualText)
        RUN_TEST(filereadtest::testEqualEmpty)
        RUN_TEST(filereadtest::testEqualBinary)
        RUN_TEST(filereadtest::testUnequal)
        RUN_TEST(filereadtest::testNonExistent)
        return 0;
    }
}