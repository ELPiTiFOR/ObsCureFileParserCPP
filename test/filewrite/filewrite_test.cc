#include "filewrite_test.hh"

#include <cstdint>
#include <filesystem>

#include "fileread/fileread_test.hh"
#include "test.hh"

// Every test returns 0 if it passed and 1 if it failed

namespace filewritetest
{

    bool testCopyFile()
    {
        std::filesystem::path path = std::filesystem::current_path();
        path.append("test");
        path.append("resources");
        std::filesystem::path path_copy = path;
        path.append("helloWorld.txt");
        path_copy.append("helloWorldCopy.txt");

        filewrite::copyFile(path, path_copy);
        bool are_equal = fileread::areFilesEqual(path, path_copy);
        
        std::filesystem::remove(path_copy);

        return !are_equal;
    }

    bool test()
    {
        RUN_TEST(filewritetest::testCopyFile)
        return 0;
    }
}