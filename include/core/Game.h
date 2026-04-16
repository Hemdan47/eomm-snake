#ifndef EOMM_SNAKE_GAME_H
#define EOMM_SNAKE_GAME_H
#include <memory>

#include "../Config.h"
#include "../entities/Food.h"
#include "../entities/Snake.h"

class Game {
public:
    explicit Game(Config &config);
    ~Game();
    void update();
    void draw();
    Vector2 get_snake_current_direction();
    void set_snake_direction(Vector2 direction);
    bool is_running();
    void set_running(bool running);
    std::size_t get_score();

private:
    bool check_collision_with_food();
    bool check_collision_with_wall();
    void game_over();
    bool check_collision_with_tail();
    Vector2 generate_random_cell();
    bool check_element_in_deque(Vector2 element, std::deque<Vector2>snake_body);
    Vector2 generate_random_position(std::deque<Vector2>snake_body);


    Config &config;
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Food> food;
    bool running;
    std::size_t score;
    Sound eat_sound;
    Sound wall_sound;
};
#endif //EOMM_SNAKE_GAME_H