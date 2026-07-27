#include "it_scroll_list.hh"

#include "gui/scissors.hh"
#include "utils/utils.hh"

#include "oci/item.hh"

namespace gui
{
    ItScrollElement::ItScrollElement(ItItem& it_item)
        : Component(0, 0,
            IT_SCROLL_ELEMENT_UID_WIDTH + 5 + IT_SCROLL_ELEMENT_MUL_WIDTH,
            IT_SCROLL_ELEMENT_UID_HEIGHT
                + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN * 2
                + IT_SCROLL_ELEMENT_REMOVE_BUTTON_MARGIN * 2
                + IT_SCROLL_ELEMENT_REMOVE_BUTTON_WIDTH
        )
        , uid_(0, 0,
            IT_SCROLL_ELEMENT_UID_WIDTH,
            IT_SCROLL_ELEMENT_UID_HEIGHT
        )
        , multiplier_(0, 0,
            IT_SCROLL_ELEMENT_MUL_WIDTH,
            IT_SCROLL_ELEMENT_MUL_HEIGHT
        )
        , diff_mode_(DiffMode(it_item.getDiffMode()))
        , item_type_selector_(ItemTypeSelector(it_item.getItemType()))
        , extra_info_selector_(ExtraInfoSelector(it_item.getExtraInfo()))
        , remove_button_(Button(
            IT_SCROLL_ELEMENT_REMOVE_BUTTON_WIDTH,
            IT_SCROLL_ELEMENT_REMOVE_BUTTON_WIDTH,
            "X"
        ))
        , add_up_button_(Button(
            IT_SCROLL_ELEMENT_ADD_BUTTON_WIDTH,
            IT_SCROLL_ELEMENT_ADD_BUTTON_HEIGHT,
            "Add up"
        ))
        , add_down_button_(Button(
            IT_SCROLL_ELEMENT_ADD_BUTTON_WIDTH,
            IT_SCROLL_ELEMENT_ADD_BUTTON_HEIGHT,
            "Add down"
        ))
        , it_item_(it_item)
    {
        uid_.setText(utils::uintToHexString(it_item.getItemUid()));
        uid_.setNotFocusedCallback([this]() {
            this->updateUid();
        });

        multiplier_.setText(utils::uintToString(it_item.getMultiplier()));
        multiplier_.setNotFocusedCallback([this]() {
            this->updateMultiplier();
        });
    }

    ItScrollElement::ItScrollElement(const ItScrollElement& other)
        : Component(other)
        , uid_(other.uid_)
        , multiplier_(other.multiplier_)
        , diff_mode_(other.diff_mode_)
        , item_type_selector_(other.item_type_selector_)
        , extra_info_selector_(other.extra_info_selector_)
        , remove_button_(other.remove_button_)
        , add_up_button_(other.add_up_button_)
        , add_down_button_(other.add_down_button_)
        , it_item_(other.it_item_)
    {
        uid_.setNotFocusedCallback([this]() {
            this->updateUid();
        });

        multiplier_.setNotFocusedCallback([this]() {
            this->updateMultiplier();
        });
    }

    gui::TextBox& ItScrollElement::getUid()
    {
        return uid_;
    }

    ItItem& ItScrollElement::getItItem()
    {
        return it_item_;
    }

    gui::ItemTypeSelector& ItScrollElement::getItemTypeSelector()
    {
        return item_type_selector_;
    }

    gui::ExtraInfoSelector& ItScrollElement::getExtraInfoSelector()
    {
        return extra_info_selector_;
    }

    gui::Button& ItScrollElement::getRemoveButton()
    {
        return remove_button_;
    }

    gui::Button& ItScrollElement::getAddUpButton()
    {
        return add_up_button_;
    }

    gui::Button& ItScrollElement::getAddDownButton()
    {
        return add_down_button_;
    }

    void ItScrollElement::updateUid()
    {
        try
        {
            std::uint32_t new_uid = utils::hexStringToUint(uid_.getText());
            it_item_.setItemUid(new_uid);
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: Invalid input for UID" << std::endl;
        }
    }

