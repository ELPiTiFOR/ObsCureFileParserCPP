#include "diff_mode/diff_mode_test.hh"

#include "test.hh"

namespace diffmodetest
{
    bool testSetFalseSimple()
    {
        oci::DiffMode diff(0x7);
        diff.setHard(false);
        return !(!diff.getHard() && diff.getNormal() && diff.getEasy()
            && !diff.getSpecial());
    }

    bool testSetTrueSimple()
    {
        oci::DiffMode diff(0x3);
        diff.setHard(true);
        return !(diff.getHard() && diff.getNormal() && diff.getEasy()
            && !diff.getSpecial());
    }
}

bool diffmodetest::test()
{
    RUN_TEST(diffmodetest::testSetFalseSimple)
    RUN_TEST(diffmodetest::testSetTrueSimple)
    return 0;
}