#include "sav_window.hh"

namespace gui
{
    SavWindow::SavWindow(const std::string& file_path)
        : Canvas(
            SAV_WINDOW_WIDTH,
            SAV_WINDOW_HEIGHT,
            false,
            nullptr
        )
        , sav_search_bar_(FileSearchBar<SavFile>(0, 0, file_path))
        , sav_view_(SavView())
    {
        Line* search_bar_line = addLine(45);
        Canvas* search_bar_canvas = search_bar_line->addCanvas(SAV_WINDOW_WIDTH);
        search_bar_canvas->setComponent(&sav_search_bar_);

        Line* sav_view_line = addLine(SAV_WINDOW_HEIGHT - 45);
        Canvas* sav_view_canvas = sav_view_line->addCanvas(SAV_WINDOW_WIDTH);
        sav_view_canvas->setComponent(&sav_view_);
    }

    void SavWindow::display()
    {
        sav_view_.setSavFileAndUpdate(sav_search_bar_.getFile());
        Canvas::display();
    }
}