#pragma once

#include "gui/canvas.hh"
#include "gui/file_search_bar.hh"
#include "gui/it_scroll_list.hh"
#include "it/it_file.hh"

#define IT_WINDOW_WIDTH 660
#define IT_WINDOW_HEIGHT 700

namespace gui
{
    class ItWindow : public Canvas
    {
    private:
        gui::FileSearchBar<ItFile> it_search_bar_;
        gui::ItScrollList it_scroll_list_;
    public:
        ItWindow(const std::string& file_path);
        void display();
    };
}