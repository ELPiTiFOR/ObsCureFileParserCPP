#pragma once

#include "fileread/fileread.hh"

namespace filereadtest
{
    bool testEqualFiles(const std::string& filename1,
        const std::string& filename2);
    bool test();
}