    void ItScrollElement::updateMultiplier()
    {
        try
        {
            int new_mul = utils::stringToUint(multiplier_.getText());
            it_item_.setMultiplier(new_mul);
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: Invalid input for multiplier" << std::endl;
        }
    }

    void ItScrollElement::displayItemTypeSelector()
    {
        item_type_selector_.setX(x_);
        item_type_selector_.setY(y_ + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN);
        item_type_selector_.display();
    }

    void ItScrollElement::displayExtraInfoSelector()
    {
        extra_info_selector_.setX(x_ + ITEM_TYPE_SELECTOR_WIDTH + 5 + 5 + IT_SCROLL_ELEMENT_UID_WIDTH);
        extra_info_selector_.setY(y_ + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN);
        extra_info_selector_.display();
    }

    void ItScrollElement::display()
    {
        uid_.setX(x_ + ITEM_TYPE_SELECTOR_WIDTH + 5);
        uid_.setY(y_ + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN);
        uid_.display();

        multiplier_.setX(x_ + ITEM_TYPE_SELECTOR_WIDTH + 5 + 5 + IT_SCROLL_ELEMENT_UID_WIDTH + EXTRA_INFO_SELECTOR_WIDTH + 5);
        multiplier_.setY(y_ + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN);
        multiplier_.display();

        diff_mode_.setX(x_ + ITEM_TYPE_SELECTOR_WIDTH + 5 + 5 + IT_SCROLL_ELEMENT_UID_WIDTH + EXTRA_INFO_SELECTOR_WIDTH + 5 + IT_SCROLL_ELEMENT_MUL_WIDTH + 5);
        // TODO: isn't this a bit dirty?
        diff_mode_.setY(y_);
        diff_mode_.display();

        remove_button_.setX(x_);
        remove_button_.setY(y_ + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN
            + IT_SCROLL_ELEMENT_UID_HEIGHT
            + IT_SCROLL_ELEMENT_REMOVE_BUTTON_MARGIN);
        remove_button_.display();

        add_up_button_.setX(x_ + IT_SCROLL_ELEMENT_REMOVE_BUTTON_WIDTH
            + IT_SCROLL_ELEMENT_REMOVE_BUTTON_MARGIN);
        add_up_button_.setY(y_ + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN
            + IT_SCROLL_ELEMENT_UID_HEIGHT
            + IT_SCROLL_ELEMENT_REMOVE_BUTTON_MARGIN);
        add_up_button_.display();

        add_down_button_.setX(x_ + IT_SCROLL_ELEMENT_REMOVE_BUTTON_WIDTH
            + IT_SCROLL_ELEMENT_REMOVE_BUTTON_MARGIN * 2
            + IT_SCROLL_ELEMENT_ADD_BUTTON_WIDTH);
        add_down_button_.setY(y_ + IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN
            + IT_SCROLL_ELEMENT_UID_HEIGHT
            + IT_SCROLL_ELEMENT_REMOVE_BUTTON_MARGIN);
        add_down_button_.display();

        displayItemTypeSelector();
        displayExtraInfoSelector();
    }

    ItScrollList::ItScrollList(float x, float y)
        : Component(x, y,
            IT_SCROLL_LIST_WIDTH,
            IT_SCROLL_LIST_HEIGHT
        )
        , panel_bounds_((Rectangle){ x, y,
            IT_SCROLL_LIST_WIDTH,
            IT_SCROLL_LIST_HEIGHT }
        )
        , content_bounds_((Rectangle{ 0, 0,
            IT_SCROLL_LIST_WIDTH - 20,
            0 })
        )
        , scroll_({0, 0})
        , view_({0, 0})
        , it_file_(nullptr)
    {}

    std::vector<ItScrollElement>& ItScrollList::getItems()
    {
        return items_;
    }

    ItFile* ItScrollList::getItFile()
    {
        return it_file_;
    }

    void ItScrollList::setItFile(ItFile* it_file)
    {
        it_file_ = it_file;
    }

    void ItScrollList::setItFileAndUpdate(ItFile* it_file)
    {
        if (it_file == it_file_)
        {
            return;
        }

        setItFile(it_file);
        if (!it_file_)
        {
            return;
        }

        items_.clear();
        updateItems();
    }

