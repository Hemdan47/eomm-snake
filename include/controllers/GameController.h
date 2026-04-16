#ifndef EOMM_SNAKE_GAMECONTROLLER_H
#define EOMM_SNAKE_GAMECONTROLLER_H

#include "raylib.h"

class GameController {
public:
    Vector2 handle_movement(Vector2 current_direction, bool &running);
};

#endif //EOMM_SNAKE_GAMECONTROLLER_H