#ifndef EOMM_SNAKE_TEXTINPUTBOX_H
#define EOMM_SNAKE_TEXTINPUTBOX_H

#include <cstddef>
#include <string>

#include "raylib.h"

class TextInputBox {
public:
    TextInputBox(Rectangle bounds, int text_size, std::size_t max_length);

    void update();
    void draw(const Color &accent_color, const Color &surface_color) const;
    const std::string &get_text() const;
    void set_text(const std::string &value);
    const Rectangle &get_bounds() const;

private:
    Rectangle bounds;
    int text_size;
    std::size_t max_length;
    std::string text;
    bool active;
};

#endif //EOMM_SNAKE_TEXTINPUTBOX_H