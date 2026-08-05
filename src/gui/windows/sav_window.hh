#pragma once

#include "gui/canvas.hh"
#include "gui/file_search_bar.hh"
#include "gui/sav_view.hh"
#include "sav/sav_file.hh"

#define SAV_WINDOW_WIDTH 660
#define SAV_WINDOW_HEIGHT 700

namespace gui
{
    class SavWindow : public Canvas
    {
    private:
        gui::FileSearchBar<SavFile> sav_search_bar_;
        gui::SavView sav_view_;
    public:
        SavWindow(const std::string& file_path);
        void display();
    };
}