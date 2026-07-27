#include <iostream>

#include "diff_mode/diff_mode_test.hh"
#include "fileread/fileread_test.hh"
#include "it/it_test.hh"

int main()
{
    filereadtest::test();
    ittest::test();
    diffmodetest::test();

    return 0;
}