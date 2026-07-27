#include "component.hh"

namespace gui
{
    Component::Component()
        : x_(0)
        , y_(0)
        , width_(0)
        , height_(0)
    {}

    Component::Component(Rectangle* rect)
        : x_(rect->x)
        , y_(rect->y)
        , width_(rect->width)
        , height_(rect->height)
    {}

    Component::Component(float x, float y, float width, float height)
        : x_(x)
        , y_(y)
        , width_(width)
        , height_(height)
    {}

    float Component::getX() const
    {
        return x_;
    }

    float Component::getY() const
    {
        return y_;
    }

    float Component::getWidth() const
    {
        return width_;
    }

    float Component::getHeight() const
    {
        return height_;
    }

    void Component::setX(float x)
    {
        x_ = x;
    }

    void Component::setY(float y)
    {
        y_ = y;
    }

    void Component::setWidth(float width)
    {
        width_ = width;
    }

    void Component::setHeight(float height)
    {
        height_ = height;
    }

    void Component::display()
    {}
}