#include "entities/Food.h"

Food::Food(Config &config, Vector2 initial_position) : config(config), position(initial_position) {
    Image image = LoadImage("resources/images/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}
Food::~Food() {
    UnloadTexture(texture);
}
void Food::draw() {
    DrawTexture(texture , config.offset + position.x * config.cell_size,
        config.offset + position.y * config.cell_size, WHITE);
}

Vector2 Food::get_position() const {
    return position;
}

void Food::set_position(Vector2 new_position) {
    this->position = new_position;
}