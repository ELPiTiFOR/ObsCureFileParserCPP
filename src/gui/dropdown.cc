#include "dropdown.hh"

#include "raygui.h"

namespace gui
{
    Dropdown::Dropdown(float width)
        : Component(0, 0, width, DROPDOWN_HEIGHT)
        , options_string_("")
        , active_option_(0)
        , is_open_(false)
    {}

    Dropdown::Dropdown(const Dropdown& other)
        : Component(other)
        , options_string_(other.options_string_)
        , active_option_(other.active_option_)
        , is_open_(other.is_open_)
    {
        for (const std::string& str : other.options_)
        {
            addOption(str);
        }
    }

    int Dropdown::getActiveOption()
    {
        return active_option_;
    }

    bool Dropdown::getIsOpen()
    {
        return is_open_;
    }

    void Dropdown::setActiveOption(int option)
    {
        active_option_ = option;
    }

    void Dropdown::addOption(const std::string& option)
    {
        options_.push_back(option);
        if (options_.size() == 1)
        {
            options_string_ = option;
            return;
        }

        options_string_ += ";" + option;
    }

    void Dropdown::display()
    {
        Rectangle rect =
        {
            x_,
            y_,
            width_,
            height_
        };

        if (GuiDropdownBox(rect, options_string_.data(), &active_option_, is_open_))
        {
            is_open_ = !is_open_;
        }
    }
}