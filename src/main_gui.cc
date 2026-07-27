#include <iostream>
#include <vector>

#include "raylib.h"
#include "raygui.h"

#include "it/it_file.hh"
#include "gui/canvas.hh"
#include "gui/diff_mode.hh"
#include "gui/file_search_bar.hh"
#include "gui/it_scroll_list.hh"
#include "gui/text_box.hh"
#include "oci/item.hh"

#define IT_WINDOW_WIDTH 660
#define IT_WINDOW_HEIGHT 700

int main(int argc, char *argv[])
{
    oci::initializeAllItems();
    oci::initializeAllItemUids();
    oci::initializeAllExtraInfos();

    InitWindow(IT_WINDOW_WIDTH, IT_WINDOW_HEIGHT, "ObsCureFileParser");
    SetTargetFPS(60);

    std::string file_path_str("");
    if (argc > 1)
    {
        std::string first_parametre(argv[1]);
        std::filesystem::path file_path(first_parametre);
        if (std::filesystem::exists(file_path))
        {
            file_path_str = first_parametre;
        }
    }

    gui::FileSearchBar<ItFile> it_search_bar(0, 0, file_path_str);
    gui::ItScrollList it_scroll_list(0, 0);

    Rectangle rect = {0, 0, IT_WINDOW_WIDTH, IT_WINDOW_HEIGHT};
    gui::Canvas window_canvas(&rect, false, nullptr);

    gui::Line* search_bar_line = window_canvas.addLine(45);
    gui::Canvas* search_bar_canvas = search_bar_line->addCanvas(IT_WINDOW_WIDTH);
    search_bar_canvas->setComponent(&it_search_bar);

    gui::Line* it_scroll_line = window_canvas.addLine(IT_WINDOW_HEIGHT - 45);
    gui::Canvas* it_scroll_canvas = it_scroll_line->addCanvas(IT_WINDOW_WIDTH);
    it_scroll_canvas->setComponent(&it_scroll_list);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        it_scroll_list.setItFileAndUpdate(it_search_bar.getFile());
        window_canvas.display();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}