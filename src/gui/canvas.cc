#include "canvas.hh"

#include "gui/scissors.hh"

namespace gui
{
    Canvas::Canvas()
        : Component()
        , is_scrollable_(false)
        , component_(nullptr)
        , scroll_({0, 0})
        , view_({0, 0})
    {}

    Canvas::Canvas(Rectangle* rect, bool is_scrollable, gui::Component* component)
        : Component(rect)
        , is_scrollable_(is_scrollable)
        , component_(component)
        , scroll_({0, 0})
        , view_({0, 0})
    {}

    bool Canvas::getIsScrollable()
    {
        return is_scrollable_;
    }

    gui::Component* Canvas::getComponent()
    {
        return component_;
    }

    std::vector<Line>& Canvas::getLines()
    {
        return lines_;
    }

    void Canvas::setIsScrollable(bool is_scrollable)
    {
        is_scrollable_ = is_scrollable;
    }

    void Canvas::setComponent(gui::Component* component)
    {
        component_ = component;
    }

    Line* Canvas::addLine(float height)
    {
        float current_y = 0;
        for (Line& line : lines_)
        {
            current_y += line.getHeight();
        }

        if (current_y + height > height_ && !is_scrollable_)
            return nullptr;

        lines_.push_back(Line(x_, current_y, width_, height));

        return &lines_.back();
    }

    void Canvas::display()
    {
        // TODO: optimize scroll (things that do not need to be displayed)
        if (is_scrollable_)
        {
            panel_bounds_ =
            {
                x_,
                y_,
                width_,
                height_,

            };
            float content_height = 0;
            if (lines_.size())
            {
                float cumulative_height = 0;
                for (Line& line : lines_)
                {
                    cumulative_height += line.getHeight();
                }
                content_height = cumulative_height;
            }
            else if (component_)
                content_height = component_->getHeight();
            else
                content_height = height_;
            content_bounds_ =
            {
                x_,
                y_,
                width_ - 20,
                content_height,
            };
            GuiScrollPanel(panel_bounds_, nullptr, content_bounds_, &scroll_, &view_);
            Scissors::StartScissors(panel_bounds_);
        }

        if (component_)
        {
            float x_center_canvas = x_ + scroll_.x + width_ / 2;
            float y_center_canvas = y_ + scroll_.y + height_ / 2;
            component_->setX(x_center_canvas - component_->getWidth() / 2);
            component_->setY(y_center_canvas - component_->getHeight() / 2);
            component_->display();
            if (is_scrollable_)
                Scissors::EndScissors();
            return;
        }

        float current_y = y_;
        for (Line& line : lines_)
        {

            line.setX(x_ + scroll_.x);
            line.setY(current_y + scroll_.y);
            line.display();
            current_y += line.getHeight();
        }

        if (is_scrollable_)
        {
            Scissors::EndScissors();
        }
    }

    Line::Line()
        : Component()
        , style_(LineStyle::NONE)
    {}

    Line::Line(Rectangle* rect)
        : Component(rect)
        , style_(LineStyle::NONE)
    {}

    Line::Line(float x, float y, float width, float height)
        : Component(x, y, width, height)
        , style_(LineStyle::NONE)
    {}

    std::vector<gui::Canvas>& Line::getCanvases()
    {
        return canvases_;
    }

    LineStyle Line::getStyle()
    {
        return style_;
    }

    void Line::setStyle(LineStyle style)
    {
        style_ = style;
    }

    void Line::display()
    {
        float space = 0;
        if (style_ != LineStyle::NONE)
        {
            float cumulative_width = 0;
            for (Canvas& canvas: canvases_)
            {
                cumulative_width += canvas.getWidth();
            }
            if (style_ == LineStyle::SPACE_BETWEEN)
                space = (width_ - cumulative_width) / (canvases_.size() + 1);
            else if (style_ == LineStyle::CENTERED)
                space = (width_ - cumulative_width) / 2;
        }

        float current_x = x_;
        if (style_ == LineStyle::CENTERED)
            current_x += space;

        for (Canvas& canvas: canvases_)
        {
            // TODO: center the canvases
            if (style_ == LineStyle::SPACE_BETWEEN)
                current_x += space;
            canvas.setX(current_x);
            canvas.setY(y_);
            canvas.display();
            current_x += canvas.getWidth();
        }
    }

    Canvas* Line::addCanvas(float width)
    {
        float current_x = x_;
        for (Canvas& canvas : canvases_)
        {
            current_x += canvas.getWidth();
        }

        if (current_x + width > width_)
            return nullptr;

        Rectangle rect = {current_x, y_, width, height_};
        canvases_.push_back(Canvas(&rect, false, nullptr));

        return &canvases_.back();
    }
} // namespace gui