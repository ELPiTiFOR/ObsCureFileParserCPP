#include "text_box.hh"

namespace gui
{
    TextBox::TextBox(Rectangle* rect, const std::string& text)
        : Component(rect)
        , is_focused_(false)
    {
        memset(text_, 0, TEXT_BOX_BUFFER_SIZE);
        text.copy(text_, text.length(), 0);
    }

    TextBox::TextBox(float x, float y, float width, float height)
        : Component(x, y, width, height)
        , is_focused_(false)
    {}

    TextBox::TextBox(const TextBox& other)
        : Component(other)
        , is_focused_(other.is_focused_)
        , focused_callback_(other.focused_callback_)
        , not_focused_callback_(other.not_focused_callback_)
    {
        strncpy(text_, other.text_, TEXT_BOX_BUFFER_SIZE);
        text_[TEXT_BOX_BUFFER_SIZE - 1] = '\0';
    }

    TextBox& TextBox::operator=(const TextBox& other)
    {
        if (this != &other)
        {
            Component::operator=(other);
            
            is_focused_ = other.is_focused_;
            focused_callback_ = other.focused_callback_;
            not_focused_callback_ = other.not_focused_callback_;
            strncpy(text_, other.text_, TEXT_BOX_BUFFER_SIZE);
            text_[TEXT_BOX_BUFFER_SIZE - 1] = '\0';
        }
        return *this;
    }

    char* TextBox::getText()
    {
        return text_;
    }

    bool TextBox::getIsFocused() const
    {
        return is_focused_;
    }

    void TextBox::setText(const std::string& text)
    {
        memset(text_, 0, TEXT_BOX_BUFFER_SIZE);
        text.copy(text_, text.length(), 0);
    }

    void TextBox::setFocusedCallback(std::function<void()> callback)
    {
        focused_callback_ = callback;
    }

    void TextBox::setNotFocusedCallback(std::function<void()> callback)
    {
        not_focused_callback_ = callback;
    }

    void TextBox::display()
    {
        Rectangle text_box_rect =
        {
            x_,
            y_,
            width_,
            height_ 
        };

        if (GuiTextBox(text_box_rect, text_, TEXT_BOX_BUFFER_SIZE, is_focused_))
        {
            is_focused_ = !is_focused_;
            if (!is_focused_ && not_focused_callback_)
            {
                not_focused_callback_();
            }
            else if (is_focused_ && focused_callback_)
            {
                focused_callback_();
            }
        }
    }
}