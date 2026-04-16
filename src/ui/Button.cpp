#include "ui/Button.h"

Button::Button(Rectangle bounds, std::string text, int text_size)
    : bounds(bounds), text(std::move(text)), text_size(text_size) {}

void Button::draw(const Color &accent_color,
                  const Color &surface_color,
                  bool selected) const {
    Color fill_color = selected ? accent_color : Fade(accent_color, 0.15f);
    Color text_color = selected ? surface_color : accent_color;

    DrawRectangleRounded(bounds, 0.2f, 8, fill_color);
    DrawRectangleRoundedLinesEx(bounds, 0.2f, 8, 2.0f, accent_color);

    int text_x = (int)(bounds.x + (bounds.width - (float)MeasureText(text.c_str(), text_size)) / 2.0f);
    int text_y = (int)(bounds.y + (bounds.height - (float)text_size) / 2.0f);
    DrawText(text.c_str(), text_x, text_y, text_size, text_color);
}

bool Button::contains(Vector2 point) const {
    return CheckCollisionPointRec(point, bounds);
}

const Rectangle &Button::get_bounds() const {
    return bounds;
}
