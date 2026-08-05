#pragma once

#include <filesystem>
#include <iostream>
#include <string>

#include "gui/text_box.hh"

#define FILE_SEARCH_BAR_TEXT_BOX_WIDTH 400
#define FILE_SEARCH_BAR_TEXT_BOX_HEIGHT 25
#define FILE_SEARCH_BAR_BUTTON_WIDTH 70
#define FILE_SEARCH_BAR_BUTTON_HEIGHT 25

namespace gui
{
    // This concept ensures the given T type has the static makeFile method
    // and the serialize method
    template <typename T>
    concept FileFormatClass = requires(T f)
    {
        { T::makeFile(std::filesystem::current_path()) };
        { f.serialize(std::filesystem::current_path()) };
    };

    template <FileFormatClass T>
    class FileSearchBar : public Component
    {
    public:
        FileSearchBar(float x, float y, const std::string& file_path);
        char* getFilePath();
        void display() override;
        bool getIsTextBoxFocused() const;
        T* getFile();
        void setFile(T* file);
    private:
        gui::TextBox text_box_;
        T* file_;
    };
} // namespace gui

#include "file_search_bar.hxx"