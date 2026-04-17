#ifndef EOMM_SNAKE_APPLICATION_H
#define EOMM_SNAKE_APPLICATION_H
#include <memory>
#include <raylib.h>
#include "Config.h"
#include "Game.h"
#include "Menu.h"


class Application {
public:
    Application();
    void run();

private:
    enum class Scene {
        Menu,
        Game
    };

    bool event_triggered(double interval);
    std::unique_ptr<Game> create_game_for_selected_mode(GameMode mode);


    Config config;
    std::unique_ptr<Game> game;
    std::unique_ptr<Menu> menu;
    Scene current_scene;
    double last_updated_time;
};


#endif //EOMM_SNAKE_APPLICATION_H