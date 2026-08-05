#pragma once

#include "gui/canvas.hh"
#include "gui/diff_mode.hh"
#include "gui/text_box.hh"
#include "sav/sav_file.hh"

#define SAV_VIEW_WIDTH 500
#define SAV_VIEW_HEIGHT 620
#define SAV_INDEX_WIDTH 25
#define SAV_INDEX_HEIGHT 25
#define SAV_INDEX_CANVAS_WIDTH 50
#define SAV_DIFF_MODE_CANVAS_WIDTH 50
#define SAV_HEADER_HEIGHT 60

namespace gui
{
    class SavView : public Canvas
    {
    public:
        SavView();
        SavFile* getSavFile();
        void setSavFile(SavFile* sav_file);
        void setSavFileAndUpdate(SavFile* sav_file);
    private:
        gui::TextBox index_;
        gui::DiffMode diff_mode_;
        SavFile* sav_file_;
        void updateIndex();
        void LoadSavFile();
    };
}