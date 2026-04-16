#include "modes/ClassicMode.h"


ClassicMode::ClassicMode(Config &config) : Game(config){}

bool ClassicMode::check_collision_with_wall() {
    std::deque<Vector2> snake_body = snake->get_body();
    if (snake_body.front().x == config.cell_count
        || snake_body.front().x == -1
        || snake_body.front().y == config.cell_count
        || snake_body.front().y == -1)
    {
        return true;
    }
    return false;
}

void ClassicMode::update() {
    if (running) {
        bool add = check_collision_with_food();
        bool wrap = false;
        snake->update(add , wrap);
        bool game_over = check_collision_with_wall() || check_collision_with_tail();
        if (game_over) {
            this->game_over();
        }
    }
}
