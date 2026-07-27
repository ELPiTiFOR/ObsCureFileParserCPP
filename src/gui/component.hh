#pragma once

#include "raygui.h"

namespace gui
{
    class Component
    {
    public:
        Component();
        Component(Rectangle* rect);
        Component(float x, float y, float width, float height);
        float getX() const;
        float getY() const;
        float getWidth() const;
        float getHeight() const;
        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
        virtual void display();
    protected:
        float x_;
        float y_;
        float width_;
        float height_;
    };
} // namespace gui