#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class PpmPixel
{
public:
    PpmPixel(std::uint32_t red, std::uint32_t green, std::uint32_t blue);
    std::uint32_t getRed() const;
    std::uint32_t getGreen() const;
    std::uint32_t getBlue() const;
private:
    std::uint32_t red_;
    std::uint32_t green_;
    std::uint32_t blue_;
};

class PpmFile
{
public:
    PpmFile();
    PpmFile(std::uint32_t width, std::uint32_t height, std::uint32_t max_value);
    static PpmFile* makeFile(std::filesystem::path path);
    void serialize(std::filesystem::path path);
    static void skipCommentaries(std::ifstream& file, std::string& line);

    std::uint32_t getWidth() const;
    std::uint32_t getHeight() const;
    std::uint32_t getMaxValue() const;
    std::vector<PpmPixel>& getPixels();

    void setWidth(std::uint32_t width);
    void setHeight(std::uint32_t height);
    void setMaxValue(std::uint32_t max_value);
private:
    std::uint32_t width_;
    std::uint32_t height_;
    std::uint32_t max_value_;
    std::vector<PpmPixel> pixels_;
};