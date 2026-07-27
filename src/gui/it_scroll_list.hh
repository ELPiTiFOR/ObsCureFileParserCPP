#pragma once

#include <vector>

#include "raygui.h"

#include "it/it_file.hh"
#include "gui/button.hh"
#include "gui/diff_mode.hh"
#include "gui/extra_info_selector.hh"
#include "gui/item_type_selector.hh"
#include "gui/text_box.hh"

#define IT_SCROLL_ELEMENT_UID_WIDTH 100
#define IT_SCROLL_ELEMENT_UID_HEIGHT 25
#define IT_SCROLL_ELEMENT_MUL_WIDTH 40
#define IT_SCROLL_ELEMENT_MUL_HEIGHT 25
#define IT_SCROLL_ELEMENT_HEIGHT 70
#define IT_SCROLL_ELEMENT_MARGIN 10
#define IT_SCROLL_ELEMENT_DIFF_MODE_MARGIN 15
#define IT_SCROLL_ELEMENT_REMOVE_BUTTON_WIDTH 25
#define IT_SCROLL_ELEMENT_REMOVE_BUTTON_MARGIN 10
#define IT_SCROLL_ELEMENT_ADD_BUTTON_WIDTH 60
#define IT_SCROLL_ELEMENT_ADD_BUTTON_HEIGHT 25

#define IT_SCROLL_LIST_WIDTH 580
#define IT_SCROLL_LIST_HEIGHT 630

namespace gui
{
    class ItScrollElement : public Component
    {
    private:
        gui::TextBox uid_;
        gui::TextBox multiplier_;
        gui::DiffMode diff_mode_;
        gui::ItemTypeSelector item_type_selector_;
        gui::ExtraInfoSelector extra_info_selector_;
        gui::Button remove_button_;
        gui::Button add_up_button_;
        gui::Button add_down_button_;
        // int index_;
        ItItem& it_item_;
    public:
        ItScrollElement() = default;
        ItScrollElement(ItItem& it_item);
        ItScrollElement(const ItScrollElement& other);
        gui::TextBox& getUid();
        ItItem& getItItem();
        gui::ItemTypeSelector& getItemTypeSelector();
        gui::ExtraInfoSelector& getExtraInfoSelector();
        gui::Button& getRemoveButton();
        gui::Button& getAddUpButton();
        gui::Button& getAddDownButton();
        void updateUid();
        void updateMultiplier();
        void display();
        void displayItemTypeSelector();
        void displayExtraInfoSelector();
    };

    class ItScrollList : public Component
    {
    private:
        std::vector<ItScrollElement> items_;
        Rectangle panel_bounds_;
        Rectangle content_bounds_;
        Vector2 scroll_;
        Rectangle view_;
        ItFile* it_file_;
    public:
        ItScrollList(float x, float y);
        std::vector<ItScrollElement>& getItems();
        ItFile* getItFile();
        void setItFile(ItFile* it_file);
        void setItFileAndUpdate(ItFile* it_file);
        void updateItems();
        void addItem(ItItem& it_item);
        void removeItem(int index);
        void addEmptyItem(int index);
        void display() override;
    };
} // namespace gui