    void ItScrollList::updateItems()
    {
        if (!it_file_)
        {
            return;
        }

        int index = 0;
        for (ItItem& it_item : it_file_->getItems())
        {
            addItem(it_item);
            items_.back().getRemoveButton().setPressedCallback([this, index]() {
                this->removeItem(index);
            });
            items_.back().getAddUpButton().setPressedCallback([this, index]() {
                this->addEmptyItem(index);
            });
            items_.back().getAddDownButton().setPressedCallback([this, index]() {
                this->addEmptyItem(index + 1);
            });
            ++index;
        }
    }

    void ItScrollList::addItem(ItItem& it_item)
    {
        items_.push_back(ItScrollElement(it_item));
    }

    void ItScrollList::removeItem(int index)
    {
        if (!it_file_)
        {
            return;
        }

        int i = 0;
        std::vector<ItItem>& items = it_file_->getItems();
        for (std::vector<ItItem>::iterator it = items.begin();
            it != items.end(); ++it)
        {
            if (i == index)
            {
                items.erase(it);
                break;
            }

            ++i;
        }

        items_.clear();
        updateItems();
    }

    void ItScrollList::addEmptyItem(int index)
    {
        if (!it_file_)
        {
            return;
        }

        std::vector<ItItem>& items = it_file_->getItems();
        if (index == items.size())
        {
            // handle push_back() case
            items.push_back(ItItem(
                oci::weak_flashlight.type, 0x0, oci::no_document_id.id, 0,
                oci::DiffMode(0x7)
            ));
            items_.clear();
            updateItems();
            return;
        }

        int i = 0;
        for (std::vector<ItItem>::iterator it = items.begin();
            it != items.end(); ++it)
        {
            if (i == index)
            {
                items.insert(it, ItItem(
                    oci::weak_flashlight.type, 0x0, oci::no_document_id.id, 0,
                    oci::DiffMode(0x7)
                ));
                break;
            }

            ++i;
        }

        items_.clear();
        updateItems();
    }

    void ItScrollList::display()
    {
        content_bounds_.x = x_;
        content_bounds_.y = y_;
        float element_height = 0;
        if (!items_.empty())
        {
            element_height = items_.back().getHeight();
        }

        // TODO: increase height only if necessary
        // we add some more height at the end so that the last Dropdowns can fit
        // TODO: when the dropdown is closed, do not move the view, reduce
        // the height little by little
        float new_height = items_.size() * element_height;
        if (items_.size() /*&& items_.back().getItemTypeSelector().getDropdown().getIsOpen()*/)
        {
            new_height += oci::all_items.size() * 27;
        }
        else if (items_.size() /*&& items_.back().getExtraInfoSelector().getDropdown().getIsOpen()*/)
        {
            new_height += oci::all_extra_infos.size() * 27;
        }
        content_bounds_.height = new_height;
        panel_bounds_.x = x_;
        panel_bounds_.y = y_;

        GuiScrollPanel(panel_bounds_, nullptr, content_bounds_, &scroll_, &view_);
        Scissors::StartScissors(view_);

        for (int i = items_.size() - 1; i >= 0; i--) 
        {
            float start_y = view_.y + scroll_.y + (i * element_height)
                + IT_SCROLL_ELEMENT_MARGIN;
            float start_x = view_.x + scroll_.x + IT_SCROLL_ELEMENT_MARGIN;

            ItScrollElement& element = items_.at(i);
            if (start_y + element_height < view_.y || start_y > view_.y + view_.height)
            {
                // only display the dropdown
                element.setX(start_x);
                element.setY(start_y);
                element.displayItemTypeSelector();
                element.displayExtraInfoSelector();
                continue;
            }

            GuiLine((Rectangle){ start_x , start_y + element_height
                - IT_SCROLL_ELEMENT_MARGIN, IT_SCROLL_LIST_WIDTH - IT_SCROLL_ELEMENT_MARGIN, 1 }, NULL);

            element.setX(start_x);
            element.setY(start_y);
            element.display();
        }

        Scissors::EndScissors();
    }
}