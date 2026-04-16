#include "controllers/MenuController.h"

MenuAction MenuController::handle_menu(const std::vector<MenuButtonDescriptor> &buttons) const {
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return MenuAction::None;
    }

    Vector2 mouse_position = GetMousePosition();

    for (const MenuButtonDescriptor &descriptor : buttons) {
        if (descriptor.button.contains(mouse_position)) {
            return descriptor.action;
        }
    }

    return MenuAction::None;
}