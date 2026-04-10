#ifndef EOMM_SNAKE_CONFIG_H
#define EOMM_SNAKE_CONFIG_H
#include <string>
#include "raylib.h"

class Config {
public:
    char title[11]{"eomm snake"};

    Color light_sand = { 245, 230, 200, 255 };
    Color burnt_orange = { 190, 110, 50, 255 };

    std::size_t cell_size = 30;
    std::size_t cell_count = 25;
    std::size_t offset = 75;
};

#endif //EOMM_SNAKE_CONFIG_H