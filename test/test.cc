#include <iostream>

#include "config/config_test.hh"
#include "crc32/crc32_test.hh"
#include "diff_mode/diff_mode_test.hh"
#include "fileread/fileread_test.hh"
#include "filewrite/filewrite_test.hh"
#include "hoe/hoe_test.hh"
#include "it/it_test.hh"
#include "oci/room.hh"
#include "sav/sav_test.hh"

int main()
{
    oci::initializeAllRooms();
    filereadtest::test();
    ittest::test();
    diffmodetest::test();
    crc32test::test();
    filewritetest::test();
    savtest::test();
    configtest::test();
    hoetest::test();

    return 0;
}