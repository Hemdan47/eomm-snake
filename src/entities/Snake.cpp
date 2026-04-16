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

void Snake::update(bool add = false, bool wrap = false) {
    Vector2 head = Vector2Add(body.front() , direction);
    Vector2 mod = {(float)config.cell_count , (float)config.cell_count};
    if (wrap) {
        head = {
            fmodf(fmodf(head.x, mod.x) + mod.x , mod.x),
            fmodf(fmodf(head.y, mod.y) + mod.y , mod.y)
        };
    }

    body.push_front(head);
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