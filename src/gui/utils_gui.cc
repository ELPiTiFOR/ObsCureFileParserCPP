#include "utils_gui.hh"

#include <algorithm>

namespace gui::utils
{
    void overlap(Rectangle& rect1, Rectangle& rect2, Rectangle& res)
    {
        float left = std::max(rect1.x, rect2.x);
        float right = std::min(rect1.x + rect1.width, rect2.x + rect2.width);
        float top = std::max(rect1.y, rect2.y);
        float bottom = std::min(rect1.y + rect1.height, rect2.y + rect2.height);

        res = { 0 };
        if (left < right && top < bottom)
        {
            res.x = left;
            res.y = top;
            res.width = right - left;
            res.height = bottom - top;
        }
    }

    void overlap(Rectangle& dst, Rectangle& src)
    {
        overlap(dst, src, dst);
    }
}