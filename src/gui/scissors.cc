#include "scissors.hh"

#include "gui/utils_gui.hh"

namespace gui
{
    std::vector<ScissorsRectangles> Scissors::rectangles_;

    std::vector<ScissorsRectangles>& Scissors::getRectangles()
    {
        return rectangles_;
    }

    void Scissors::StartScissors(Rectangle& rect)
    {
        if (rectangles_.size())
        {
            EndScissorMode();
        }

        Rectangle& overlapped = pushRectangles(rect).overlapped;
        BeginScissorMode(overlapped.x, overlapped.y, overlapped.width,
            overlapped.height);
    }

    void Scissors::EndScissors()
    {
        EndScissorMode();
        popRectangles(nullptr);
        if (!rectangles_.size())
        {
            return;
        }

        Rectangle& previous_rect = rectangles_.back().overlapped;
        BeginScissorMode(previous_rect.x, previous_rect.y, previous_rect.width,
            previous_rect.height);
    }

    void Scissors::popRectangles(ScissorsRectangles* res)
    {
        if (!rectangles_.size())
        {
            return;
        }

        if (res)
        {
            *res = rectangles_.back();
        }

        rectangles_.pop_back();
    }

    ScissorsRectangles& Scissors::pushRectangles(Rectangle& rect)
    {
        // TODO: checking only the last overlapped rectangle would be quicker
        Rectangle overlap_rect = rect;
        for (ScissorsRectangles scissors_rectangle : rectangles_)
        {
            gui::utils::overlap(overlap_rect, scissors_rectangle.solo);
        }

        ScissorsRectangles new_rects = { rect, overlap_rect };
        rectangles_.push_back(new_rects);
        return rectangles_.back();
    }
}