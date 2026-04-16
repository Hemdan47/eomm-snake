#ifndef EOMM_SNAKE_CONTROLLER_H
#define EOMM_SNAKE_CONTROLLER_H
#include "raylib.h"

class Controller {
public:
    Vector2 handle_movement(Vector2 current_direction , bool &running);
};
#endif //EOMM_SNAKE_CONTROLLER_H