#include "ppm/ppm_test.hh"

#include <bit>
#include <cstdint>

#include "config/config.hh"
#include "fileread/fileread_test.hh"
#include "test.hh"

namespace ppmtest
{
    bool testSimpleParse()
    {
        std::filesystem::path my_path = std::filesystem::current_path();
        my_path.append("test");
        my_path.append("resources");
        my_path.append("simple_image_to_parse.ppm");

        PpmFile* ppm_file = PpmFile::makeFile(my_path);
        if (!ppm_file) return 1;

        if (ppm_file->getWidth() != 5) return 1;
        if (ppm_file->getHeight() != 5) return 1;
        if (ppm_file->getMaxValue() != 255) return 1;
        if (ppm_file->getPixels().at(0).getRed() != 0) return 1;
        if (ppm_file->getPixels().at(0).getGreen() != 0) return 1;
        if (ppm_file->getPixels().at(0).getBlue() != 255) return 1;
        if (ppm_file->getPixels().at(1).getRed() != 255) return 1;
        if (ppm_file->getPixels().at(1).getGreen() != 0) return 1;
        if (ppm_file->getPixels().at(1).getBlue() != 0) return 1;
        if (ppm_file->getPixels().at(24).getRed() != 0) return 1;
        if (ppm_file->getPixels().at(24).getGreen() != 0) return 1;
        if (ppm_file->getPixels().at(24).getBlue() != 0) return 1;

        delete ppm_file;
        return 0;
    }

    bool testSimpleSerialize()
    {
        PpmFile ppm_file(3, 1, 255);
        ppm_file.getPixels().push_back(PpmPixel(255, 0, 0));
        ppm_file.getPixels().push_back(PpmPixel(0, 255, 0));
        ppm_file.getPixels().push_back(PpmPixel(0, 0, 255));

        std::filesystem::path output_path = std::filesystem::current_path();
        output_path.append("test");
        output_path.append("results");
        output_path.append("serialized_image.ppm");
        std::filesystem::path expected_path = std::filesystem::current_path();
        expected_path.append("test");
        expected_path.append("resources");
        expected_path.append("simple_serialization_expected.ppm");

        ppm_file.serialize(output_path);

        return filereadtest::testEqualFiles(output_path.string(),
            expected_path.string());
    }
}

bool ppmtest::test()
{
    RUN_TEST(ppmtest::testSimpleParse)
    RUN_TEST(ppmtest::testSimpleSerialize)
    return 0;
}