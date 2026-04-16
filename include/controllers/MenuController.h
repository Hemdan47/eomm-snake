#ifndef EOMM_SNAKE_MENUCONTROLLER_H
#define EOMM_SNAKE_MENUCONTROLLER_H

#include <vector>

#include "ui/Button.h"

enum class MenuAction {
    None,
    Play,
    SelectClassicMode,
    SelectWrapAroundMode
};

struct MenuButtonDescriptor {
    Button button;
    MenuAction action;
};

class MenuController {
public:
    MenuAction handle_menu(const std::vector<MenuButtonDescriptor> &buttons) const;
};

#endif //EOMM_SNAKE_MENUCONTROLLER_H