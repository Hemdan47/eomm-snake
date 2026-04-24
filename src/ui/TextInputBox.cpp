#include "ui/TextInputBox.h"

TextInputBox::TextInputBox(Rectangle bounds, int text_size, std::size_t max_length)
    : bounds(bounds), text_size(text_size), max_length(max_length), active(false) {}

void TextInputBox::update() {
    const int first_printable_ascii = 32;
    const int last_printable_ascii = 125;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_position = GetMousePosition();
        active = CheckCollisionPointRec(mouse_position, bounds);
    }

    if (!active) {
        return;
    }

    int key = GetCharPressed();
    while (key > 0) {
        if (key >= first_printable_ascii && key <= last_printable_ascii && text.size() < max_length) {
            text.push_back((char)key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
        text.pop_back();
    }
}

void TextInputBox::draw(const Color &accent_color, const Color &surface_color) const {
    const float active_fill_alpha = 0.20f;
    const float inactive_fill_alpha = 0.10f;
    const float placeholder_alpha = 0.55f;

    const float corner_roundness = 0.2f;
    const int corner_segments = 8;
    const float active_border_thickness = 3.0f;
    const float inactive_border_thickness = 2.0f;

    const int cursor_x_offset = 4;
    const std::string placeholder_text = "Type your name";

    Color fill_color = Fade(accent_color, active ? active_fill_alpha : inactive_fill_alpha);
    DrawRectangleRounded(bounds, corner_roundness, corner_segments, fill_color);
    DrawRectangleRoundedLinesEx(bounds,
                               corner_roundness,
                               corner_segments,
                               active ? active_border_thickness : inactive_border_thickness,
                               accent_color);

    const std::string display_text = text.empty() ? placeholder_text : text;
    Color text_color = text.empty() ? Fade(accent_color, placeholder_alpha) : accent_color;

    int text_width = MeasureText(display_text.c_str(), text_size);
    int text_x = (int)(bounds.x + (bounds.width - (float)text_width) / 2.0f);
    int text_y = (int)(bounds.y + (bounds.height - (float)text_size) / 2.0f);
    DrawText(display_text.c_str(), text_x, text_y, text_size, text_color);

    if (active) {
        int cursor_x = text_x + text_width + cursor_x_offset;
        int cursor_y = text_y;
        DrawText("|", cursor_x, cursor_y, text_size, accent_color);
    }
}

const std::string &TextInputBox::get_text() const {
    return text;
}

void TextInputBox::set_text(const std::string &value) {
    text = value.substr(0, max_length);
}

const Rectangle &TextInputBox::get_bounds() const {
    return bounds;
}