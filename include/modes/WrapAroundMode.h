#ifndef EOMM_SNAKE_WRAPAROUNDMODE_H
#define EOMM_SNAKE_WRAPAROUNDMODE_H
#include "core/Game.h"

class WrapAroundMode : public Game {
public:
    explicit WrapAroundMode(Config &config);
    virtual void update();
};

#endif //EOMM_SNAKE_WRAPAROUNDMODE_H