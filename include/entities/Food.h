#ifndef EOMM_SNAKE_FOOD_H
#define EOMM_SNAKE_FOOD_H
#include <deque>
#include "Config.h"
#include "raylib.h"

class Food {
public:
    explicit Food(Config &config, Vector2 initial_position);
    ~Food();
    void draw();
    Vector2 get_position() const;
    void set_position(Vector2 new_position);


private:
    Vector2 position;
    Texture2D texture;
    Config &config;
};

#endif //EOMM_SNAKE_FOOD_H