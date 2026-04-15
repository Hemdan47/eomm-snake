#ifndef EOMM_SNAKE_CONFIG_H
#define EOMM_SNAKE_CONFIG_H
#include <string>
#include "raylib.h"

class Config {
public:
    char title[11]{"eomm snake"};
    int target_fps = 60;

    int board_frame_offset = 5;
    int board_frame_extra_size = 10;
    int board_frame_line_thickness = 5;
    int ui_text_y = 20;
    int ui_text_size = 40;

    Color light_sand = { 245, 230, 200, 255 };
    Color burnt_orange = { 190, 110, 50, 255 };

    std::size_t cell_size = 30;
    std::size_t cell_count = 25;
    std::size_t offset = 75;


    double initial_speed = 0.2;
    double speed = initial_speed;
    double speed_change = 0.005;


    void increase_speed() {
        speed = std::max(0.05 , speed-speed_change);
    }

    void reset_speed() {
        speed = initial_speed;
    }
};

#endif //EOMM_SNAKE_CONFIG_H