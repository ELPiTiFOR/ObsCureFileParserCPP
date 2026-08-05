#include "sav_view.hh"

#include "utils/utils.hh"

namespace gui
{
    SavView::SavView()
        : Canvas(
            SAV_VIEW_WIDTH,
            SAV_VIEW_HEIGHT,
            true,
            nullptr
        )
        , index_(TextBox(0, 0, SAV_INDEX_WIDTH, SAV_INDEX_HEIGHT))
        , diff_mode_(DiffMode(nullptr))
    {
        Line* header_line = addLine(SAV_HEADER_HEIGHT);
        header_line->setStyle(LineStyle::SPACE_BETWEEN);
        Canvas* index_canvas = header_line->addCanvas(SAV_DIFF_MODE_CANVAS_WIDTH);
        index_canvas->setComponent(&index_);

        Canvas* diff_mode_canvas = header_line->addCanvas(SAV_INDEX_CANVAS_WIDTH);
        diff_mode_canvas->setComponent(&diff_mode_);

        index_.setNotFocusedCallback([this]() {
            this->updateIndex();
        });
    }

    SavFile* SavView::getSavFile()
    {
        return sav_file_;
    }

    void SavView::setSavFile(SavFile* sav_file)
    {
        sav_file_ = sav_file;
    }

    void SavView::updateIndex()
    {
        if (!sav_file_)
        {
            return;
        }

        try
        {
            std::uint32_t index = utils::stringToUint(index_.getText());
            sav_file_->getHeader().setIndex(index);
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: Invalid input for UID" << std::endl;
        }
    }

    void SavView::setSavFileAndUpdate(SavFile* sav_file)
    {
        if (sav_file == sav_file_)
        {
            return;
        }

        setSavFile(sav_file);
        if (!sav_file_)
        {
            return;
        }

        // TODO: do we need to do more stuff here?
        LoadSavFile();
    }

    void SavView::LoadSavFile()
    {
        if (!sav_file_)
        {
            return;
        }

        index_.setText(utils::uintToString(sav_file_->getHeader().getIndex()));
        diff_mode_.setDiffMode(sav_file_->getHeader().getDiffModePtr());
    }
}