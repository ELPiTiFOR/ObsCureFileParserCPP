#include <iostream>

#include "crc32/crc32_test.hh"
#include "diff_mode/diff_mode_test.hh"
#include "fileread/fileread_test.hh"
#include "filewrite/filewrite_test.hh"
#include "it/it_test.hh"
#include "sav/sav_test.hh"

int main()
{
    filereadtest::test();
    ittest::test();
    diffmodetest::test();
    crc32test::test();
    filewritetest::test();
    savtest::test();

    return 0;
}