#ifndef EOMM_SNAKE_MENU_H
#define EOMM_SNAKE_MENU_H

#include <cstddef>
#include <string>
#include <vector>

#include "Config.h"
#include "core/Scoreboard.h"
#include "controllers/MenuController.h"
#include "ui/Button.h"
#include "ui/TextInputBox.h"

enum class GameMode {
    Classic,
    WrapAround
};

class Menu {
public:
    explicit Menu(Config &config);
    void update();
    void draw() const;
    void add_score(std::size_t score);
    bool consume_start_request();
    GameMode get_selected_mode() const;

private:
    TextInputBox create_name_input_box() const;
    MenuButtonDescriptor create_menu_button(const std::string &label,
                                            int index,
                                            MenuAction action) const;
    bool is_button_selected(MenuAction action) const;

    Config &config;
    GameMode selected_mode;
    std::vector<MenuButtonDescriptor> buttons;
    TextInputBox name_input;
    Scoreboard scoreboard;
    MenuController controller;
    bool start_requested;
};

#endif //EOMM_SNAKE_MENU_H