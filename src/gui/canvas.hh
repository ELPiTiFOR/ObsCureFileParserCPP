#pragma once

#include <vector>

#include "raygui.h"

#include "gui/component.hh"

namespace gui
{
    enum class LineStyle
    {
        NONE,
        SPACE_BETWEEN,
        CENTERED
    };

    // TODO: the addLine and addCanvas functions returning a pointer is not
    // ideal, the pointers seem to go invalid after adding more lines/canvases
    class Line;
    class Canvas : public Component
    {
    public:
        Canvas();
        Canvas(Rectangle* rect, bool is_scrollable, gui::Component* component);
        Canvas(float width, float height, bool is_scrollable,
            gui::Component* component);
        bool getIsScrollable();
        gui::Component* getComponent();
        std::vector<Line>& getLines();
        void setIsScrollable(bool is_scrollable);
        void setComponent(gui::Component* component);
        virtual void display();
        Line* addLine(float height);
    private:
        bool is_scrollable_;
        gui::Component* component_;
        std::vector<Line> lines_;
        Rectangle panel_bounds_;
        Rectangle content_bounds_;
        Vector2 scroll_;
        Rectangle view_;
    };

    class Line : public Component
    {
    public:
        Line();
        Line(Rectangle* rect);
        Line(float x, float y, float width, float height);
        std::vector<gui::Canvas>& getCanvases();
        LineStyle getStyle();
        void setStyle(LineStyle style);
        void display();
        Canvas* addCanvas(float width);
    private:
        std::vector<Canvas> canvases_;
        LineStyle style_;
    };
} // namespace gui