#ifndef EOMM_SNAKE_APPLICATION_H
#define EOMM_SNAKE_APPLICATION_H
#include <memory>
#include <raylib.h>
#include "../Config.h"
#include "../Controller.h"
#include "../Game.h"


class Application {
public:
    Application();
    void run();

private:
    bool event_triggered(double interval);


    Config config;
    std::unique_ptr<Game> game;
    std::unique_ptr<Controller> controller;
    double last_updated_time;
};


#endif //EOMM_SNAKE_APPLICATION_H