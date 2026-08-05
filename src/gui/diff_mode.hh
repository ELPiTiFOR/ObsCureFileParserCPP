#pragma once

#include "gui/check_box.hh"
#include "oci/diff_mode.hh"

#define DIFF_MODE_WIDTH 27*4
#define DIFF_MODE_HEIGHT 50

namespace gui
{
    class DiffMode : public Component
    {
    public:
        DiffMode(oci::DiffMode* diff_mode);
        DiffMode(const DiffMode& other);
        oci::DiffMode* getDiffMode();
        void setDiffMode(oci::DiffMode* diff_mode);
        void display() override;
    private:
        oci::DiffMode* diff_mode_;
        gui::CheckBox special_box_;
        gui::CheckBox hard_box_;
        gui::CheckBox normal_box_;
        gui::CheckBox easy_box_;
    };
}