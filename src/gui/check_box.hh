#pragma once

#include <string>

#include "gui/component.hh"

#define CHECK_BOX_LABEL_HEIGHT 15

namespace gui
{
    // TODO: should I add a pointer to a bool, which would be the boolean to be
    // modified with each modification of this GUI component? Instead of having
    // a callback function that modifies the value
    //  |
    //  +--> this could also be done for other components like the TextBox
    class CheckBox : public Component
    {
    public:
        CheckBox(bool is_checked, const std::string& label, float width);
        CheckBox(const CheckBox& other);
        bool getIsChecked();
        void setIsChecked(bool is_checked);
        void display() override;
    private:
        bool is_checked_;
        std::string label_;
    };
}