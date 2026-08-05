#include "sav/sav_test.hh"

#include <cstdint>
#include <string>

#include "fileread/fileread_test.hh"
#include "filewrite/filewrite.hh"
#include "test.hh"

namespace savtest
{
    bool testHelloWorld()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        std::filesystem::path my_path_nocrc = my_path;
        std::filesystem::path my_path_nocrc_copy = my_path;
        my_path.append("helloWorld.sav");
        my_path_nocrc.append("helloWorld_nocrc.sav");
        my_path_nocrc_copy.append("helloWorld_nocrc_copy.sav");

        filewrite::copyFile(my_path_nocrc, my_path_nocrc_copy);
        SavFile::correctCrc32(my_path_nocrc_copy);

        bool res = fileread::areFilesEqual(my_path, my_path_nocrc_copy);
        std::filesystem::remove(my_path_nocrc_copy);

        return !res;
    }

    bool testDanKennyEscapeHeaderParse()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("dan_kenny_escape.sav");

        SavFile* sav_file = SavFile::makeFile(my_path);

        if (!sav_file)
        {
            return 1;
        }

        SavHeader& header = sav_file->getHeader();
        if (header.getIndex() != 2)
        {
            return 1;
        }
        
        if (header.getRoom() != 0x87)
        {
            return 1;
        }

        if (header.getPlayTime() != 113025)
        {
            return 1;
        }

        if (header.getTimesSaved() != 1)
        {
            return 1;
        }

        if (header.getUk1() != 515)
        {
            return 1;
        }

        if (header.getDiffMode().getFlags() != 0x4)
        {
            return 1;
        }

        if (header.getUk2() != 0x64)
        {
            return 1;
        }

        if (header.getItemsCharactersLength() != 0x844)
        {
            return 1;
        }

        delete sav_file;
        return 0;
    }
    bool testPreDormitoryItemsParse()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("pre_dormitory.sav");

        SavFile* sav_file = SavFile::makeFile(my_path);

        if (!sav_file)
        {
            return 1;
        }

        SavItems& items = sav_file->getItems();
        if (items.getLength() != 0x231)
        {
            return 1;
        }

        if (items.getInventoryCapacity() != 0x3e)
        {
            return 1;
        }

        // first item
        if (items.getItems().at(0).item.uid != 0x03368a)
        {
            return 1;
        }

        if (items.getItems().at(0).item.quantity != 1)
        {
            return 1;
        }

        if (items.getItems().at(0).item.extra_info != 0x020811)
        {
            return 1;
        }

        // second item
        if (items.getItems().at(1).item.uid != 0x020501)
        {
            return 1;
        }

        if (items.getItems().at(1).item.quantity != 1)
        {
            return 1;
        }

        if (items.getItems().at(1).item.extra_info != 0)
        {
            return 1;
        }

        // third item
        if (items.getItems().at(2).item.uid != 0x023301)
        {
            return 1;
        }

        if (items.getItems().at(2).item.quantity != 1)
        {
            return 1;
        }

        if (items.getItems().at(2).item.extra_info != 0)
        {
            return 1;
        }

        // those are not all items, but that is enough

        delete sav_file;
        return 0;
    }

    bool testSerialize(const std::string& filename)
    {
        // the filename has no extension
        std::filesystem::path path = std::filesystem::current_path();
        path.append("test");
        path.append("resources");
        std::filesystem::path path_copy = path;
        path.append(filename + ".sav");
        path_copy.append(filename + "_copy.sav");

        SavFile* sav_file = SavFile::makeFile(path);
        sav_file->serialize(path_copy);

        bool areEqual = fileread::areFilesEqual(path, path_copy);
        if (areEqual)
            std::filesystem::remove(path_copy);

        return !areEqual;
    }
    bool testDanKennyEscapeHeaderSerialize()
    {
        // std::filesystem::path path = std::filesystem::current_path();
        // path.append("test");
        // path.append("resources");
        // std::filesystem::path path_copy = path;
        // path.append("dan_kenny_escape.sav");
        // path_copy.append("dan_kenny_escape_copy.sav");

        // SavFile* sav_file = SavFile::makeFile(path);
        // sav_file->serialize(path_copy);

        // bool areEqual = fileread::areFilesEqual(path, path_copy);

        return testSerialize("dan_kenny_escape");
    }

    bool testPreDormitorySerialize()
    {
        return testSerialize("pre_dormitory");
    }

    bool testPreDormitoryPushItem()
    {
        std::filesystem::path path = std::filesystem::current_path();
        path.append("test");
        path.append("resources");
        std::filesystem::path path_disc = path;
        std::filesystem::path path_disc_copy = path;
        path.append("pre_dormitory.sav");
        path_disc.append("pre_dormitory_disc.sav");
        path_disc_copy.append("pre_dormitory_disc_copy.sav");

        SavFile* sav_file = SavFile::makeFile(path);
        if (!sav_file)
        {
            return 1;
        }

        sav_file->getItems().pushItem(SavInventoryElement(
            InventoryElementType::ITEM,
            SavItem(0x020401, 0xff, 0)
        ));

        sav_file->serialize(path_disc_copy);

        bool areEqual = fileread::areFilesEqual(path_disc, path_disc_copy);

        if (areEqual)
            std::filesystem::remove(path_disc_copy);

        delete sav_file;
        return !areEqual;
    }
}

bool savtest::test()
{
    RUN_TEST(savtest::testHelloWorld)
    RUN_TEST(savtest::testDanKennyEscapeHeaderParse)
    RUN_TEST(savtest::testPreDormitoryItemsParse)
    RUN_TEST(savtest::testDanKennyEscapeHeaderSerialize)
    RUN_TEST(savtest::testPreDormitorySerialize)
    RUN_TEST(savtest::testPreDormitoryPushItem)

    return 0;
}