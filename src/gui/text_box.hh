#pragma once

#include <cstring>
#include <functional>
#include <string>

#include "raygui.h"

#include "gui/component.hh"

#define TEXT_BOX_BUFFER_SIZE 1024

namespace gui
{
    class TextBox : public Component
    {
    public:
        TextBox() = default;
        TextBox(Rectangle* rect, const std::string& text);
        TextBox(float x, float y, float width, float height);
        TextBox(const TextBox& other);
        TextBox& operator=(const TextBox& other);
        char* getText();
        bool getIsFocused() const;
        void setText(const std::string& text);
        void setFocusedCallback(std::function<void()> callback);
        void setNotFocusedCallback(std::function<void()> callback);
        void display() override;
    private:
        char text_[TEXT_BOX_BUFFER_SIZE];
        bool is_focused_;
        std::function<void()> focused_callback_;
        std::function<void()> not_focused_callback_;
    };
} // namespace gui