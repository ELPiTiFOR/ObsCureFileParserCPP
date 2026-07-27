#include "check_box.hh"

#include "raygui.h"

namespace gui
{
    CheckBox::CheckBox(bool is_checked, const std::string& label, float width)
        : Component(0, 0,
            width,
            width + (static_cast<int>(!label.empty()) * CHECK_BOX_LABEL_HEIGHT)
        )
        , is_checked_(is_checked)
        , label_(label)
    {}

    CheckBox::CheckBox(const CheckBox& other)
        : Component(other)
        , is_checked_(other.is_checked_)
        , label_(other.label_)
    {}

    bool CheckBox::getIsChecked()
    {
        return is_checked_;
    }

    void CheckBox::setIsChecked(bool is_checked)
    {
        is_checked_ = is_checked;
    }

    void CheckBox::display()
    {
        Rectangle rect =
        {
            x_,
            y_ + (static_cast<int>(!label_.empty()) * CHECK_BOX_LABEL_HEIGHT),
            width_,
            width_,
            // -> not height_ because that would include the height of the label
        };

        GuiCheckBox(rect, "", &is_checked_);

        if (label_.empty())
        {
            return;
        }

        rect.y -= CHECK_BOX_LABEL_HEIGHT;
        rect.height = CHECK_BOX_LABEL_HEIGHT;
        GuiLabel(rect, label_.data());
    }
}