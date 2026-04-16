#ifndef EOMM_SNAKE_SNAKE_H
#define EOMM_SNAKE_SNAKE_H
#include <deque>
#include "Config.h"
#include "raylib.h"
#include "raymath.h"

class Snake {
public:
    explicit Snake(Config &config);
    void draw();
    void update(bool add , bool wrap);
    void reset();
    std::deque<Vector2> get_body() const;
    Vector2 get_direction() const;
    void set_direction(Vector2 direction);

private:
    std::deque<Vector2> body;
    Vector2 direction;
    Config &config;
};
#endif //EOMM_SNAKE_SNAKE_H