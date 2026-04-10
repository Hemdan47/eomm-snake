#include "entities/Snake.h"

Snake::Snake(Config &config) : direction(Vector2{1,0}),
                               config(config) {
    reset();
}

void Snake::draw() {
    for (std::size_t i = 0 ; i < body.size() ; i++) {
        float x = body[i].x;
        float y = body[i].y;

        Rectangle segment = Rectangle{config.offset + x * config.cell_size,
                                      config.offset + y * config.cell_size,
                                      (float)config.cell_size,
                                      (float)config.cell_size};

        DrawRectangleRounded(segment , 0.5 , 6 , config.burnt_orange);
    }
}

void Snake::update(bool add = false) {
    body.push_front(Vector2Add(body.front() , direction));
    if (!add) {
        body.pop_back();
    }
}
void Snake::reset() {
    body = {Vector2{6,9} , Vector2{5,9} , Vector2{4,9}};
    direction = Vector2{1,0};
}

std::deque<Vector2> Snake::get_body() const {
    return body;
}

Vector2 Snake::get_direction() const {
    return direction;
}

void Snake::set_direction(Vector2 direction) {
    this->direction = direction;
}