#pragma once

#include <vector>

#include "raygui.h"

namespace gui
{
    struct ScissorsRectangles
    {
        Rectangle solo;
        Rectangle overlapped;
    };

    class Scissors
    {
    public:
        static std::vector<ScissorsRectangles>& getRectangles();
        static void StartScissors(Rectangle& rect);
        static void EndScissors();
    private:
        static std::vector<ScissorsRectangles> rectangles_;
        static void popRectangles(ScissorsRectangles* res);
        static ScissorsRectangles& pushRectangles(Rectangle& rect);
    };
}