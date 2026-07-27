#pragma once

#include "file_search_bar.hh"

#include <cstring>
#include <iostream>

#include "raygui.h"

#include "it/it_file.hh"

namespace gui
{
    template <FileFormatClass T>
    FileSearchBar<T>::FileSearchBar(float x, float y, const std::string& file_path)
        : Component(x, y,
            FILE_SEARCH_BAR_TEXT_BOX_WIDTH
                + (5 + FILE_SEARCH_BAR_BUTTON_WIDTH) * 2,
            FILE_SEARCH_BAR_TEXT_BOX_HEIGHT)
        , file_(nullptr)
    {
        Rectangle text_box_rect =
        {
            x_,
            y_,
            FILE_SEARCH_BAR_TEXT_BOX_WIDTH,
            FILE_SEARCH_BAR_TEXT_BOX_HEIGHT
        };

        text_box_ = gui::TextBox(&text_box_rect, file_path);
    }

    template <FileFormatClass T>
    char* FileSearchBar<T>::getFilePath()
    {
        return text_box_.getText();
    }

    template <FileFormatClass T>
    bool FileSearchBar<T>::getIsTextBoxFocused() const
    {
        return text_box_.getIsFocused();
    }

    template <FileFormatClass T>
    T* FileSearchBar<T>::getFile()
    {
        return file_;
    }

    template <FileFormatClass T>
    void FileSearchBar<T>::setFile(T* file)
    {
        file_ = file;
    }

    template <FileFormatClass T>
    void FileSearchBar<T>::display()
    {
        text_box_.setX(x_);
        text_box_.setY(y_);
        text_box_.display();

        Rectangle button_rect =
        {
            x_ + FILE_SEARCH_BAR_TEXT_BOX_WIDTH + 5,
            y_,
            FILE_SEARCH_BAR_BUTTON_WIDTH,
            FILE_SEARCH_BAR_BUTTON_HEIGHT
        };

        if (GuiButton(button_rect, "Load"))
        {
            file_ = T::makeFile(this->getFilePath());
            if (file_)
            {
                // std::cout << *file_ << std::endl;
            }
        }

        button_rect.x += 5 + FILE_SEARCH_BAR_BUTTON_WIDTH;
        if (GuiButton(button_rect, "Save"))
        {
            if (file_)
            {
                file_->serialize(text_box_.getText());
            }
        }
    }
}