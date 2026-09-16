#include "hoe/hoe_test.hh"

#include <bit>
#include <cstdint>

#include "fileread/fileread_test.hh"
#include "test.hh"

namespace hoetest
{
    // The HoeFile class does not define it as a "header", but I wanted to call
    // the function in a way I could easily recognize what it does
    bool testCollisionsHeaderB008()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("b008.hoe");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;

        HoeCollisions* collisions = hoe_file->getCollisions();
        if (!collisions)
        {
            return 1;
        }

        if (collisions->getLength() != 0xaa44)
        {
            return 1;
        }

        if (collisions->getUkInt1() != 3)
        {
            return 1;
        }

        if (collisions->getRoomId() != "b008")
        {
            return 1;
        }

        if (collisions->getUkInt2() != 0x69)
        {
            return 1;
        }

        if (collisions->getUkFloat1() != 20.0)
        {
            return 1;
        }

        if (collisions->getUkFloat2() != 20.0)
        {
            return 1;
        }

        if (collisions->getUkFloat3() != 100.0)
        {
            return 1;
        }

        if (collisions->getMaps().size() != 1)
        {
            return 1;
        }

        delete hoe_file;
        return 0;
    }

    bool testCollisionsMapB008()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("b008.hoe");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;

        HoeCollisions* collisions = hoe_file->getCollisions();
        HoeCollisionsMap& map = collisions->getMaps().at(0);

        if (map.getIndex() != 0)
        {
            return 1;
        }

        if (map.getCells().size() != 0xA95)
        {
            return 1;
        }

        if (map.getWidth() != 43)
        {
            return 1;
        }

        if (map.getHeight() != 63)
        {
            return 1;
        }

        delete hoe_file;
        return 0;
    }

    bool testCollisionsFinalB008()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("b008.hoe");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;

        HoeCollisions* collisions = hoe_file->getCollisions();

        if (collisions->getWidth() != 43)
        {
            return 1;
        }

        if (collisions->getHeight() != 63)
        {
            return 1;
        }

        if (collisions->getUkFloat4() != -430.614501953125)
        {
            return 1;
        }

        std::uint32_t float_5 = std::bit_cast<std::uint32_t>(
            collisions->getUkFloat5()
        );
        if (float_5 != 0xC41D77A9)
        {
            return 1;
        }

        if (collisions->getUkFloat6() != 2.0)
        {
            return 1;
        }

        std::uint32_t float_7 = std::bit_cast<std::uint32_t>(
            collisions->getUkFloat7()
        );
        if (float_7 != 0x43D6B158)
        {
            return 1;
        }

        std::uint32_t float_8 = std::bit_cast<std::uint32_t>(
            collisions->getUkFloat8()
        );
        if (float_8 != 0x441D8857)
        {
            return 1;
        }

        if (collisions->getUkFloat9() != 2.0)
        {
            return 1;
        }

        if (collisions->getUkInt3() != 0)
        {
            return 1;
        }

        if (collisions->getUkInt4() != 2)
        {
            return 1;
        }

        if (collisions->getUkInt5() != 0)
        {
            return 1;
        }

        if (collisions->getUkInt6() != 0)
        {
            return 1;
        }

        if (collisions->getUkInt7() != 2)
        {
            return 1;
        }

        if (collisions->getUkInt8() != 0)
        {
            return 1;
        }

        if (collisions->getUkInt9() != 0)
        {
            return 1;
        }

        if (collisions->getPostCollisions().size() != 0)
        {
            return 1;
        }

        delete hoe_file;
        return 0;
    }

    // The HoeScript class does not define it as a "header", but I wanted to
    // call the function in a way I could easily recognize what it does
    bool testEventCinHeaderB008()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("b008.hoe");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;
        HoeEvent* event_cin = hoe_file->getEvent("event_cin");

        if (!event_cin)
        {
            return 1;
        }

        if (event_cin->getMagicNumber() != 4.0)
        {
            return 1;
        }

        if (event_cin->getUkInt1() != 0)
        {
            return 1;
        }

        if (event_cin->getUkInt2() != 2) return 1;
        if (event_cin->getUkInt3() != 1) return 1;
        if (event_cin->getUkInts().size() != 0) return 1;
        if (event_cin->getLStrings().size() != 2) return 1;
        if (event_cin->getLStrings().at(0) != "SaveState") return 1;
        if (event_cin->getLStrings().at(1) != "VideoInProgress") return 1;
        if (event_cin->getHoeConstants().size() != 7) return 1;
        if (event_cin->getHoeConstants().at(0).getIntValue() != 0) return 1;
        if (event_cin->getHoeConstants().at(1).getIntValue() != 1) return 1;
        if (event_cin->getHoeConstants().at(2).getIntValue() != 5) return 1;
        if (event_cin->getM1().size() != 2) return 1;

        return 0;
    }

    bool testEventCinScriptB008()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("b008_event_cin.hoe");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;

        HoeEvent* event_cin = hoe_file->getEvent("event_cin");

        if (!event_cin)
        {
            return 1;
        }

        HoeScript* script = event_cin->getScript();
        if (script->getMask() != nullptr) return 1;

        /* BLOCKS */

        if (script->getBlocks().size() != 4) return 1;

        /* TM_GetEvent(0) */
        HoeBlock* block = script->getBlocks().at(0);
        HoeBoolean* tm_get_event_block = dynamic_cast<HoeBoolean*>(block);
        if (!tm_get_event_block) return 1;
        HoeExpression* tm_get_event_expression =
            tm_get_event_block->getExpression();
        if (!tm_get_event_expression) return 1;
        HoeValexpr* tm_get_event_valexpr = dynamic_cast<HoeValexpr*>(
            tm_get_event_expression
        );
        if (!tm_get_event_valexpr) return 1;
        HoeValue* tm_get_event_value = tm_get_event_valexpr->getValue();
        if (tm_get_event_value == nullptr) return 1;
        HoeFunctionCall* tm_get_event_funcall = dynamic_cast<HoeFunctionCall*>(
            tm_get_event_value
        );
        if (!tm_get_event_funcall) return 1;
        // if (tm_get_event_funcall->getName() != "TM_GetEvent") return 1;

        block = script->getBlocks().at(1);
        if (!static_cast<HoeAssign*>(block)) return 1;

        block = script->getBlocks().at(2);
        if (!static_cast<HoeAssign*>(block)) return 1;

        block = script->getBlocks().at(3);
        if (!static_cast<HoeBoolean*>(block)) return 1;

        /* IF THENS */
        if (script->getIfThens().size() != 3) return 1;

        HoeIfThen* if_then = script->getIfThens().at(0);
        if (!static_cast<HoeIfThenBlocks*>(if_then)) return 1;

        if_then = script->getIfThens().at(1);
        if (!static_cast<HoeIfThenBlocks*>(if_then)) return 1;

        if_then = script->getIfThens().at(2);
        if (!static_cast<HoeIfThenIf*>(if_then)) return 1;

        return 0;
    }
    bool testEventCinPrintScriptB008()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("b008_event_cin.hoe");

        std::filesystem::path output_path = std::filesystem::current_path();
        output_path.append("test");
        output_path.append("results");
        output_path.append("b008_event_cin_script.txt");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;

        HoeEvent* event_cin = hoe_file->getEvent("event_cin");

        std::ofstream file(output_path, std::ios::binary);
        file << *(event_cin->getScript());
        file.close();
        return 0;
    }
    bool testTutorialPrintScriptB008()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("b008.hoe");

        std::filesystem::path output_path = std::filesystem::current_path();
        output_path.append("test");
        output_path.append("results");
        output_path.append("b008_tutorial_script.txt");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;

        HoeEvent* event_cin = hoe_file->getEvent("tutorial");

        std::ofstream file(output_path, std::ios::binary);
        file << *(event_cin->getScript());
        file.close();
        return 0;
    }

    bool testPrintRoom(std::string room_id)
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append(room_id + ".hoe");

        std::filesystem::path output_path = std::filesystem::current_path();
        output_path.append("test");
        output_path.append("results");
        output_path.append(room_id + ".hoe.txt");

        HoeFile* hoe_file = HoeFile::makeFile(my_path);
        if (!hoe_file) return 1;

        std::ofstream file(output_path, std::ios::binary);
        file << *hoe_file;
        file.close();
        return 0;
    }

    bool testPrintB008()
    {
        return testPrintRoom("b008");
    }

    bool testPrintB000()
    {
        return testPrintRoom("b000");
    }

    bool testPrintA003()
    {
        return testPrintRoom("a003");
    }

    bool testPrintE103()
    {
        return testPrintRoom("e103");
    }
}

bool hoetest::test()
{
    RUN_TEST(hoetest::testCollisionsHeaderB008)
    RUN_TEST(hoetest::testCollisionsMapB008)
    RUN_TEST(hoetest::testCollisionsFinalB008)
    RUN_TEST(hoetest::testEventCinHeaderB008)
    RUN_TEST(hoetest::testEventCinScriptB008)
    RUN_TEST(hoetest::testEventCinPrintScriptB008)
    RUN_TEST(hoetest::testTutorialPrintScriptB008)
    RUN_TEST(hoetest::testPrintB008)
    RUN_TEST(hoetest::testPrintB000)
    RUN_TEST(hoetest::testPrintA003)
    RUN_TEST(hoetest::testPrintE103)
    // TODO: test some cells in the collisions map

    return 0;
}