#include "extra_info_selector.hh"

#include "oci/item.hh"

namespace gui
{
    ExtraInfoSelector::ExtraInfoSelector(std::uint32_t& extra_info)
        : Component(0, 0, DROPDOWN_HEIGHT, EXTRA_INFO_SELECTOR_WIDTH)
        , dropdown_(Dropdown(EXTRA_INFO_SELECTOR_WIDTH))
        , extra_info_(extra_info)
    {
        int i = 0;
        for (oci::ExtraInfo my_extra_info : oci::all_extra_infos)
        {
            if (my_extra_info.id == extra_info)
            {
                dropdown_.setActiveOption(i);
            }
            dropdown_.addOption(my_extra_info.name);
            i++;
        }
    }

    ExtraInfoSelector::ExtraInfoSelector(const ExtraInfoSelector& other)
        : Component(other)
        , dropdown_(other.dropdown_)
        , extra_info_(other.extra_info_)
    {}

    Dropdown& ExtraInfoSelector::getDropdown()
    {
        return dropdown_;
    }

    void ExtraInfoSelector::setExtraInfo(std::uint32_t extra_info)
    {
        extra_info_ = extra_info;
    }

    void ExtraInfoSelector::display()
    {
        setExtraInfo(oci::all_extra_infos.at(dropdown_.getActiveOption()).id);
        dropdown_.setX(x_);
        dropdown_.setY(y_);
        dropdown_.display();
    }
}