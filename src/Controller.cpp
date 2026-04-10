#include "Controller.h"

Vector2 Controller::handle_movement(Vector2 current_direction , bool &running) {
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        && current_direction.y != 1) {

            running = true;
            return Vector2{0,-1};
    }

    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        && current_direction.y != -1) {

            running = true;
            return Vector2{0,1};
        }

    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        && current_direction.x != -1) {

            running = true;
            return Vector2{1,0};
        }

    if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        && current_direction.x != 1) {

            running = true;
            return Vector2{-1,0};
        }

    return current_direction;

}
