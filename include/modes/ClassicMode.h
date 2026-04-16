#ifndef EOMM_SNAKE_CLASSICMODE_H
#define EOMM_SNAKE_CLASSICMODE_H
#include "core/Game.h"

class ClassicMode : public Game {
public:
    explicit ClassicMode(Config &config);
    bool check_collision_with_wall();
    virtual void update();
};


#endif //EOMM_SNAKE_CLASSICMODE_H