#include "button.hh"

namespace gui
{
    Button::Button(float width, float height, const std::string& text)
        : Component(0, 0, width, height)
        , text_(text)
    {}

    Button::Button(const Button& other)
        : Component(other)
        , pressed_callback_(other.pressed_callback_)
        , text_(other.text_)
    {}

    Button& Button::operator=(const Button& other)
    {
        if (this != &other)
        {
            Component::operator=(other);
            
            pressed_callback_ = other.pressed_callback_;
            text_ = other.text_;
        }
        return *this;
    }

    void Button::display()
    {
        Rectangle rect =
        {
            x_,
            y_,
            width_,
            height_,
        };

        if (GuiButton(rect, text_.data()) && pressed_callback_)
        {
            pressed_callback_();
        }
    }

    void Button::setPressedCallback(std::function<void()> callback)
    {
        pressed_callback_ = callback;
    }
}