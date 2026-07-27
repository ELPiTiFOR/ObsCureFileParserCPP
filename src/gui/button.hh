#pragma once

#include <functional>
#include <string>

#include "gui/component.hh"

namespace gui
{
    class Button : public Component
    {
    private:
        std::function<void()> pressed_callback_;
        std::string text_;
    public:
        Button(float width, float height, const std::string& text);
        Button(const Button& other);
        Button& operator=(const Button& other);
        void display() override;
        void setPressedCallback(std::function<void()> callback);
    };
}