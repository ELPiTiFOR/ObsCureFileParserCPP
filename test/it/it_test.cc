#include "it/it_test.hh"

#include <cstdint>

#include "fileread/fileread_test.hh"
#include "test.hh"

namespace ittest
{
    bool testSingle()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("single.it");

        ItFile* it_file = ItFile::makeFile(my_path);

        if (it_file->getItems().size() != 1)
        {
            return 1;
        }

        const ItItem& actual = it_file->getItems().front();
        const ItItem& expected = ItItem(0x25f, 0xaabbcc, 0, 1, oci::DiffMode(0x4));
        if (actual != expected)
        {
            return 1;
        }

        delete it_file;
        return 0;
    }

    bool testMulti()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("multi.it");

        ItFile* it_file = ItFile::makeFile(my_path);

        if (it_file->getItems().size() != 3)
        {
            return 1;
        }

        // const ItItem& actual = it_file->getItems().front();
        // const ItItem& expected = ItItem(0x25f, 0xaabbcc, 0, 1, oci::DiffMode(0x4));
        ItFile it_file_expected;
        it_file_expected.getItems().push_back(ItItem(0x25f, 0xaabbcc, 0, 1, oci::DiffMode(0x4)));
        it_file_expected.getItems().push_back(ItItem(0x130, 0x020402, 0, 2, oci::DiffMode(0x7)));
        it_file_expected.getItems().push_back(ItItem(0x2f7, 0x020403, 0x224455, 1, oci::DiffMode(0x7)));

        bool are_equal = *it_file == it_file_expected;
        delete it_file;
        return !are_equal;
    }

    bool testEqualSingle()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("single.it");

        ItFile* it_file1 = ItFile::makeFile(my_path);
        ItFile* it_file2 = ItFile::makeFile(my_path);

        if (*it_file1 != *it_file2)
        {
            return 1;
        }

        delete it_file1;
        delete it_file2;
        return 0;
    }

    bool testEqualMulti()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("multi.it");

        ItFile* it_file1 = ItFile::makeFile(my_path);
        ItFile* it_file2 = ItFile::makeFile(my_path);

        if (*it_file1 != *it_file2)
        {
            return 1;
        }

        delete it_file1;
        delete it_file2;
        return 0;
    }

    bool testUnequal()
    {
        std::filesystem::path single_path = std::filesystem::current_path();
        single_path.append("test");
        single_path.append("resources");

        std::filesystem::path multi_path = single_path;
        multi_path.append("multi.it");
        single_path.append("single.it");

        ItFile* it_single = ItFile::makeFile(single_path);
        ItFile* it_multi = ItFile::makeFile(multi_path);

        if (*it_single == *it_multi)
        {
            return 1;
        }

        delete it_multi;
        delete it_single;
        return 0;
    }

    bool testUnequalSameSize()
    {
        ItFile it_file1;
        ItFile it_file2;

        it_file1.getItems().push_back(ItItem(0x25f, 0xaabbcc, 0, 1, oci::DiffMode(0x4)));
        it_file2.getItems().push_back(ItItem(0x25a, 0xccbbaa, 0, 1, oci::DiffMode(0x7)));

        if (it_file1 == it_file2)
        {
            return 1;
        }

        return 0;
    }

    bool testInvalid()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("invalid.it");

        ItFile* it_file = ItFile::makeFile(my_path);
        if (it_file)
        {
            delete it_file;
            return 1;
        }

        return 0;
    }

    bool testGetters()
    {
        ItItem my_item(0x130, 0x112233, 0x445566, 2, oci::DiffMode(0x8));

        if (my_item.getItemType() != 0x130)
        {
            return 1;
        }

        if (my_item.getItemUid() != 0x112233)
        {
            return 1;
        }

        if (my_item.getExtraInfo() != 0x445566)
        {
            return 1;
        }

        if (my_item.getMultiplier() != 2)
        {
            return 1;
        }

        if (my_item.getDiffMode() != oci::DiffMode(0x8))
        {
            return 1;
        }

        return 0;
    }

    bool testSetters()
    {
        ItItem actual(0, 0, 0, 0, oci::DiffMode(0));
        ItItem expected(0x130, 0x112233, 0x445566, 2, oci::DiffMode(0x8));

        actual.setItemType(0x130);
        actual.setItemUid(0x112233);
        actual.setExtraInfo(0x445566);
        actual.setMultiplier(2);
        actual.setDiffMode(oci::DiffMode(0x8));

        if (actual != expected)
        {
            return 1;
        }

        return 0;
    }

    bool testSerializeItFile(const std::string& filename)
    {
        std::filesystem::path og_path = std::filesystem::current_path();
        og_path.append("test");
        og_path.append("resources");
        std::filesystem::path new_path = og_path;
        og_path.append(filename);

        std::string new_filename = filename;
        new_filename.insert(new_filename.find("."), "_new");

        new_path.append(new_filename);

        ItFile* it_file = ItFile::makeFile(og_path);
        it_file->serialize(new_path);

        bool are_equal;
        if ((are_equal = fileread::areFilesEqual(og_path, new_path)))
        {
            std::filesystem::remove(new_path);
        }

        delete it_file;
        return !are_equal;
    }

    bool testSerializeSingle()
    {
        return ittest::testSerializeItFile("single.it");
    }

    bool testSerializeMulti()
    {
        return ittest::testSerializeItFile("multi.it");
    }
}

bool ittest::test()
{
    RUN_TEST(ittest::testSingle)
    RUN_TEST(ittest::testMulti)
    RUN_TEST(ittest::testEqualSingle)
    RUN_TEST(ittest::testEqualMulti)
    RUN_TEST(ittest::testUnequal)
    RUN_TEST(ittest::testUnequalSameSize)
    RUN_TEST(ittest::testInvalid)
    RUN_TEST(ittest::testGetters)
    RUN_TEST(ittest::testSetters)
    RUN_TEST(ittest::testSerializeSingle)
    RUN_TEST(ittest::testSerializeMulti)

    return 0;
}