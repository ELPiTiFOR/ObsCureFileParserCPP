#include "item_type_selector.hh"

#include "oci/item.hh"

namespace gui
{
    ItemTypeSelector::ItemTypeSelector(std::uint32_t& item_type)
        : Component(0, 0, DROPDOWN_HEIGHT, ITEM_TYPE_SELECTOR_WIDTH)
        , dropdown_(Dropdown(ITEM_TYPE_SELECTOR_WIDTH))
        , item_type_(item_type)
    {
        int i = 0;
        for (oci::Item item : oci::all_items)
        {
            if (item.type == item_type)
            {
                dropdown_.setActiveOption(i);
            }
            dropdown_.addOption(item.name);
            i++;
        }
    }

    ItemTypeSelector::ItemTypeSelector(const ItemTypeSelector& other)
        : Component(other)
        , dropdown_(other.dropdown_)
        , item_type_(other.item_type_)
    {}

    Dropdown& ItemTypeSelector::getDropdown()
    {
        return dropdown_;
    }

    void ItemTypeSelector::setItemType(std::uint32_t item_type)
    {
        item_type_ = item_type;
    }

    void ItemTypeSelector::display()
    {
        setItemType(oci::all_items.at(dropdown_.getActiveOption()).type);
        dropdown_.setX(x_);
        dropdown_.setY(y_);
        dropdown_.display();
    }
}