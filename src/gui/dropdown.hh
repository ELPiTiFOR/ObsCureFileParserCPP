#pragma once

#include <string>
#include <vector>

#include "component.hh"

#define DROPDOWN_HEIGHT 25

namespace gui
{
    class Dropdown : public Component
    {
    public:
        Dropdown(float width);
        Dropdown(const Dropdown& other);
        int getActiveOption();
        bool getIsOpen();
        void setActiveOption(int option);
        void addOption(const std::string& option);
        void display() override;
    private:
        std::vector<std::string> options_;
        std::string options_string_;
        int active_option_;
        bool is_open_;
    };
}