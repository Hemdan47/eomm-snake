#ifndef EOMM_SNAKE_BUTTON_H
#define EOMM_SNAKE_BUTTON_H

#include <string>
#include "raylib.h"

class Button {
public:
    Button(Rectangle bounds, std::string text, int text_size);

    void draw(const Color &accent_color,
              const Color &surface_color,
              bool selected) const;
    bool contains(Vector2 point) const;
    const Rectangle &get_bounds() const;

private:
    Rectangle bounds;
    std::string text;
    int text_size;
};

#endif //EOMM_SNAKE_BUTTON_H
