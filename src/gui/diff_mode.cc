#include "diff_mode.hh"

namespace gui
{
    DiffMode::DiffMode(oci::DiffMode& diff_mode)
        : Component(0, 0, DIFF_MODE_WIDTH, DIFF_MODE_HEIGHT)
        , diff_mode_(diff_mode)
        , special_box_(CheckBox(diff_mode.getSpecial(), "S", 25))
        , hard_box_(CheckBox(diff_mode.getHard(), "H", 25))
        , normal_box_(CheckBox(diff_mode.getNormal(), "N", 25))
        , easy_box_(CheckBox(diff_mode.getEasy(), "E", 25))
    {}

    DiffMode::DiffMode(const DiffMode& other)
        : Component(other)
        , diff_mode_(other.diff_mode_)
        , special_box_(other.special_box_)
        , hard_box_(other.hard_box_)
        , normal_box_(other.normal_box_)
        , easy_box_(other.easy_box_)
    {}

    void DiffMode::display()
    {
        diff_mode_.setSpecial(special_box_.getIsChecked());
        diff_mode_.setHard(hard_box_.getIsChecked());
        diff_mode_.setNormal(normal_box_.getIsChecked());
        diff_mode_.setEasy(easy_box_.getIsChecked());

        special_box_.setX(x_);
        special_box_.setY(y_);
        special_box_.display();

        // TODO: very dirty
        hard_box_.setX(x_ + 27);
        hard_box_.setY(y_);
        hard_box_.display();

        normal_box_.setX(x_ + 54);
        normal_box_.setY(y_);
        normal_box_.display();

        easy_box_.setX(x_ + 81);
        easy_box_.setY(y_);
        easy_box_.display();
    }
}