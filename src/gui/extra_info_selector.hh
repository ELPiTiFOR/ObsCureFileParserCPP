#pragma once

#include <cstdint>

#include "gui/dropdown.hh"

#define EXTRA_INFO_SELECTOR_WIDTH 140

namespace gui
{
    class ExtraInfoSelector : public Component
    {
    public:
        ExtraInfoSelector(std::uint32_t& extra_info);
        ExtraInfoSelector(const ExtraInfoSelector& other);
        Dropdown& getDropdown();
        void display() override;
    private:
        Dropdown dropdown_;
        std::uint32_t& extra_info_;
        void setExtraInfo(std::uint32_t extra_info);
    };
}