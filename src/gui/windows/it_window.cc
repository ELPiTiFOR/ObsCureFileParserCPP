#include "it_window.hh"

namespace gui
{
    ItWindow::ItWindow(const std::string& file_path)
        : Canvas(
            IT_WINDOW_WIDTH,
            IT_WINDOW_HEIGHT,
            false,
            nullptr
        )
        , it_search_bar_(FileSearchBar<ItFile>(0, 0, file_path))
        , it_scroll_list_(ItScrollList(0, 0))
    {
        Line* search_bar_line = addLine(45);
        Canvas* search_bar_canvas = search_bar_line->addCanvas(IT_WINDOW_WIDTH);
        search_bar_canvas->setComponent(&it_search_bar_);

        Line* it_scroll_line = addLine(IT_WINDOW_HEIGHT - 45);
        Canvas* it_scroll_canvas = it_scroll_line->addCanvas(IT_WINDOW_WIDTH);
        it_scroll_canvas->setComponent(&it_scroll_list_);
    }

    void ItWindow::display()
    {
        it_scroll_list_.setItFileAndUpdate(it_search_bar_.getFile());
        Canvas::display();
    }
}