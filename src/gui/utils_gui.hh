#pragma once

#include "raygui.h"

namespace gui::utils
{
    void overlap(Rectangle& rect1, Rectangle& rect2, Rectangle& res);
    void overlap(Rectangle& dst, Rectangle& src);
}