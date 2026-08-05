#include <iostream>
#include <vector>

#include "raylib.h"
#include "raygui.h"

#include "config/config.hh"
#include "it/it_file.hh"
#include "sav/sav_file.hh"
#include "gui/canvas.hh"
#include "gui/diff_mode.hh"
#include "gui/file_search_bar.hh"
#include "gui/it_scroll_list.hh"
#include "gui/sav_view.hh"
#include "gui/text_box.hh"
#include "gui/windows/it_window.hh"
#include "gui/windows/sav_window.hh"
#include "oci/item.hh"

int main(int argc, char *argv[])
{
    oci::initializeAllItems();
    oci::initializeAllItemUids();
    oci::initializeAllExtraInfos();

    // float main_window_width = IT_WINDOW_WIDTH * 2;
    float main_window_width = IT_WINDOW_WIDTH;
    float main_window_height = IT_WINDOW_HEIGHT;
    InitWindow(main_window_width, main_window_height, "ObsCureFileParser");
    SetTargetFPS(60);

    std::string sav_path_str("");
    std::string it_path_str("");

    // Reading the config file
    try
    {
        std::string filename("OCFP.config");
        Config config(filename);
        it_path_str = config.getValueOrDefault("IT_DEFAULT_PATH", "");
        sav_path_str = config.getValueOrDefault("SAV_DEFAULT_PATH", "");
    } catch (std::exception& e)
    {}

    if (argc > 1)
    {
        std::string first_parametre(argv[1]);
        std::filesystem::path file_path(first_parametre);
        if (std::filesystem::exists(file_path))
        {
            it_path_str = first_parametre;
            sav_path_str = first_parametre;
        }
    }

    // IT WIN
    gui::ItWindow it_window(it_path_str);
    // gui::SavWindow sav_window(sav_path_str);

    gui::Canvas main_window(main_window_width, main_window_height, false,
        nullptr);
    gui::Line* line = main_window.addLine(main_window_height);
    gui::Canvas* it_win_canvas = line->addCanvas(IT_WINDOW_WIDTH);
    it_win_canvas->setComponent(&it_window);

    // gui::Canvas* sav_win_canvas = line->addCanvas(SAV_WINDOW_WIDTH);
    // sav_win_canvas->setComponent(&sav_window);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // IT WIN
        main_window.display();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}