#pragma once

#include <cstdint>

#include "gui/dropdown.hh"

#define ITEM_TYPE_SELECTOR_WIDTH 140

namespace gui
{
    class ItemTypeSelector : public Component
    {
    public:
        ItemTypeSelector(std::uint32_t& item_type);
        ItemTypeSelector(const ItemTypeSelector& other);
        Dropdown& getDropdown();
        void display() override;
    private:
        Dropdown dropdown_;
        std::uint32_t& item_type_;
        void setItemType(std::uint32_t item_type);
    };
}