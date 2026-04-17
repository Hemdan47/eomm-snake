#ifndef EOMM_SNAKE_MENU_H
#define EOMM_SNAKE_MENU_H

#include <vector>

#include "Config.h"
#include "controllers/MenuController.h"
#include "ui/Button.h"

enum class GameMode {
    Classic,
    WrapAround
};

class Menu {
public:
    explicit Menu(Config &config);
    void update();
    void draw() const;
    bool consume_start_request();
    GameMode get_selected_mode() const;

private:
    MenuButtonDescriptor create_menu_button(const char *label,
                                            int index,
                                            MenuAction action) const;
    bool is_button_selected(MenuAction action) const;

    Config &config;
    GameMode selected_mode;
    std::vector<MenuButtonDescriptor> buttons;
    MenuController controller;
    bool start_requested;
};

#endif //EOMM_SNAKE_MENU_H