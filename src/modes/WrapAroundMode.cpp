#include "modes/WrapAroundMode.h"

WrapAroundMode::WrapAroundMode(Config &config) : Game(config){}

void WrapAroundMode::update() {
    if (running) {
        bool add = check_collision_with_food();
        bool wrap = true;
        snake->update(add , wrap);
        bool game_over = check_collision_with_tail();
        if (game_over) {
            this->game_over();
        }
    }
}
